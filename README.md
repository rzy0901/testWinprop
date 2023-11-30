## Channel Modeling and Simulation Based on Altair Winprop C++ API

**Run the programs again to produce the simulation results.**
+ Simulation goal: simulate the channel variations and received power variations due to impacts of moving objects or moving RXs.

+ Environment settings: `MSVC(VS 2019)` + `Clion 2023` + `WinProp API 2022 for windows`. Use `CMakeLists.txt` to compile the project.

## How to Run and Use
- Firstly, run the ./indoor_trajectory_csv.cpp to get the CIR.csv and some TX Power.txt files.
- Then, run the ./indoor_trajectory_str.cpp to get the TX Rays.str file.
- Finally, open the ./data/indoor_trajectory folder to see the above result files.

