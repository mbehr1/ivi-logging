INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

add_executable( logging-android
    exampleLoggingAndroid.cpp
)

TARGET_LINK_LIBRARIES( logging-android
    ${LIB_NAME}
    log
)

install(TARGETS logging-android
        DESTINATION ${CMAKE_INSTALL_BINDIR})
