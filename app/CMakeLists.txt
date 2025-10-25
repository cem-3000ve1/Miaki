
cmake_minimum_required(VERSION 3.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(MIAKI)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "★Miaki")
set(VITA_TITLEID  "MIAKITOOL")

set(VITA_VERSION  "02.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS}")
set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS}")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
  src/pup.c
  src/main.c
  src/ctrl.c
  src/source/utils.c
  src/source/menu/edition.c
  src/source/menu/activation.c
  src/source/menu/boot_parameters.c
  src/source/modules.c
  src/source/flasher.c
  src/source/flasher/boot.c
  src/source/flasher/config.c
  src/source/ui/ui.c
  src/source/compat/cex2rex.c
  src/source/compat/config.c
  src/source/compat/idu.c
)

target_link_libraries(${PROJECT_NAME}
  c
  SceLibKernel_stub
  SceIofilemgr_stub
  SceAppMgr_stub
  SceCtrl_stub
  SceDisplay_stub
  SceVshBridge_stub
  SceShellSvc_stub
  ScePower_stub
  SceRegistryMgr_stub
  Miaki_User_stub_weak
  taihen_stub
  vita2d
  SceGxm_stub
  SceSysmodule_stub
  ScePgf_stub
  SceCommonDialog_stub
  SceTouch_stub
  m
	SceNpManager_stub
	SceNpCommon_stub_weak
	SceSblPostSsMgr_stub
)

vita_create_self(eboot.bin ${PROJECT_NAME} UNSAFE)

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}

  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE user.suprx user.suprx  
  FILE kernel.skprx kernel.skprx
  FILE kmspico.skprx kmspico.skprx
  FILE dkmspico.skprx dkmspico.skprx
  FILE ykmspico.skprx ykmspico.skprx
  FILE lowkmspico.skprx lowkmspico.skprx
  FILE testkit_vita.skprx testkit_vita.skprx
  FILE devmode.skprx devmode.skprx
  FILE reF00D.skprx reF00D.skprx
  FILE pro_vita.skprx pro_vita.skprx
  FILE dev_vita.skprx dev_vita.skprx
  FILE vitaConfig.txt vitaConfig.txt
  FILE app.info app.info
)
