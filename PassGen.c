#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
// hai <3 :) xD
#define DEFAULT_LENGTH_MAX 32 // Arbitrary number, feel free to change the max range :)
#define DEFAULT_LEN_MIN 8 // Arbitrary number, feel free to change the min range :)
#define INIT_PASS_LENGTH (srand((unsigned int)time(NULL)), (rand() % (DEFAULT_LENGTH_MAX - DEFAULT_LEN_MIN + 1)) + DEFAULT_LEN_MIN) //I mean, this way - if they don't specify, it won't be 10 every time ~ 0 as the seed.
/* ~+ srand() already been initialized, so no need to have that anywhere else <3 :) xD
//+=============================================================================================================================+
//|   Developed by ya boi 3XPL017_N4T0 of course ;)                                                                             |
//|   Was bored, and thought I could develop something better. This is a better version of my other pass gen in C <3            |
//|   Took longer, than all the other projects on my github, but I thought this was something other people might like to use <3 |
//+=============================================================================================================================+
*/
void generate_password(char* password, size_t password_length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    size_t charset_length = strlen(charset);
    for (size_t i = 0; i < password_length; i++) /*GeN BaBy GeN*/ password[i] = charset[rand() % charset_length];
    password[password_length] = '\0'; // It's okay to be overkill <3 #N4T0
}

int main(int argc, char* argv[]) {
    size_t password_length = INIT_PASS_LENGTH;

    printf("Enter password length (press ENTER for random length): ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    if (!(strcmp(input, "\n") == 0 || atoi(input) <= 0)) /*then*/ password_length = atoi(input); // Generate password as normal, with specified length <3 ~ Nato
    char password[password_length];
    generate_password(password, password_length);
    printf("Generated password: \n\n%s\n\n", password);

    FILE* file;
    char file_name[256];
    char extension[] = ".txt";
    printf("Enter file name to save password (password.txt): ");
    while (fgets(file_name, sizeof(file_name), stdin) == NULL || strchr(file_name, '\n') == NULL) {} // Read user input ~ makin' sure it's not null, and the second condition is to check for 'NULL' to catch any prollems
    size_t len = strlen(file_name);
    if (len > 0 && file_name[len-1] == '\n') /*then*/ file_name[len-1] = '\0'; // Null terminator ~ no trailing naughty naughties
    if (strlen(file_name) > 0) {
        if (strstr(file_name, extension) == NULL) /*then*/ strcat(file_name, extension); // Append ".txt" if not already present in the filename
    } else {
        strcpy(file_name, "password");
        strcat(file_name, extension);
    }

    if ((file = fopen(file_name, "w")) == NULL || fprintf(file, "%s", password) < 0 || fclose(file) != 0) { // Check for prollems xD
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    memset(password, 0, sizeof(password)); // Clear password from memory <3 :)
    printf("Password saved to file: %s\n\nPress Enter To Exit.", file_name);
    memset(file_name, 0, sizeof(file_name)); // Clear filename from memory <3 :)
    getchar(); // Makes sure the person has the ability to copy & paste the password, before they exit - as well as double check what they saved the file as.
    return 0;
}
