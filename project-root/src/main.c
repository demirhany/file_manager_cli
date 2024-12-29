#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

#define MAX_INPUT_SIZE 256

// print commands that user can use
void print_help() {
    printf("File Manager\n");
    printf("Available commands:\n\n");
    printf("File:\n");
    printf("-----------------------\n");
    printf("  fdisplay <path>                 - See the content of given file\n");
    printf("  fcopy <source> <destination>    - Copy a file to desired directory\n");
    printf("  fmove <source> <destination>    - Move (rename) a file\n");
    printf("  fcreate <path>                  - Create a file in desired directory\n");
    printf("  fstat <path>                    - Get the information of given file\n");
    printf("  fdelete <path>                  - Delete a file in desired directory\n");
    printf("  fsearch <path> <file_name>      -Search for a file in desired directory\n");
    printf("-----------------------\n\n");
    printf("Directory:\n");
    printf("-----------------------\n");
    printf("  dlist <path>                    - List the files in given directory\n");
    printf("  ddelete <path>                  - Delete given directory\n");
    printf("  dcreate <path>                  - Create given directory\n");
    printf("-----------------------\n\n");
    printf("Permissions:\n");
    printf("-----------------------\n");
    printf("  fdchmod <path> <permissions>    - Change file/folder permissions\n");
    printf("-----------------------\n\n");
    printf("  --help                          - Display help message\n");
    printf("  exit                            - Exit\n");
}

int main() {
    initialize_logger("../logs/file_manager.log");
    log_info("Program is running...");	

    char input[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];
    char arg1[MAX_INPUT_SIZE];
    char arg2[MAX_INPUT_SIZE];

    printf("WELCOME!\n\n");
    print_help(); // print "help" at the beginning of program

    while (1) {
        printf("\n> ");

	// read input from console
        if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
	    log_error("Failed to read input from console");
            perror("Error reading input");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        // input parsing from 'input' using sscanf  
        int args = sscanf(input, "%s %s %s", command, arg1, arg2);

	// check if input type is valid.
        if (args < 1) {
            printf("Invalid input. '--help' for the list of commands.\n");
            continue;
        }

	// call functions with respect to command that the user enters
        if (strcmp(command, "dlist") == 0 && args == 2) {
            list_directory(arg1); // ls
        } else if (strcmp(command, "fcopy") == 0 && args == 3) {
            copy_file(arg1, arg2); // cp
        } else if (strcmp(command, "fstatus") == 0 && args == 2) {
            get_file_info(arg1); // stat
	} else if (strcmp(command, "fdisplay") == 0 && args == 2) {
    	    display_file(arg1); // cat
        } else if (strcmp(command, "fmove") == 0 && args == 3) {
            move_file(arg1, arg2); // mv
        } else if (strcmp(command, "fsearch") == 0 && args == 3) {
            search_in_folder(arg1, arg2); // search 
        } else if (strcmp(command, "fcreate") == 0 && args == 2) {
            create_file(arg1); // touch
        } else if (strcmp(command, "fdelete") == 0 && args == 2) {
            delete_file(arg1); // rm
        } else if (strcmp(command, "ddelete") == 0 && args == 2) {
            delete_folder(arg1); // rm -rf
        } else if (strcmp(command, "dcreate") == 0 && args == 2) {
            create_folder(arg1); // mkdir
        } else if (strcmp(command, "fdchmod") == 0 && args == 3) {
            change_permissions(arg1, arg2); // chmod
        } else if (strcmp(command, "--help") == 0) {
            print_help();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting the program...\n");
	    log_info("Program is terminated!");
	    close_logger();
            break;
        } else {
            printf("Invalid command. '--help' for the list of commands.\n");
        }
    }

    return 0;
}

