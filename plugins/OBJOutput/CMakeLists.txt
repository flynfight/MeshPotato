SET(PLUGIN_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include
      ${Boost_INCLUDE_DIRS}
      ${PYTHON_INCLUDE_PATH}
  )
SET(PLUGIN_LIBRARY_DIRS meshpotato
      ${PYTHON_LIBRARIES}
      ${Boost_LIBRARIES}
  )
INCLUDE_DIRECTORIES(${PLUGIN_INCLUDE_DIRS})



SET(OBJOUTPUT_SRC OBJOutputPlugin.C)
SET(OBJOUTPUT_PYTHON_SRC pyOBJOutputPlugin.C)

ADD_LIBRARY(objoutput SHARED ${OBJOUTPUT_SRC})
TARGET_LINK_LIBRARIES(objoutput meshpotato)
INSTALL(TARGETS objoutput DESTINATION lib)

ADD_LIBRARY(pyOBJOutputPlugin MODULE ${OBJOUTPUT_PYTHON_SRC})
SET_TARGET_PROPERTIES(pyOBJOutputPlugin PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(pyOBJOutputPlugin PROPERTIES SUFFIX ".so")
TARGET_LINK_LIBRARIES(pyOBJOutputPlugin meshpotato ${PLUGIN_LIBRARY_DIRS})
INSTALL(TARGETS pyOBJOutputPlugin DESTINATION pymeshpotato)
