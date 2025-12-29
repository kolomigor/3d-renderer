add_executable(renderer
    main.cpp
    ../external/glad/src/glad.c
)

# Include directories
target_include_directories(renderer PRIVATE
    ../include
    ../external/glad/include
)

# GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(renderer PRIVATE glfw)