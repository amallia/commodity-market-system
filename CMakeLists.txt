cmake_minimum_required(VERSION 2.8)
project(CMS)
# c++03 specified since compiled with gcc 6.1.0 (requirements are no c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

# Extensive warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-missing-braces")

set(CMS_INCLUDE_DIR "${CMS_SOURCE_DIR}/include")
set(CMS_LIB_DIR "${CMS_SOURCE_DIR}/lib")
file(GLOB CMS_SRC_DIR src/*.cpp)
list(REMOVE_ITEM CMS_SRC_DIR "${CMS_SOURCE_DIR}/src/cms.cpp")

find_package(Boost 1.54.0 COMPONENTS system thread unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${CMS_INCLUDE_DIR})
include_directories(${CMS_LIB_DIR})

include_directories(${CMS_SOURCE_DIR})

add_executable(cms src/cms.cpp ${CMS_SRC_DIR})
target_link_libraries(cms
        ${Boost_LIBRARIES}
        )
enable_testing()
add_subdirectory(test)

