#!/bin/bash

GAME_EXECUTABLE="./cub3D"
MAPS_DIRECTORY="maps"
MAP_PATH=""
EXIT_CODE=0

choose_map() {
    echo "Available maps:"
    select map_file in $(ls "$MAPS_DIRECTORY"); do
        if [ -n "$map_file" ]; then
            echo "You selected the map: $map_file"
            MAP_PATH="$MAPS_DIRECTORY/$map_file"
            break
        else
            echo "Invalid selection. Please try again."
        fi
    done
    echo "$MAP_PATH"
}

compile_game() {
    echo "Compiling the game..."
    make
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Exiting."
        exit 1
    fi
    echo "Compilation successful."
}

main() {
    compile_game

    while true; do
        choose_map
        echo "Starting the game with the selected map: $MAP_PATH"
        $GAME_EXECUTABLE "$MAP_PATH"
        EXIT_CODE=$?

        if [ $EXIT_CODE -ne 42 ]; then
            echo "Game has terminated with exit code: $EXIT_CODE"
            break
        fi
    done

    echo "Game has completely terminated."
}

main
