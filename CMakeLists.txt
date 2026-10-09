# Configure with [fxsdk build-cp], which provides the toolchain file and
# module path of the fxSDK.

cmake_minimum_required(VERSION 3.15)
project(AzurTemplate VERSION 0.1 LANGUAGES CXX C ASM)

include(GenerateHH3)
include(Fxconv)

find_package(Gint 2.9 REQUIRED)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Azur is used as a source submodule. Run:
#   git submodule update --init --recursive
# before building outside Codespaces.
add_subdirectory(azur)

set(SOURCES
  src/main.cxx
)

set(ASSETS)
set(ASSETS_cp)

fxconv_declare_assets(${ASSETS} ${ASSETS_cp} WITH_METADATA)

add_executable(azur_template ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(azur_template PRIVATE -Wall -Wextra -Os -g)
target_link_libraries(azur_template -lstdc++ azur num Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fxCP)
  generate_hh3(TARGET azur_template OUTPUT "AzurTemplate.hh3")
endif()

