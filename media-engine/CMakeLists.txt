find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

add_executable(
    media-engine
    src/main.cpp
    src/server.cpp
)

target_include_directories(
    media-engine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    media-engine
    PRIVATE
    Boost::system
    Threads::Threads
)