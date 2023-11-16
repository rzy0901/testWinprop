//
// Created by Ren Zhenyu on 2021/7/7. Modified by Ji Chenqing on 2023/11/16.
//
#include <iostream>
#include <fstream>
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

using namespace std;

/*Macro API_DATA_FOLDER was defined in CMakeLists.txt.*/
#ifndef API_DATA_FOLDER
#define API_DATA_FOLDER "D:/Codes/testWinprop/data/"
#endif


int main()
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
    WinPropScenario.VectorDatabase = API_DATA_FOLDER "test_database/indoor_office.idb";
    /* Define callback functions. */
    WinPropCallback.Percentage = CallbackProgress;
    WinPropCallback.Message = CallbackMessage;
    WinPropCallback.Error = CallbackError;

    const int NbrTimeInstances = 8;
    WinPropMore.NbrTimeInstances = NbrTimeInstances;
    double timeInstances[NbrTimeInstances];
    double framerate = 1;
    for(int i = 0; i < WinPropMore.NbrTimeInstances; i++)
        timeInstances[i] = framerate*i;
    /* Call the WinProp API to open a project and load the vector database. */
    Error = WinProp_Open(&ProjectHandle, &WinPropScenario, &WinPropCallback);
    /* --------------------------------------- Set up prediction --------------------------------- */
    if (Error == 0) {
        /* Definition of prediction trajectory and resolution. */
        WinPropTrajectory.Name = "L-shape";
        WinPropTrajectory.NrPoints = 3; // Number of corners of the trajectory.
        WinPropTrajectory.samplingResolution = 0.1;
        WinProp_Trajectory_Point points[3];
        points[0] = {COORDPOINT{6.00,1.50,1},1.0,0,0,0};
        points[1] = {COORDPOINT{3.5,1.5,1},1.0,0,0,0};
        points[2] = {COORDPOINT{3.5,6.5,1},1.0,0,0,0};
        WinPropTrajectory.Points = points;
        WinPropTrajectory.PointSize = 0.1; // Resolution for each sampling point, default by 1.

        /* Defintion of antenna properties. */
        WinPropAntenna.Enabled = 1;
        WinPropAntenna.Longitude_X = 3.5;
        WinPropAntenna.Latitude_Y = 7.0;
        WinPropAntenna.Height = 1.25; // Antenna height 1.25 meter
        WinPropAntenna.Model = WINPROP_MODEL_SRT; // Use the DPM
        WinPropAntenna.DataType = PROP_RESULT_POWER; // Compute received power
        WinPropAntenna.Power = 40.0; // Power in dBm 10w =10^4 mw = 40dBm
        WinPropAntenna.Frequency = 2000; // Frequency 1800 MHz
        WinPropAntenna.Name = "TX"; // name of the antenna

        /* Definition of outputs to be computed and written in WinProp format. */
        WinPropMore.OutputResults = &OutputResults;
        OutputResults.ResultPath = API_DATA_FOLDER "indoor_trajectory_csv"; // Output data directory
        WinPropMore.TimeInstances = timeInstances;
        OutputResults.AdditionalResultsASCII = 1;
        OutputResults.StrFilePropPaths = 1;
        OutputResults.RayFilePropPaths = 1;
        /* Further parameters: With filtering. */
        WinPropMore.ResultFiltering = 1;
        char* filename = API_DATA_FOLDER "indoor_trajectory_csv/CIR.csv";
        ofstream myfile(filename);
        if(!myfile.is_open())
        {
            cout << " Can not open " << filename << endl;
        }
        /*time(s) field strength(dBuV/m) delay(ns)*/
        myfile << "TimeSteps,Delay,FieldStrength,DopplerShift,AoD_Azimuth,AoA_Azimuth,AoD_Elevation,AoA_Elevation"<<endl;
        // begin the loop for each time stamps
        for (int count = 0; count < 8; count++) {
            if (count == 0) {
                WinPropMore.TimeInstances = WinPropMore.TimeInstances;
            }
            else {
                WinPropMore.TimeInstances = WinPropMore.TimeInstances + 1;
            }
            /* ------------------------------------ Start prediction -------------------------------- */
            WinProp_Predict_Trajectories(ProjectHandle, &WinPropAntenna, &WinPropTrajectory,
                                         1, nullptr, &WinPropMore,
                                         &TrajectoryList, nullptr, nullptr);
            for (int i = 0; i < TrajectoryList->trajectories[0].NrSampledPoints; i++) {
                for (int j = 0; j < TrajectoryList->trajectories[0].ResultPoints.ResultPoints->Rays.NrRays; j++) {
                    /*RayMatrix->Rays(NbrHeights,Columns,Lines)*/
                    double *timeSteps_ptr = TrajectoryList->trajectories[0].ResultPoints.TimeSteps;
                    myfile << *timeSteps_ptr << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].Delay << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].FieldStrength
                           << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].DopplerShift
                           << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].AngleAzimutBTS
                           << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].AngleAzimutMS
                           << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].AngleElevationBTS
                           << ","
                           << TrajectoryList->trajectories[0].ResultPoints.ResultPoints[i].Rays.Rays[j].AngleElevationMS
                           << ","
                           << endl;
                }
            }
        }
        cout << endl;
//        cout << RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolHfieldX << RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolHfieldY << RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolHfieldZ<< RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolVfieldX << RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolVfieldY << RayMatrix->Rays[0][x][y].Rays[0].FieldVectors.PolVfieldZ << endl;
        myfile.close();
        WinProp_Close(ProjectHandle);
    }
    return 0;
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
        /* Loop through WinPropall pixels. */
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