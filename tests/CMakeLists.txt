set(BINARIES ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

add_executable(${BINARIES} ${TEST_SOURCES} Transport_utils-test.cpp)#Application_layer-test.cpp Transport_layer-test.cpp)
add_test(NAME command_Test COMMAND ${BINARIES})
target_link_libraries(${BINARIES} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)


set(BINARY Application_layer_Tests)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Application_layer-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Application_layer-test.cpp)
add_test(NAME Command_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

set(BINARY Transport_layer_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Transport_layer-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Transport_layer-test.cpp)
add_test(NAME Transport_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

set(BINARY Transport_utils_Test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false Transport_utils-test.cpp main.cpp)
add_executable(${BINARY} ${TEST_SOURCES} Transport_utils-test.cpp)
add_test(NAME Transport_utils_Test COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
