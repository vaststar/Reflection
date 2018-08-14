add_definitions(-DPLUGINCORE_LIB )
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC)


file(GLOB_RECURSE HEAD_RES "include/*.h")
source_group("include" FILES ${HEAD_RES})

add_library(PluginCore SHARED  ${SRC} ${HEAD_RES})
target_link_libraries(PluginCore ${PROJECT_SOURCE_DIR}/lib/ReflectCore.lib)

install(FILES ${HEAD_RES} DESTINATION ${PROJECT_SOURCE_DIR}/include/PluginCore)
install(TARGETS PluginCore  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
		LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
		ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)