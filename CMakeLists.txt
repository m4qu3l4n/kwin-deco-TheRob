project(therobdecoration)
cmake_minimum_required(VERSION 3.7.2)
set(QT_MIN_VERSION "5.6.0")
set(KF5_MIN_VERSION "5.26.0")

set (KDE_INSTALL_USE_QT_SYS_PATHS TRUE)
find_package(ECM 0.0.11 REQUIRED NO_MODULE)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    Quick
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMInstallIcons)
include(ECMOptionalAddSubdirectory)

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0 -DQT_USE_QSTRINGBUILDER)

# require at least gcc 4.8
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if ("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "4.8")
        message(SEND_ERROR "Version ${CMAKE_CXX_COMPILER_VERSION} of the ${CMAKE_CXX_COMPILER_ID} C++ compiler is not supported. Please use version 4.8 or later.")
    endif()
endif()


set(KWIN_NAME "kwin")
add_subdirectory(code)
install(DIRECTORY package/
       DESTINATION ${KDE_INSTALL_FULL_DATADIR}/${KWIN_NAME}/decorations/kwin4_decoration_qml_therob)

install(FILES package/metadata.desktop
        DESTINATION ${KDE_INSTALL_FULL_KSERVICES5DIR}/${KWIN_NAME}
        RENAME kwin4_decoration_qml_therob.desktop)
