add_definitions(-DREFLECTCORE_LIB )
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC)


file(GLOB_RECURSE HEAD_RES "include/*.h")
source_group("include" FILES ${HEAD_RES})

add_library(ReflectCore SHARED  ${SRC} ${HEAD_RES})



install(FILES ${HEAD_RES} DESTINATION ${PROJECT_SOURCE_DIR}/include/ReflectCore)
install(TARGETS ReflectCore  
		RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
		LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
		ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)