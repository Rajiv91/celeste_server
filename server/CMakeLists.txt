# ---- Set cmake minimum version ---------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

project(celeste_server VERSION 0.0.1 LANGUAGES CXX)
message("${gray}celeste_server v${PROJECT_VERSION} ${reset}")

message("${gray}This project uses the following dependencies:")
message("@ restbed")
message("@ MySQL C++ connector v8")
message("@ Boost property_tree")
message("@ nhlomann JSON")
message("@ object_pool")
message("${reset}")

# ---- Set the module path ---------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake/modules")

include_directories(".")

# ---- Configure compiler ----------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Sunspec ---------------------------------
file(GLOB_RECURSE SUNSPEC_SRC
    "sunspec/*.hpp"
    "sunspec/*.cpp"
    )
set(sunspec ${SUNSPEC_SRC})

# ---- Server ----------------------------------
file(GLOB_RECURSE SRV_SRC
    "srv/*.hpp"
    "srv/*.cpp"
    )
set(srv ${SRV_SRC})

# ---- Sunspec ---------------------------------
file(GLOB_RECURSE SUNSPEC_SRC
    "db/*.hpp"
    "db/*.cpp"
    )
set(db ${DB_SRC})

# ---- Mix all source files --------------------
set(SERVER_SOURCE_FILES 
        main.cpp
        ${sunspec}
        ${srv}
        ${tests}
    )

# ---- Find packages ---------------------------
find_package(restbed        REQUIRED)
find_package(mysqlcppconn   REQUIRED)
find_package(json           REQUIRED)
find_package(object_pool    REQUIRED)
find_package(Boost          REQUIRED
             COMPONENTS
             date_time)

include_directories(${mysqlcppconn_INCLUDE})
include_directories(${restbed_INCLUDE})
include_directories(${json_INCLUDE})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${object_pool_INCLUDE})

# ---- Add an executable -----------------------
add_executable(celeste_server ${SERVER_SOURCE_FILES})

# ---- Link executable -------------------------
if (NOT restbed_LIBRARY)
    add_subdirectory("dependency/restbed")
    target_link_libraries(celeste_server restbed)
else()
    target_link_libraries(celeste_server ${restbed_LIBRARY})
endif()

if (NOT mysqlcppconn_LIBRARY)
    add_subdirectory("dependency/mysql-connector-cpp/")
    target_link_libraries(celeste_server libconcpp )
else()
    target_link_libraries(celeste_server ${mysqlcppconn_LIBRARY})
endif()
target_link_libraries(celeste_server ${Boost_LIBRARIES})

# Add our own Sunspec library
add_library(sunspec SHARED ${sunspec})
set_target_properties(sunspec PROPERTIES LINKER_LANGUAGE CXX)
