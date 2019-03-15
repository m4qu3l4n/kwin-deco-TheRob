set(therob_plugin_SRCS
    therobbutton.cpp
    therobplugin.cpp
    therobcolors.cpp
    )

add_library(therobplugin SHARED ${therob_plugin_SRCS})
target_link_libraries(therobplugin Qt5::Core Qt5::Gui Qt5::Quick)

get_target_property (QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_QML OUTPUT_VARIABLE QMLDIR)
string(REGEX REPLACE "\n$" "" QMLDIR "${QMLDIR}")
install(TARGETS therobplugin DESTINATION ${QMLDIR}/org/kde/kwin/decorations/therob)
install(FILES qmldir DESTINATION ${QMLDIR}/org/kde/kwin/decorations/therob)
