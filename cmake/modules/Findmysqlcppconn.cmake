# ---- Find MySQL C++ connector ----------------
message("${yellow}Looking for MySQL C++ connector...${reset}")
find_path(mysqlcppconn_INCLUDE mysql_devapi.h
          PATHS 
          "${PROJECT_SOURCE_DIR}/dependency/mysql-connector-cpp/include"
          "/usr/include"
          "/usr/local/include"
          "/opt/local/include"
          )

find_library(mysqlcppconn_LIBRARY mysqlcppconn8
             HINTS
             "${PROJECT_SOURCE_DIR}/../build/dependency/mysql-cpp-connector/build"
             "/usr/local/lib"
             "/opt/local/lib"
             )

# ---- Verify we found the dependency ----------
if (mysqlcppconn_INCLUDE)
    message(STATUS "${green}Found MySQL C++ connector include files at: ${mysqlcppconn_INCLUDE}${reset}")
else()
    message(FATAL_ERROR "${red}Failed to locate MySQL C++ connector include files.${reset}")    
endif()

if (mysqlcppconn_LIBRARY)
   message(STATUS "${green}Found MySQL C++ connector library at: ${mysqlcppconn_LIBRARY}${reset}")
endif()

if (mysqlcppconn_LIBRARY)
    set(LIBMYSQLPPCONN_FOUND TRUE)
endif()

if (mysqlcppconn_INCLUDE)
    set(MYSQLPPCONN_FOUND TRUE)
endif()
