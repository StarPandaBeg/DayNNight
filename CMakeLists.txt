cmake_minimum_required(VERSION 3.16)
project(DayNNight LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB_RECURSE source_files
   "src/*.cpp"
   "src/Base/*.cpp"
   "src/Collision/*.cpp"
   "src/Nodes/*.cpp"
)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCE_FILES ${source_files})
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(DayNNight src/main.cpp ${source_files})

target_link_libraries(DayNNight PRIVATE sfml-graphics)
target_include_directories(DayNNight PRIVATE src/)
target_compile_features(DayNNight PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET DayNNight
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:DayNNight>
        VERBATIM)
endif()

install(TARGETS DayNNight)