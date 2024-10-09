# Coolness Calculation README

## Description

The Coolness program is a C application designed to calculate "coolness" as a function of wind speed and temperature according to a specific formula. The formula used for this calculation is \( coolness = 35.74 + 0.6215 \times T - 35.75 \times V^{0.16} + 0.4275 \times T \times V^{0.16} \), where \( T \) represents the temperature and \( V \) the wind speed. The program is capable of handling different scenarios including zero, one, or two command-line arguments, providing flexibility for the user's inputs.

## Author

- Devin Maya
- Email: demaya@ucsc.edu
- Assignment: Coolness

## File Names and What They Do

- `coolness.c`: The main source file containing the logic for the coolness calculation.
- `.gitignore`: File specifying which files and directories Git should ignore.
- `testing.sh`: A shell script used for testing the Coolness program, ensuring that it functions correctly for a variety of inputs.
- `testing.out`: Contains the output of the test cases run by the `testing.sh` script.
- `Makefile`: A makefile to simplify the compilation process.
- `README.md`: The file you are currently reading, providing a comprehensive overview of the Coolness program.

## Compilation Process and How to Run It

To compile the Coolness program, open a terminal in the project directory and run:

make


This will generate the executable `coolness`. To run the program, use:

./coolness [temperature] [wind speed]

Replace `[temperature]` and `[wind speed]` with the desired numeric values. The program will then calculate and display the coolness based on the provided input.

## Input

- **No Arguments**: The program calculates coolness for a range of temperatures and wind speeds.
- **One Argument**: The single argument represents the temperature. The program calculates coolness for this temperature and a range of wind speeds.
- **Two Arguments**: The first argument is the temperature and the second is the wind speed. The program calculates and displays a single coolness value.

## Output

- A table of coolness values based on the input parameters, formatted neatly with tabs and rounded numbers.

## Exit Status

- The program exits with a status of 0 if it completes successfully.
- If an error occurs (such as invalid input values), the program exits with a status of 1.

## Testing

Run the provided `testing.sh` script using:


bash -v testing.sh >& testing.out

This script includes various test cases designed to verify the functionality of the Coolness program and ensure it handles different types of input correctly.

## Compilation

The included `Makefile` facilitates the compilation process and links the necessary math library. 

##  How to Run it
To compile the coolness calculator, open a terminal in the project directory and run:
make
then input in the terminal:
./coolness "user inputs"
Then hit enter and the output should follow.
Here user inputs should be replaced with the acceptable range values. The user can run your program with zero, one, or two command line arguments. In the event that arguments are passed, T will always be the first argument, and V always the second. If only one argument is passed, it is T. Ensure that any passed arguments are within the acceptable values: -99 <= T <= 50 and 0.5 <= V if you want the program to run correctly.

