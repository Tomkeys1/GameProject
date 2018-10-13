cmake_minimum_required(VERSION 3.10)

project(Game)
set(TARGET_NAME Game)

set(CMAKE_CXX_STANDARD 17)

find_program(FXC fxc DOC "fx compiler")
if(NOT FXC)
	message(SEND_ERROR "Cannot find fxc.")
endif(NOT FXC)

# define the include directories
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

# list include files to variables
file (GLOB_RECURSE ENGINE_INCLUDES
    LIST_DIRECTORIES false
    "includes/*.h"
)
file(GLOB CORE_SOURCE
    "src/*.cpp"
)

file(GLOB RES_FILES
	"res/*.ico"
	"res/*.rc"
)

file(GLOB_RECURSE SHADER_FILES
	"includes/shader*.hlsl"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${TARGET_NAME} ${CORE_SOURCE} ${ENGINE_INCLUDES} ${RES_FILES})
else()
    add_executable(${TARGET_NAME} WIN32 ${CORE_SOURCE} ${ENGINE_INCLUDES} ${RES_FILES})
endif()

set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX ".debug")

target_link_libraries(${TARGET_NAME} d3d11 dxgi d3dcompiler)

foreach(file ${SHADER_FILES})

	get_filename_component(filename ${file} NAME_WE)

	add_custom_command(
		TARGET ${TARGET_NAME}
		COMMAND ${FXC} /T vs_5_0 /E Default_VS /Fo ${CMAKE_SOURCE_DIR}/bin/data/shader/${filename}vs.shader ${CMAKE_SOURCE_DIR}/includes/shader/${filename}.hlsl
		COMMAND ${FXC} /T ps_5_0 /E Default_PS /Fo ${CMAKE_SOURCE_DIR}/bin/data/shader/${filename}ps.shader ${CMAKE_SOURCE_DIR}/includes/shader/${filename}.hlsl
		COMMENT "Effect: ${filename}"
		VERBATIM
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)

endforeach(file)
