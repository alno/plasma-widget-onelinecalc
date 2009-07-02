# Project Needs a name ofcourse
project(onelinecalc)
 
# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} )
 
# We add our source code here
set(onelinecalc_SRCS onelinecalc.cpp configdialog.cpp)

kde4_add_ui_files( onelinecalc_SRCS preferences.ui )
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_onelinecalc ${onelinecalc_SRCS})
target_link_libraries(plasma_onelinecalc plasma ${KDE4_KDEUI_LIBS} ${QT_QTSCRIPT_LIBRARY})
 
install(TARGETS plasma_onelinecalc
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-onelinecalc.desktop
        DESTINATION ${SERVICES_INSTALL_DIR}) 
