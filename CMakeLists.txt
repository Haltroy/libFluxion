cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Fluxion)

add_library(Fluxion SHARED
            src/Fluxion.cpp
            src/FluxionNode.cpp
            src/DataValues.cpp)

add_library(Fluxion::library ALIAS Fluxion)

target_include_directories(Fluxion PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(FluxionExample src/main.cpp)

target_link_libraries(FluxionExample PRIVATE Fluxion::library)

file(GLOB_RECURSE HEADER_FILES include/shared/*.h)

install(FILES build/libFluxion.so DESTINATION lib/)

foreach(HEADER_FILE ${HEADER_FILES})
    install(FILES ${HEADER_FILE} DESTINATION include/)
endforeach()
