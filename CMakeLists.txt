cmake_minimum_required(VERSION 3.10)
project(Miaki)

if(NOT DEFINED ENV{VITASDK})
    message(FATAL_ERROR "You need to install vitasdk and define the sdk path.")
endif()

set(VITASDK $ENV{VITASDK})
set(CMAKE_TOOLCHAIN_FILE "${VITASDK}/share/vita.toolchain.cmake")
set(BUILD_ROOT ${CMAKE_SOURCE_DIR}/build)
add_compile_options(-Wno-error=implicit-function-declaration -Wno-implicit-function-declaration)

macro(vita_build_cmake NAME DIR)
  add_custom_target(${NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_ROOT}/${DIR}
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR}/${DIR}
                             -B ${BUILD_ROOT}/${DIR}
    COMMAND ${CMAKE_MAKE_PROGRAM} -s -C ${BUILD_ROOT}/${DIR} install
  )
endmacro()

macro(vita_build_cmake_noinstall NAME DIR)
  add_custom_target(${NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_ROOT}/${DIR}
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR}/${DIR}
                             -B ${BUILD_ROOT}/${DIR}
    COMMAND ${CMAKE_MAKE_PROGRAM} -s -C ${BUILD_ROOT}/${DIR}
  )
endmacro()

macro(vita_build_makefile NAME DIR)
  add_custom_target(${NAME}
    COMMAND ${CMAKE_MAKE_PROGRAM} -s clean
    COMMAND ${CMAKE_MAKE_PROGRAM} -s
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${DIR}
  )
endmacro()

vita_build_cmake(build_kernel         kernel)
vita_build_cmake_noinstall(build_deeper_spoofer  deeper-spoofer)
vita_build_cmake(build_user           user)
vita_build_cmake(build_devmode        devmode)
vita_build_cmake(build_qaf_qafull     devmode/qaf/qafull)
vita_build_cmake(build_qaf_sceshell   devmode/qaf/sceshell)
vita_build_cmake(build_qaf_debugflag  devmode/qaf/debugflag)
vita_build_cmake(build_yellowmsg      kmspico/src/yellowmsg)
vita_build_cmake(build_lowact         kmspico/src/lowact)
vita_build_cmake(build_kms            kmspico/src/kms)
vita_build_cmake(build_kmspico        kmspico)

add_dependencies(build_kms      build_lowact)
add_dependencies(build_kmspico  build_kms build_yellowmsg build_lowact)

vita_build_makefile(build_spoofer_tool  spoofer_vita/TOOL)
vita_build_makefile(build_spoofer_test  spoofer_vita/TEST)
vita_build_makefile(build_spoofer_vita  spoofer_vita)

add_dependencies(build_spoofer_test  build_spoofer_tool)
add_dependencies(build_spoofer_vita  build_spoofer_test)

add_custom_target(build_all)
add_dependencies(build_all
  build_kernel
  build_deeper_spoofer
  build_spoofer_vita
  build_user
  build_devmode
  build_qaf_qafull
  build_qaf_sceshell
  build_qaf_debugflag
  build_kmspico
)

add_custom_target(move_plugins
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/kmspico/src/lowact/lowact.skprx
          ${CMAKE_SOURCE_DIR}/app/lowkmspico.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/kmspico/src/yellowmsg/yellowmsg.skprx
          ${CMAKE_SOURCE_DIR}/app/ykmspico.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/kmspico/src/kms/kmspico.skprx
          ${CMAKE_SOURCE_DIR}/app/kmspico.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/kmspico/dkmspico.skprx
          ${CMAKE_SOURCE_DIR}/app/dkmspico.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_SOURCE_DIR}/spoofer_vita/TOOL/kDump.skprx
          ${CMAKE_SOURCE_DIR}/app/dev_vita.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/deeper-spoofer/spoofer.skprx
          ${CMAKE_SOURCE_DIR}/app/spoofer.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_SOURCE_DIR}/spoofer_vita/TEST/kDump.skprx
          ${CMAKE_SOURCE_DIR}/app/pro_vita.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_SOURCE_DIR}/spoofer_vita/kDump.skprx
          ${CMAKE_SOURCE_DIR}/app/testkit_vita.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/devmode/devmode.skprx
          ${CMAKE_SOURCE_DIR}/app/devmode.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/devmode/qaf/sceshell/sceshell.skprx
          ${CMAKE_SOURCE_DIR}/app/sceshell.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/devmode/qaf/qafull/qafull.skprx
          ${CMAKE_SOURCE_DIR}/app/qafull.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/devmode/qaf/debugflag/debugflag.skprx
          ${CMAKE_SOURCE_DIR}/app/debugflag.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/kernel/kernel.skprx
          ${CMAKE_SOURCE_DIR}/app/kernel.skprx
  COMMAND ${CMAKE_COMMAND} -E copy
          ${BUILD_ROOT}/user/user.suprx
          ${CMAKE_SOURCE_DIR}/app/user.suprx
  DEPENDS build_all
)

add_custom_target(build_miaki
  COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_ROOT}/app
  COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR}/app
                           -B ${BUILD_ROOT}/app
  COMMAND ${CMAKE_MAKE_PROGRAM} -s -C ${BUILD_ROOT}/app
  DEPENDS move_plugins
)

add_custom_target(ALL_TARGET ALL
  DEPENDS build_miaki
  COMMAND ${CMAKE_COMMAND} -E copy
        ${BUILD_ROOT}/app/MIAKI.vpk
        ${BUILD_ROOT}/release.vpk
)
