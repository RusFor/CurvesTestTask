cmake_minimum_required(VERSION 3.11)

set(PROJECT_NAME curves)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(
        CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} /JMC"
    )
else()
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-implicit-fallthrough"
    )
endif()

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

add_executable(${PROJECT_NAME}
	main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CURVES_DLL_DIR}/lib/")

target_link_libraries(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/curve_dll/lib/CurveLibrary.lib")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/curve_dll/lib/CurveLibrary.dll 
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT curves)