set(BINARIES ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

add_executable(${BINARIES} ${TEST_SOURCES} Transport_utils-test.cpp Serial_fake-test.cpp)
add_test(NAME command_Test COMMAND ${BINARIES})
target_link_libraries(${BINARIES} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

#[[
set(BINARY Application_layer_Tests)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Application_layer-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Application_layer-test.cpp)
add_test(NAME Application_layer_Tests COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
]]
#[[
set(BINARY Application_utils_Tests)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Application_utils-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Application_utils-test.cpp)
add_test(NAME Application_utils_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
]]

set(BINARY Transport_layer_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Transport_layer-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Transport_layer-test.cpp)
add_test(NAME Transport_layer_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

set(BINARY Transport_utils_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Transport_utils-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Transport_utils-test.cpp)
add_test(NAME Transport_utils_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

set(BINARY Serial_fake_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Serial_fake-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Serial_fake-test.cpp)
add_test(NAME Serial_fake_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

set(BINARY Astronode_command_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Astronode_command-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Astronode_command-test.cpp)
add_test(NAME Astronode_command_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)