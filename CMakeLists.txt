# Define library. Only source files here!
set(PROJECT_NAME testWinprop)
set(PROJECT_DESC "Required os: win10 only, remember to update the winprop installation path in the other computer.")
cmake_minimum_required(VERSION 3.9)
project("${PROJECT_NAME}" DESCRIPTION ${PROJECT_DESC} LANGUAGES CXX C)
add_library( Engine SHARED IMPORTED )
set_target_properties( Engine PROPERTIES
        IMPORTED_LOCATION "D:/Download/Altair_2021/feko/api/winprop/export/winprop/64/Engine.dll"
        IMPORTED_IMPLIB "D:/Download/Altair_2021/feko/api/winprop/export/winprop/64/Engine.lib"
        )
add_executable(indoor_time_invariant indoor_time_invariant.cpp)
# Definition of Macros
target_compile_definitions(indoor_time_invariant PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_time_invariant PRIVATE "D:/Download/Altair_2021/feko/api/winprop/source")
#target_compile_features(indoor_time_invariant PUBLIC cxx_auto_type PRIVATE cxx_variadic_templates)
target_link_libraries(indoor_time_invariant PRIVATE Engine)

add_executable(indoor_trajectory indoor_trajectory.cpp)
target_compile_definitions(indoor_trajectory PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(indoor_trajectory PRIVATE "D:/Download/Altair_2021/feko/api/winprop/source")
target_link_libraries(indoor_trajectory PRIVATE Engine)

add_executable(outdoor_trajectory outdoor_trajectory.cpp)
target_compile_definitions(outdoor_trajectory PRIVATE API_DATA_FOLDER=\"${PROJECT_SOURCE_DIR}/data/\" _SBCS _DLL_ENGINE_IMPORT)
target_include_directories(outdoor_trajectory PRIVATE "D:/Download/Altair_2021/feko/api/winprop/source")
target_link_libraries(outdoor_trajectory PRIVATE Engine)