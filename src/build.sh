#!/bin/bash
# Function to display usage instructions
function display_usage {
    echo "Usage: $0 <target>"
    echo "Targets:"
    echo "  all: Build the library (calc.a) and run tests"
    echo "  calc.a: Build the library (calc.a)"
    echo "  test: Run unit tests"
    echo "  codestyle: Apply Google code style to the project"
    echo "  clean: Clean build files"
    echo "  run: Build and run the command line calculator"
}

# Check if the target is provided as an argument
if [ "$#" -ne 1 ]; then
    display_usage
    exit 1
fi

# Check the target and execute the corresponding command
case "$1" in
    "all")
        # Build the library (calc.a) and run tests
        make all
        ;;
    "calc.a")
        # Build the library (calc.a)
        make calc.a
        ;;
    "test")
        # Run unit tests
        make test
        ;;
    "codestyle")
        # Apply Google code style to the project
        make codestyle
        ;;
    "clean")
        # Clean build files
        make clean
        ;;
    "run")
        # Build and run the command line calculator
        make run
        ;;
    *)
        echo "Invalid target: $1"
        display_usage
        exit 1
        ;;
esac
