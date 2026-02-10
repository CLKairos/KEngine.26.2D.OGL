cmake_minimum_required(VERSION 3.10)

#Engine root target name

set(KENGINE_TARGET ${KENGINE_LIBRARY_NAME})

add_subdirectory(audio)
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(npc)
add_subdirectory(physics2d)
add_subdirectory(components)
add_subdirectory(systems)
add_subdirectory(topdown)

add_library(${KENGINE_TARGET} STATIC
application.cpp
game.cpp
component_list.cpp
)

add_library(${KENGINE_LIBRARY_NAME}::${KENGINE_TARGET} ALIAS ${KENGINE_TARGET})

target_link_libraries(${KENGINE_TARGET} PUBLIC
${KENGINE_LIBRARY_NAME}::components
${KENGINE_LIBRARY_NAME}::systems
${KENGINE_LIBRARY_NAME}::audio
${KENGINE_LIBRARY_NAME}::core
${KENGINE_LIBRARY_NAME}::graphics
${KENGINE_LIBRARY_NAME}::npc
${KENGINE_LIBRARY_NAME}::physics2d
${KENGINE_LIBRARY_NAME}::topdown
OpenGL::GL
${GLAD_LIBRARIES}
${SDL2_LIBRARIES}
${ENTT_LIBRARIES}
${FREETYPE_LIBRARIES}
${LUA_LIBRARIES}
${PLATFORM_LIBRARIES}
)

#Prefer including the top-level include/ folder.
#If you renamed include/kengine to include/kengine, this just works.

target_include_directories(${KENGINE_TARGET} PUBLIC
${PROJECT_SOURCE_DIR}/include
)