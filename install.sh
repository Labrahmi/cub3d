#!/bin/bash

echo -e "\033[0;32m-----------------------------------------------"
echo -e "This script requires Homebrew to be installed!"
echo -e "-----------------------------------------------\033[0m"

# Ask the user if they have the packages installed
read -p "Do you already have 'cmake' and 'glfw' installed? (y/n): " response

if [[ "$response" != "y" && "$response" != "Y" ]]; then
    # Loading effect of 3 dots being written and then erased
    for i in {1..3}; do
        for j in {1..3}; do
            echo -n "."
            sleep 0.5
        done

        # Erase dots with backspaces
        echo -ne "\b\b\b   \b\b\b"
        sleep 0.5
    done

    # Executing brew install commands
    brew install cmake
    brew install glfw
else
    echo "Skipping installation."
fi

git clone https://github.com/codam-coding-college/MLX42.git ~/goinfre/MLX42;
cd ~/goinfre/MLX42;
cmake -B build;
make -C build -j4;