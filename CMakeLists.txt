cmake_minimum_required(VERSION 3.10)
project(AlignFour)
set(CMAKE_C_STANDARD 11)

# Add your source files here
set(COMMON_FILES 
    src/ai.c
    src/gameboard.c
)

set(MAIN_FILES
    src/main.c
)

set(TEST_FILES
    test/test_main.c
    test/test_ai.c
    test/test_gameboard.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/include
)

find_library(CUNIT_LIB cunit)
include_directories(${CMAKE_SOURCE_DIR}/src/include ${CUNIT_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECT_NAME} ${MAIN_FILES} ${COMMON_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

ADD_EXECUTABLE(tests ${TEST_FILES} ${COMMON_FILES})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(tests ${CUNIT_LIB})
