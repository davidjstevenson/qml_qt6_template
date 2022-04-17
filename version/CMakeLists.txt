
function(make_version_header TARGET)
    find_package(Git)

    if(Git_FOUND)
        execute_process(COMMAND
          "${GIT_EXECUTABLE}" describe --match=NOT_A_MATCH --always --abbrev=40 --dirty
          WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
          OUTPUT_VARIABLE GIT_SHA_DIRTY
          OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif()

    string(SUBSTRING "${GIT_SHA_DIRTY}" 0 40 GIT_SHA)

    target_include_directories(${TARGET} PRIVATE "${CMAKE_BINARY_DIR}/include")
    configure_file(
        "${CMAKE_SOURCE_DIR}/version/version.h.in"
        "${CMAKE_BINARY_DIR}/include/${TARGET}_version.h"
        ESCAPE_QUOTES
    )

endfunction()
