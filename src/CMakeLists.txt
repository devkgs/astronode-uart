cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

project(astroUart)

set(BINARY ${CMAKE_PROJECT_NAME})

## src
#set(TEST_SRCS main.cpp RequestCommand-test.cpp RequestCommand-test.h Transport_layer.cpp Transport_layer.h)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

#add_executable(${BINARY}_run ${SOURCES})

#fake serial build
if (FAKE_SERIAL_BUILD STREQUAL 1)
    add_definitions(-DFAKE_SERIAL)
    add_executable(${BINARY}_fake_serial ${SOURCES} Serial_fake/Serial_fake.cpp Opcodes_id.h)

else()
    add_executable(${BINARY}_run ${SOURCES})
    ## Link Boost libraries
    set(BOOST_LIBS date_time system)
    find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
    target_link_libraries(${BINARY}_run ${Boost_LIBRARIES})
    find_package(Threads REQUIRED)
    target_link_libraries(${BINARY}_run ${CMAKE_THREAD_LIBS_INIT})
endif()


## Google test
add_library(${BINARY}_lib STATIC ${SOURCES} Application_layer.cpp Application_layer.h)