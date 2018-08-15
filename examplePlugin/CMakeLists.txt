add_definitions(-DEXAMPLEPLUGIN_LIB )
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC)


file(GLOB_RECURSE HEAD_RES "include/*.h")
source_group("include" FILES ${HEAD_RES})

add_library(examplePlugin SHARED  ${SRC} ${HEAD_RES})
target_link_libraries(examplePlugin ${PROJECT_SOURCE_DIR}/lib/PluginCore.lib ${PROJECT_SOURCE_DIR}/lib/ReflectCore.lib)

install(FILES ${HEAD_RES} DESTINATION ${PROJECT_SOURCE_DIR}/include/examplePlugin)
install(TARGETS examplePlugin  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/Plugins
		)