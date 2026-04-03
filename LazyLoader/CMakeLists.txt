cmake_minimum_required(VERSION 3.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(LazyLoader)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -nostdlib")

add_executable(LazyLoader
  src/main.c
  src/config.c
  src/act_sm.c
)

target_link_libraries(LazyLoader
  SceSysmemForKernel_stub
  SceIofilemgrForDriver_stub 
  SceSysclibForDriver_stub 
  SceCpuForKernel_stub
  SceDipswForDriver_stub
  taihenForKernel_stub
  SceDebugForDriver_stub
  SceModulemgrForDriver_stub
  SceThreadmgrForDriver_stub
  SceProcessmgrForDriver_stub
  SceSysmemForDriver_stub
  SceSysrootForKernel_stub
  taihenModuleUtils_stub
)

vita_create_self(LazyLoader.skprx LazyLoader
  UNSAFE
  CONFIG exports.yml
)
