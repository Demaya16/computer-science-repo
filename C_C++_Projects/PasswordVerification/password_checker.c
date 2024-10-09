#include <assert.h>
#include <string.h>
#include "password_checker.h"
/*
Password checker
Requirements:
- Password must be at least 10 characters
- Password must contain at least
- 1 upper case letter
- 1 lower case letter
- 1 number
*/
/* Returns true if the length of PASSWORD is at least 10, false otherwise */
bool check_length(const char *password);
bool check_upper(const char *password);
bool check_lower(const char *password);
bool check_number(const char *password);
bool check_name(const char *first_name, const char *last_name, const char *password);
bool check_range(char letter, char lower, char upper);
//needed to add to the top in order to successfully declare before being used




bool check_length(const char *password) {
int length = strlen(password);
bool meets_len_req = (length >= 10);//changed the sign on the function 
return meets_len_req;
}
/* Returns true if PASSWORD contains at least one upper case letter, false
otherwise */
bool check_upper(const char *password) {
while (*password != '\0') {
bool is_in_range = check_range(*password, 'A', 'Z');
if (is_in_range) {
return true;
}
++password;
}
return false;
}
/* Returns true if PASSWORD contains at least one lower case letter, false
otherwise */
bool check_lower(const char *password) {
while (*password != '\0') {
bool is_in_range = check_range(*password, 'a', 'z');
if (is_in_range) {
return true;
}
++password;
}
return false;
}



/* Returns true if LETTER is in the range [LOWER, UPPER], false otherwise */
bool check_range(char letter, char lower, char upper) {
//Need fix check_range used wrong logic (letter > lower && letter < upper), which would not include the boundary characters lower and upper.
// fix was to use >= and <= in check_range which  checks if a letter is within the range inclusive of the lower and upper bounds.
return letter >= lower && letter <= upper;
//bool is_in_range = (letter > lower && letter < upper);
//return is_in_range;
}






/* Returns true if PASSWORD contains at least one number, false otherwise */
bool check_number(const char *password) {

//check_number function contained an infinite loop and an attempt to check the value at password+200 which was beyond the bounds of typical password lengths and  also used the check_range function incorrectly.
//The updated code iterates through each character in the password string and  checks if the char is between '0' and '9'.
while (*password != '\0') {
        if (*password >= '0' && *password <= '9') {
		return true;
}
++password;
}
return false;
}
/* Returns true if the person's first and last name are NOT in the password, false
otherwise */
bool check_name(const char *first_name, const char *last_name, const char
*password) {
const char *first = strstr(password, first_name);
const char *last = strstr(password, last_name);
return (!first && !last);
}
/* Returns true if PASSWORD meets the conditions specified above */
bool check_password(const char *first_name, const char *last_name, const char
*password) {

//original code contained an assert(lower) statement within the check_password function. This assertion would terminate the program if the password didn't contain a lowercase letter thus needing to be fixed.
//The updated code removes the assertion
    bool length = check_length(password);
    bool upper = check_upper(password);
    bool lower = check_lower(password);
    bool number = check_number(password);
    bool name = check_name(first_name, last_name, password);
return (lower && length && name && upper && number);
}
