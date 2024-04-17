cmake_minimum_required(VERSION 3.27)

project(2023-project-LoweegeeBelgium)

set(CMAKE_CXX_STANDARD 14)

include_directories(${SFML_INCLUDE_DIR} logic)

add_executable(2023-project-LoweegeeBelgium
        main.cpp
        Game_logic/World.h
        Game_logic/World.cpp
        Game_logic/Entities/Wall/Wall.h
        Game_logic/Entities/Wall/Wall.cpp
        Game_logic/Entities/PacMan/PacMan.h
        Game_logic/Entities/PacMan/PacMan.cpp
        Game_logic/Entities/Ghost/Ghost.h
        Game_logic/Entities/Ghost/Ghost.cpp
        Game_logic/Entities/Collectable/Collectable.h
        Game_logic/Entities/Collectable/Collectable.cpp
        Game_logic/Entities/EntityModel.h
        Game_logic/Entities/EntityModel.cpp
        Game_representation/Concrete_factory/EntityFactory.h
        Game_representation/Concrete_factory/EntityFactory.cpp
        Game_representation/Entities/EntityView.h
        Game_representation/Entities/EntityView.cpp
        Game_logic/Utils/Stopwatch.h
        Game_logic/Utils/Random.h
        Game_logic/Utils/Position.h
        Game_logic/Observer/Observer.h
        Game_representation/Game.h
        Game_representation/Game.cpp
        Game_representation/Entities/Ghost/Ghost_v.h
        Game_representation/Entities/Ghost/Ghost_v.cpp
        Game_representation/Entities/Collectale/Collectable_v.h
        Game_representation/Entities/Collectale/Collectable_v.cpp
        Game_representation/Entities/PacMan/PacMan_v.h
        Game_representation/Entities/PacMan/PacMan_v.cpp
        Game_representation/Entities/Wall/Wall_v.h
        Game_representation/Entities/Wall/Wall_v.cpp
        Game_logic/AbstractFactory/AbstractFactory.h
        Game_representation/Camera/Camera.h
        Game_logic/Utils/Utils.h
        Game_logic/Utils/Utils.cpp
        Game_logic/Ghost_AI/Ghost_AI.h
        Game_logic/Entities/PacMan/PacmanMovement.h
        Game_logic/Score/Score.h
        Game_logic/Score/Score.cpp
        Game_logic/Entities/PacMan/PacmanMovement.cpp
        Game_logic/Ghost_AI/Ghost_AI.cpp
        Game_representation/Utils/Window.h
        Game_logic/Entities/VoidCell/VoidCell.h
        Game_logic/Entities/VoidCell/VoidCell.cpp
        Game_representation/Entities/VoidCell/VoidCell_v.h
        Game_representation/Entities/VoidCell/VoidCell_v.cpp
        Game_representation/States/States.h
        Game_representation/States/States.cpp
        Game_representation/StateManager/StateManager.cpp)

TARGET_LINK_LIBRARIES(2023-project-LoweegeeBelgium sfml-system sfml-graphics sfml-window)

INSTALL(TARGETS 2023-project-LoweegeeBelgium DESTINATION bin)