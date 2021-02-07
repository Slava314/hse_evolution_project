# hse_evolution_project

# Инструкция по установке:

- Ubuntu
    - `sudo apt update`
    - `sudo apt install libsfml-dev`
    - add to cmake `find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)`
    - add to cmake `target_link_libraries(${PROJECT_NAME} sfml-graphics)`
- Mac
    - `brew update`
    - `brew install sfml`
    - add to cmake `find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)`
    - add to cmake `target_link_libraries(${PROJECT_NAME} sfml-graphics)`