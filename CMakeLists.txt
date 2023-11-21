# Define library. Only source files here!
set(PROJECT_NAME testWinprop)
set(PROJECT_DESC "Required os: win10 only, remember to update the winprop installation path in the other computer.")
cmake_minimum_required(VERSION 3.9)
project("${PROJECT_NAME}" DESCRIPTION ${PROJECT_DESC} LANGUAGES CXX C)
add_library( Engine SHARED IMPORTED )
set_target_properties( Engine PROPERTIES
        IMPORTED_LOCATION "D:/Program Files/Altair/2022/feko/api/winprop/export/winprop/64/Engine.dll"
        IMPORTED_IMPLIB "D:/Program Files/Altair/2022/feko/api/winprop/export/winprop/64/Engine.lib"
        )
add_executable(indoor_time_variant indoor_time_variant.cpp)
# Definition of Macros
target_compile_definitions(indoor_time_variant PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_time_variant PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
#target_compile_features(indoor_time_variant PUBLIC cxx_auto_type PRIVATE cxx_variadic_templates)
target_link_libraries(indoor_time_variant PRIVATE Engine)

add_executable(indoor_trajectory_csv indoor_trajectory_csv.cpp)
target_compile_definitions(indoor_trajectory_csv PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_trajectory_csv PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
target_link_libraries(indoor_trajectory_csv PRIVATE Engine)

add_executable(indoor_trajectory_str indoor_trajectory_str.cpp)
target_compile_definitions(indoor_trajectory_str PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_trajectory_str PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
target_link_libraries(indoor_trajectory_str PRIVATE Engine)

add_executable(indoor_stationary_trajectory_str indoor_stationary_trajectory_str.cpp)
target_compile_definitions(indoor_stationary_trajectory_str PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_stationary_trajectory_str PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
target_link_libraries(indoor_stationary_trajectory_str PRIVATE Engine)

add_executable(indoor_stationary_trajectory_csv indoor_stationary_trajectory_csv.cpp)
target_compile_definitions(indoor_stationary_trajectory_csv PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_stationary_trajectory_csv PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
target_link_libraries(indoor_stationary_trajectory_csv PRIVATE Engine)

add_executable(outdoor_trajectory outdoor_trajectory.cpp)
target_compile_definitions(outdoor_trajectory PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(outdoor_trajectory PRIVATE "D:/Program Files/Altair/2022/feko/api/winprop/source")
target_link_libraries(outdoor_trajectory PRIVATE Engine)