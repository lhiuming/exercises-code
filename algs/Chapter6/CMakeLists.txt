# Build Programs for Chapter 6

# Collision System
add_library(CollisionSystem  CollisionSystem.cpp CollisionSystem.h)

# Collistion Simulating App
add_executable(CollisionSimulation.app collision_simulation_app.cpp)
target_link_libraries(CollisionSimulation.app CollisionSystem)
