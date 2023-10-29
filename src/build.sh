#!/bin/bash
# Function to display usage instructions
function display_usage {
    echo "Usage: $0 <target>"
    echo "Targets:"
    echo "  all: Build the library (calc.a) and run tests"
    echo "  calc.a: Build the library (calc.a)"
    echo "  test: Run unit tests"
    echo "  gcov_report: Generate test coverage HTML report"
    echo "  codestyle: Apply Google code style to the project"
    echo "  run: Build and run the command line calculator"
}

# Check if the target is provided as an argument
if [ "$#" -ne 1 ]; then
    display_usage
    make all
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
    "gcov_report")
        # Generate test coverage HTML report
        make gcov_report
        ;;
    "codestyle")
        # Apply Google code style to the project
        make codestyle
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
