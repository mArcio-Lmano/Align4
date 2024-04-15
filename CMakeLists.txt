cmake_minimum_required(VERSION 3.10)
project(AlignFour)
set(CMAKE_C_STANDARD 11)

# Add your source files here
set(SOURCE_FILES 
    src/main.c
    src/ai.c
    src/gameboard.c
)

set (HEADER_FILES
    src/include/ai.h
    src/include/gameboard.h
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
# Add any header files if necessary
# set(HEADER_FILES
#     include/header1.h
#     include/header2.h
# )

# Include directories
# include_directories(include)

# Add executable target
