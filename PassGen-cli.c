#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
// hai <3 :) xD ~ Like CLI more? Can't blame ya :) ;) xD
#define DEFAULT_LENGTH_MAX 32 // Arbitrary number, feel free to change the max range :)
#define DEFAULT_LEN_MIN 8 // Arbitrary number, feel free to change the min range :)
#define INIT_PASS_LENGTH (srand((unsigned int)time(NULL)), (rand() % (DEFAULT_LENGTH_MAX - DEFAULT_LEN_MIN + 1)) + DEFAULT_LEN_MIN) //I mean, this way - if they don't specify, it won't be 10 every time.
/* ~+ srand() already been initialized, so no need to have that anywhere else <3 :) xD
//+=============================================================================================================================+
//|   Developed by ya boi 3XPL017_N4T0 of course ;)                                                                        |
//|   Was bored, and thought I could develop something better. This is a better version of my other pass gen in C <3            |
//|   Took longer, than all the other projects on my github, but I thought this was something other people might like to use <3 |
//+=============================================================================================================================+
*/
void generate_password(char* password, size_t password_length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    size_t charset_length = strlen(charset);
    for (size_t i = 0; i < password_length; i++) /*GeN BaBy GeN*/ password[i] = charset[rand() % charset_length]; // <3 ~ Nato :)
    password[password_length] = '\0'; // It's okay to be overkill <3 #N4T0
}

int main(int argc, char* argv[]) {
    size_t password_length = INIT_PASS_LENGTH;
    char file_name[256] = "password.txt";
    if (argc > 1) {
        password_length = atoi(argv[1]);
        if (password_length <= 0) /*then*/ password_length = rand() % DEFAULT_LENGTH_MAX + 1;
        if (argc > 2) {
            strncpy(file_name, argv[2], sizeof(file_name) - 1);
            file_name[sizeof(file_name) - 1] = '\0';
            if (strstr(file_name, ".txt") == NULL) /*then*/ strncat(file_name, ".txt", sizeof(file_name) - 1);
        }
    } // Basically, if they don't specify a length, or a filename - we do that for em <3

    char password[password_length + 1];
    generate_password(password, password_length);
    printf("Generated password:\n\n%s\n", password);
    FILE* file;
    if ((file = fopen(file_name, "w")) == NULL || fprintf(file, "%s", password) < 0 || fclose(file) != 0) { // Check for prollems xD
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    memset(password, 0, sizeof(password));  // Clear password from memory <3 :)
    printf("\nPassword saved to file: %s\r\n", file_name);
    memset(file_name, 0, sizeof(file_name)); // Clear filename from memory <3 :)
    return 0;
}
