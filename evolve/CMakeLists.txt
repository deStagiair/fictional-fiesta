find_package(Qt5Widgets)

if (Qt5Widgets_FOUND)

  set(EVOLVE_GUI_ITF
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/WorldView.h
    CACHE INTERNAL "")

  set(EVOLVE_GUI_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/WorldView.cpp
    CACHE INTERNAL "")
  
  set(EVOLVE_GUI_FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/MainWindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/evolve/WorldView.ui
    CACHE INTERNAL "")

  set(CMAKE_AUTOMOC ON)
  SET(CMAKE_AUTOUIC ON)

  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

  include_directories(${CMAKE_SOURCE_DIR})
  include_directories(${Qt5Widgets_INCLUDE_DIRS})

  add_executable(evolve-gui ${EVOLVE_GUI_SRC} ${EVOLVE_GUI_ITF})
  
  target_link_libraries(evolve-gui Qt5::Widgets)
  target_link_libraries(evolve-gui fictional-fiesta)
  target_link_libraries(evolve-gui pugixml)
  target_link_libraries(evolve-gui stdc++fs)

else ()
  message(STATUS "QT5 not found, the evolve-gui target will not be generated.")
endif ()
