project(systems)

add_library(${PROJECT_NAME} STATIC animation_player.cpp
                                   character_animation.cpp
                                   group.cpp
                                   npc.cpp
                                   physics.cpp
                                   render.cpp
                                   speech.cpp
                                   text.cpp
                                   tile.cpp
                                   timer.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${KENGINE_LIBRARY_NAME}::graphics)

add_library(${KENGINE_LIBRARY_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/kengine/${PROJECT_NAME})