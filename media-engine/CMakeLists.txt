add_executable(
    media-engine
    src/main.cpp
    src/stream_manager.cpp
)

target_include_directories(
    media-engine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
