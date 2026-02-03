cmake_minimum_required(VERSION 4.2)
project(SimpleCDL C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_SUPPRESS_REGENERATION true)

add_executable(
${PROJECT_NAME}
  src/main.c
  src/matrix.c
  src/nn.c
)

include_directories(include)
link_directories(lib)

if (APPLE)
  target_link_libraries(
  ${PROJECT_NAME}

  )
elseif (WIN32)
  target_link_libraries(
  ${PROJECT_NAME}

  )
else ()
  target_link_libraries(
  ${PROJECT_NAME}
  m
  )
  target_include_directories(${PROJECT_NAME} PRIVATE)
endif ()

