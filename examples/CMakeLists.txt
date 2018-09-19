
add_subdirectory(basic)
add_subdirectory(file)
add_subdirectory(multithreaded)
if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    add_subdirectory(android)
endif()
