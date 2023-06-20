cmake_minimum_required(VERSION 3.25)
project(chessbot)

set(CMAKE_CXX_STANDARD 17)
include_directories(headers C:/sfml/SFML-2.5.1/include)

add_executable(chessbot main.cpp)

set(SFML_ROOT C:/sfml/SFML-2.5.1)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(chessbot ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()