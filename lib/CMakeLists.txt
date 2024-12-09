
target_sources (${PROJECT_NAME} PRIVATE
    lib/buffer.cpp
    lib/register.cpp
)

target_include_directories (${PROJECT_NAME} PUBLIC
    lib
)
