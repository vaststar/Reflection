add_definitions(-DPLUGINMANAGER_LIB )
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/thirdparty)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC)


file(GLOB_RECURSE HEAD_RES "include/*.h")
source_group("include" FILES ${HEAD_RES})

add_library(PluginManager SHARED  ${SRC} ${HEAD_RES})
target_link_libraries(PluginManager ${PROJECT_SOURCE_DIR}/lib/ReflectCore.lib ${PROJECT_SOURCE_DIR}/lib/PluginCore.lib)

install(FILES ${HEAD_RES} DESTINATION ${PROJECT_SOURCE_DIR}/include/PluginManager)
install(TARGETS PluginManager  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
		LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
		ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)