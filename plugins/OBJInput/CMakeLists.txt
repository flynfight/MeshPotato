SET(PLUGIN_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include
      ${Boost_INCLUDE_DIRS}
      ${PYTHON_INCLUDE_PATH}
  )
SET(PLUGIN_LIBRARY_DIRS meshpotato
      ${PYTHON_LIBRARIES}
      ${Boost_LIBRARIES}
  )
INCLUDE_DIRECTORIES(${PLUGIN_INCLUDE_DIRS})



SET(OBJINPUT_SRC OBJInputPlugin.C)
SET(OBJINPUT_PYTHON_SRC pyOBJInputPlugin.C)

ADD_LIBRARY(objinput SHARED ${OBJINPUT_SRC})
TARGET_LINK_LIBRARIES(objinput meshpotato)
INSTALL(TARGETS objinput DESTINATION lib)

ADD_LIBRARY(pyOBJInputPlugin MODULE ${OBJINPUT_PYTHON_SRC})
SET_TARGET_PROPERTIES(pyOBJInputPlugin PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(pyOBJInputPlugin PROPERTIES SUFFIX ".so")
TARGET_LINK_LIBRARIES(pyOBJInputPlugin meshpotato ${PLUGIN_LIBRARY_DIRS})
INSTALL(TARGETS pyOBJInputPlugin DESTINATION pymeshpotato)
