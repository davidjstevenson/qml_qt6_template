
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # qt has errors at /W4 that rules out /W4 and /WX
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX" PARENT_SCOPE)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall" PARENT_SCOPE)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall" PARENT_SCOPE)

endif()
