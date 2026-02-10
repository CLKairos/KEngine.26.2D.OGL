project(npc)

add_library(${PROJECT_NAME} STATIC npc.cpp
                                   speech.cpp)
add_library(${KENGINE_LIBRARY_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/kengine/${PROJECT_NAME})
