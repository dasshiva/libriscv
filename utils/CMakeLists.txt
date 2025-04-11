set(TGEN_SOURCES 
		"tablegen.cpp"
		"cfg/cfg_parse.c"
		"cfg/cfg_parse.h"
)

add_executable(tablegen ${TGEN_SOURCES})
add_custom_command(
	OUTPUT ${CMAKE_SOURCE_DIR}/include/generated.h
	COMMAND tablegen ${CMAKE_SOURCE_DIR}/include/generated.h 
		${CMAKE_SOURCE_DIR}/utils/tables.cfg
	DEPENDS tablegen ${CMAKE_SOURCE_DIR}/utils/tables.cfg
	COMMENT "Generating tables"
	VERBATIM
)

add_custom_target(
	GEN_HEADERS ALL
	DEPENDS ${CMAKE_SOURCE_DIR}/include/generated.h
)
