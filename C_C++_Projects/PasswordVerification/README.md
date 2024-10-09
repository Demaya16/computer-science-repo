#  Password Checker README

## Description

The Password Checker is a C application designed to validate passwords based on specific requirements. It checks for minimum length, if there are uppercase and lowercase letters, numerical digits, and if the password contains the user's first or last name. These requirements are set in place to ensure that users create strong and secure passwords.
the assignment conssissted of making sure the password_checker.c file was passing the given test cases correctly. 
## Author

- Devin Maya
- Email: demaya@ucsc.edu
- Assignment Password Checker

## File Names and What They Do

- `password_checker.c`: The main source file containing all the password validation logic and code that has been updated to satisy the requirements.
- `password_checker.h`: The header file with function declarations for the password checker.
- `test_password_checker.c`: Contains a suite of test cases for verifying the correctness of the password checker functions.
- `.gitignore`: Specifies files that Git should ignore.
- `Makefile`: Addresses the compilation process and uses the test cases provided.
- `README.md`: Provides detailed information about the Password Checker and all of asignment 3 files.

## Compilation Process and How to Run Tests

To compile the Password Checker and run the tests you need to run 

make        # Compiles the password checker and test suite.
make test   # Runs the compiled test suite to validate functionality.
after running make just input ./password_checker

## Changes made 
Fixing the Length Check Logic:

Originally, the check_length function incorrectly used <= 10, which meant it would return true for passwords that were less than or equal to 10 characters opposite to the requirement.
The change corrected the logic to >= 10 to ensure that the password must be at least 10 characters long.

Function Declaration Order:

Initially, the check_range function was implicitly declared because it was used before being defined. This led to a warning and potential undefined behavior.
The final code includes the function for check_range at the top of the file so that the function is properly declared before being used.

Correcting the Range Check Logic:

In the original code, check_range used incorrect logic (letter > lower && letter < upper), which would not include the boundary characters lower and upper.
The change was to use >= and <= in check_range which  checks if a letter is within the range inclusive of the lower and upper bounds.

Eliminating Potentially Undefined Behavior in check_number:

The original check_number function contained an infinite loop and an attempt to check the value at password+200, which was beyond the bounds of accepted password lengths but also used the check_range function incorrectly.
The updated code iterates through each character in the password string and  checks if the character is between '0' and '9'.

Removing Assertion from check_password:

The original code contained an assert(lower) statement within the check_password function. This assertion would terminate the program if the password didn't contain a lowercase letter which was not the needed requirement.
The updated code removes the assertion.


Reordering Checks in check_password:

Originally check_password was making checks in the wrong order that didn't match the overall return statement. Thus fixed the order of variable assignment in check_password so that it is consistent with the order of conditions in the return statement.


Improving Function Comments:

Comments were updated or added where necessary to more accurately describe the functions behaviors and the changes made.
