//
// Created by Ren Zhenyu on 2021/7/7.
//
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Interface/Engine.h"
#include "Interface/Convert.h"
#include "Interface/OutdoorPlugIn.h"
#include "Interface/OutdoorPlugInPrePro.h"
#include "Net/Net.h"
#include "Interface/Init.h"
#include "Interface/Prepro.h"
#include "Public/Interface/Clutter.h"
#include "Public/Interface/Topo.h"

int _STD_CALL CallbackMessage(const char *Text);
int _STD_CALL CallbackProgress(int value, const char* text);
int _STD_CALL CallbackError(const char *Message, int Mode);
void write_ascii(WinProp_Result Resultmatrix, char* Filename);
void simu_DPM();
void simu_IRT();
void simu_SRT();
using namespace std;

#ifndef API_DATA_FOLDER
#define API_DATA_FOLDER "D:/Codes/testWinprop/data/"
#endif

int main()
{
    /*Generate .oib file for IRT.*/
    simu_DPM();
    simu_SRT();
    simu_IRT();
    return 0;
}
void simu_IRT()
{
    int                 Error = 0;
    WinProp_ParaMain    GeneralParameters;
    WinProp_Antenna     WinPropAntenna;
    WinProp_Callback    Callback;
    WinProp_Propagation_Results OutputResults;
    WinProp_Trajectory  WinPropTrajectory;
    WinProp_ResultTrajectoryList *TrajectoryList = NULL;

    /* ------------------------ Initialisation of parameters ----------------------*/
    WinProp_Structure_Init_ParameterMain(&GeneralParameters);
    WinProp_Structure_Init_Antenna(&WinPropAntenna);
    WinProp_Structure_Init_Propagation_Results(&OutputResults);
    WinProp_Structure_Init_Trajectory(&WinPropTrajectory);
    /*---------------- Definition of scenario -------------------------------------*/
    /* Definition of general parameters. */
    GeneralParameters.ScenarioMode = SCENARIOMODE_URBAN; // Urban prediction
    GeneralParameters.PredictionModelUrban = PREDMODEL_IRT; // Use IRT Model
    GeneralParameters.Resolution = 1; // Resolution in meter
    GeneralParameters.PredictionHeight = 1.5; // Prediction height in meter
    GeneralParameters.BuildingsMode = BUILDINGSMODE_IRT ; // .oib
    sprintf(GeneralParameters.BuildingsName, "%s", API_DATA_FOLDER "test_database/f_park");
    /* Defintion of antenna properties. */
    WinPropAntenna.Enabled = 1;
    WinPropAntenna.Longitude_X = 340;
    WinPropAntenna.Latitude_Y = 280;
    WinPropAntenna.Height = 15; // Antenna height 15 meter
    WinPropAntenna.Model = WINPROP_MODEL_IRT; // Use the DPM
    WinPropAntenna.DataType = PROP_RESULT_POWER; // Compute received power
    WinPropAntenna.Power = 40.0; // Power in dBm 10w =10^4 mw = 40dBm
    WinPropAntenna.Frequency = 2000; // Frequency 1800 MHz
    WinPropAntenna.Name = "TX"; // name of the antenna
    /* Definition of outputs to be computed and written in WinProp format. */
    GeneralParameters.OutputResults = &OutputResults;
    OutputResults.ResultPath = API_DATA_FOLDER "outdoor_trajectory/IRT"; // Output data directory
    OutputResults.RayFilePropPaths = 1;
    OutputResults.StrFilePropPaths = 1;
    OutputResults.AdditionalResultsASCII = 1;
    /* Definition of prediction trajectory and resolution. */
    WinPropTrajectory.Name = "I";
    WinPropTrajectory.NrPoints = 2; // Number of corners of the trajectory.
    WinPropTrajectory.samplingResolution = 1;
    WinProp_Trajectory_Point points[2];
    points[0] = {COORDPOINT{240,80,1.5},10,0,0,0};
    points[1] = {COORDPOINT{240,420,1.5},10,0,0,0};
    WinPropTrajectory.Points = points;
    WinPropTrajectory.PointSize = 1; // Resolution for each sampling point, default by 1.
    /*-------------------------- Callbacks --------------------------------------------------*/
    Callback.Percentage = CallbackProgress;
    Callback.Message = CallbackMessage;
    Callback.Error = CallbackError;
    Error = OutdoorPlugIn_ComputeTrajectories(&WinPropAntenna,&GeneralParameters, NULL, NULL,&WinPropTrajectory,1,&Callback,TrajectoryList);
}
void simu_SRT()
{
    int                 Error = 0, ProjectHandle = 0;
    WinProp_Scenario    WinPropScenario;
    WinProp_Callback    WinPropCallback;
    WinProp_Trajectory  WinPropTrajectory;
    WinProp_Antenna     WinPropAntenna;
    WinProp_Additional  WinPropMore;
    WinProp_Propagation_Results OutputResults;
    WinProp_ResultTrajectoryList *TrajectoryList = NULL;
//    double              PredictionHeight = 1.25;
    /* --------------------------------- Initialization of structures --------------------------- */
    WinProp_Structure_Init_Scenario(&WinPropScenario);
    WinProp_Structure_Init_Trajectory(&WinPropTrajectory);
    WinProp_Structure_Init_Antenna(&WinPropAntenna);
    WinProp_Structure_Init_Additional(&WinPropMore);
    WinProp_Structure_Init_Propagation_Results(&OutputResults);
    /* -------------------------- Load indoor vector database and initialise scenario ------------ */
    /* Assign database name. */
    WinPropScenario.Scenario = WINPROP_SCENARIO_INDOOR;
    WinPropScenario.VectorDatabase = API_DATA_FOLDER "test_database/f_park.idb";
    /* Define callback functions. */
    WinPropCallback.Percentage = CallbackProgress;
    WinPropCallback.Message = CallbackMessage;
    WinPropCallback.Error = CallbackError;
    /* Call the WinProp API to open a project and load the vector database. */
    Error = WinProp_Open(&ProjectHandle, &WinPropScenario, &WinPropCallback);
    /* --------------------------------------- Set up prediction --------------------------------- */
    if (Error == 0) {
        /* Definition of prediction trajectory and resolution. */
        WinPropTrajectory.Name = "I";
        WinPropTrajectory.NrPoints = 2; // Number of corners of the trajectory.
        WinPropTrajectory.samplingResolution = 1;
        WinProp_Trajectory_Point points[2];
        points[0] = {COORDPOINT{240,80,1.5},1.0,0,0,0};
        points[1] = {COORDPOINT{240,420,1.5},1.0,0,0,0};
        WinPropTrajectory.Points = points;
        WinPropTrajectory.PointSize = 1; // Resolution for each sampling point, default by 1.

        /* Defintion of antenna properties. */
        WinPropAntenna.Enabled = 1;
        WinPropAntenna.Longitude_X = 340;
        WinPropAntenna.Latitude_Y = 280;
        WinPropAntenna.Height = 15; // Antenna height 15 meter
        WinPropAntenna.Model = WINPROP_MODEL_SRT; // Use the DPM
        WinPropAntenna.DataType = PROP_RESULT_POWER; // Compute received power
        WinPropAntenna.Power = 40.0; // Power in dBm 10w =10^4 mw = 40dBm
        WinPropAntenna.Frequency = 2000; // Frequency 1800 MHz
        WinPropAntenna.Name = "TX"; // name of the antenna

        /* Definition of outputs to be computed and written in WinProp format. */
        WinPropMore.OutputResults = &OutputResults;
        OutputResults.ResultPath = API_DATA_FOLDER "outdoor_trajectory/SRT"; // Output data directory
        OutputResults.AdditionalResultsASCII = 1;
        OutputResults.StrFilePropPaths = 1;
        OutputResults.RayFilePropPaths = 1;
        /* Further parameters: With filtering. */
        WinPropMore.ResultFiltering = 1;

        /* ------------------------------------ Start prediction -------------------------------- */
        WinProp_Predict_Trajectories(ProjectHandle, &WinPropAntenna,&WinPropTrajectory,1, nullptr,&WinPropMore,&TrajectoryList);
    }
    WinProp_Close(ProjectHandle);
}

void simu_DPM()
{
    int                 Error = 0;
    WinProp_ParaMain    GeneralParameters;
    WinProp_Antenna     WinPropAntenna;
    WinProp_Callback    Callback;
    WinProp_Propagation_Results OutputResults;
    WinProp_Trajectory  WinPropTrajectory;
    WinProp_ResultTrajectoryList *TrajectoryList = NULL;

    /* ------------------------ Initialisation of parameters ----------------------*/
    WinProp_Structure_Init_ParameterMain(&GeneralParameters);
    WinProp_Structure_Init_Antenna(&WinPropAntenna);
    WinProp_Structure_Init_Propagation_Results(&OutputResults);
    WinProp_Structure_Init_Trajectory(&WinPropTrajectory);
    /*---------------- Definition of scenario -------------------------------------*/
    /* Definition of general parameters. */
    GeneralParameters.ScenarioMode = SCENARIOMODE_URBAN; // Urban prediction
    GeneralParameters.PredictionModelUrban = PREDMODEL_UDP; // Use Dominant Path Model
    GeneralParameters.Resolution = 1; // Resolution in meter
    GeneralParameters.PredictionHeight = 1.5; // Prediction height in meter
    GeneralParameters.BuildingsMode = BUILDINGSMODE_BINARY; // .odb
    sprintf(GeneralParameters.BuildingsName, "%s", API_DATA_FOLDER "test_database/f_park");
    /* Defintion of antenna properties. */
    WinPropAntenna.Enabled = 1;
    WinPropAntenna.Longitude_X = 340;
    WinPropAntenna.Latitude_Y = 280;
    WinPropAntenna.Height = 15; // Antenna height 15 meter
    WinPropAntenna.Model = WINPROP_MODEL_DPM; // Use the DPM
    WinPropAntenna.DataType = PROP_RESULT_POWER; // Compute received power
    WinPropAntenna.Power = 40.0; // Power in dBm 10w =10^4 mw = 40dBm
    WinPropAntenna.Frequency = 2000; // Frequency 1800 MHz
    WinPropAntenna.Name = "TX"; // name of the antenna
    /* Definition of outputs to be computed and written in WinProp format. */
    GeneralParameters.OutputResults = &OutputResults;
    OutputResults.ResultPath = API_DATA_FOLDER "outdoor_trajectory/DPM"; // Output data directory
    OutputResults.RayFilePropPaths = 1;
    OutputResults.StrFilePropPaths = 1;
    OutputResults.AdditionalResultsASCII = 1;
    /* Definition of prediction trajectory and resolution. */
    WinPropTrajectory.Name = "I";
    WinPropTrajectory.NrPoints = 2; // Number of corners of the trajectory.
    WinPropTrajectory.samplingResolution = 1;
    WinProp_Trajectory_Point points[2];
    points[0] = {COORDPOINT{240,80,1.5},10,0,0,0};
    points[1] = {COORDPOINT{240,420,1.5},10,0,0,0};
    WinPropTrajectory.Points = points;
    WinPropTrajectory.PointSize = 1; // Resolution for each sampling point, default by 1.
    /*-------------------------- Callbacks --------------------------------------------------*/
    Callback.Percentage = CallbackProgress;
    Callback.Message = CallbackMessage;
    Callback.Error = CallbackError;
    Error = OutdoorPlugIn_ComputeTrajectories(&WinPropAntenna,&GeneralParameters, NULL, NULL,&WinPropTrajectory,1,&Callback,TrajectoryList);
}
int _STD_CALL CallbackMessage(const char * Text)
{
    if (Text == nullptr)
        return 0;

    std::cout << "\n" << Text;

    return(0);
}

int _STD_CALL CallbackError(const char * Text, int Error)
{
    if (Text == nullptr)
        return 0;

    std::cout << "\n";

#ifdef __LINUX
    std::cout << "\033[31m" << "Error (" << Error << "): "; // highlight error in red color
#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    std::cout << "Error (" << Error << "): ";
#endif // __LINUX
    std::cout << Text;

#ifdef __LINUX
    std::cout << "\033[0m"; // highlight error in red color
#else
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#endif // __LINUX

    return 0;
}

int _STD_CALL CallbackProgress(int value, const char* text)
{
    char Line[200];

    sprintf(Line, "\n%d%% %s", value, text);
    std::cout << Line;

    return(0);
}

void write_ascii(WinProp_Result Resultmatrix, char* Filename) {
    FILE* OutputFile = fopen(Filename,"w");
    if (OutputFile)
    {
        /* Loop all pixels. */
        for (int x = 0; x < Resultmatrix.Columns; x++)
        {
            for (int y = 0; y < Resultmatrix.Lines; y++)
            {
                /* Compute real coordinates. */
                double Coordinate_X = Resultmatrix.LowerLeftX + ((double)x + 0.5) * Resultmatrix.Resolution;
                double Coordinate_Y = Resultmatrix.LowerLeftY + ((double)y + 0.5) * Resultmatrix.Resolution;

                /* Check if pixel was computed or not */
                if (Resultmatrix.Matrix[0][x][y] > -1000)
                    fprintf(OutputFile, "%.2f\t%.2f\t%.2f\n", Coordinate_X, Coordinate_Y, Resultmatrix.Matrix[0][x][y]);
            }
        }

        /* Close file. */
        fclose(OutputFile);
    }
    else
        printf("\nCould not open the File: %s for writing.\n",Filename);
}

