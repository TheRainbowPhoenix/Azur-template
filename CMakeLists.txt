# Configure with [fxsdk build-cp], which provides the toolchain file and
# module path of the fxSDK.

cmake_minimum_required(VERSION 3.15)
project(AzurTemplate VERSION 0.1 LANGUAGES CXX C ASM)

include(GenerateG1A)
include(GenerateG3A)
include(GenerateHH3)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)

set(SOURCES
  src/main.cxx
)

set(ASSETS
)

set(ASSETS_fx
)

set(ASSETS_cg
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

list(APPEND CMAKE_MODULE_PATH "$ENV{AZUR_PATH_${AZUR_PLATFORM}}/lib/cmake")
find_package(Azur 0.1 REQUIRED)

add_executable(AzurTemplate ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(AzurTemplate PRIVATE -Wall -Wextra -Os -g -flto=auto)
target_link_libraries(AzurTemplate Gint::Gint)

if(AZUR_PLATFORM STREQUAL gint)
  target_link_libraries(AzurTemplate Azur::Azur)
else()
  target_link_libraries(AzurTemplate Azur::Azur Azur::GLM Azur::ImGui)
endif()

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET AzurTemplate OUTPUT "AzurTemplate.g1a"
    NAME "AzurTemplate" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET AzurTemplate OUTPUT "AzurTemplate.g3a"
    NAME "AzurTemplate" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G_G3A)
  generate_g3a(TARGET AzurTemplate OUTPUT "AzurTemplate-fx.g3a"
    NAME "AzurTemplate-fx" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCP)
  generate_hh3(TARGET AzurTemplate OUTPUT "AzurTemplate.hh3")
endif()
