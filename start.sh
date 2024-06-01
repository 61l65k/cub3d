#!/bin/bash

GAME_EXECUTABLE="./cub3D"
MAPS_DIRECTORY="maps"
MAP_PATH=""
EXIT_CODE=0

choose_map() {
    echo "Available maps:"
    map_files=($(ls -1 "$MAPS_DIRECTORY"))

    # Print each map file on a new line
    for i in "${!map_files[@]}"; do
        echo "$((i + 1)). ${map_files[$i]}"
    done
    echo ""
    # Select a map
    while true; do
        read -p "Select a map by number: " selection
        if [[ $selection -gt 0 && $selection -le ${#map_files[@]} ]]; then
            map_file="${map_files[$((selection - 1))]}"
            echo "You selected the map: $map_file"
            MAP_PATH="$MAPS_DIRECTORY/$map_file"
            break
        else
            echo "Invalid selection. Please try again."
        fi
    done
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
    clear
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
