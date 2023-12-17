cmake_minimum_required(VERSION 3.21)
message("Using toolchain file ${CMAKE_TOOLCHAIN_FILE}.")

########################################################################################################################
## Define project
########################################################################################################################
project(Pronouns64 VERSION 2.1.1 LANGUAGES CXX ASM_MASM)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

set(sources src/Main.cpp src/Papyrus.cpp src/PronounOverrides.cpp src/Serialization.cpp src/PronounProfile.h src/PronounHooks.h)


########################################################################################################################
## Configure target DLL
########################################################################################################################
find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${sources})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/PCH.h)