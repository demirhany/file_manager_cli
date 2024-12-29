#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "permissions.h"
#include "logger.h"

void change_permissions(const char *path, const char *permissions) {
	mode_t mode = strtol(permissions, NULL, 0); // convert char *permissions into mode_t type which is used in chmod system call

	if (mode == 0 && permissions[0] != '0') {  // check for error
		log_error("Invalid permissions");
        	printf("Invalid permissions: %s\n", permissions);
        	return;
    	}

	if(chmod(path, mode) == -1) { // change permissions and check for error
		log_error("Failed to change permissions, System Call: chmod()");
		perror("Error while changing the permissons");
		return;
	}

	log_info("Operation: Change Permissions, System Calls: chmod(), Result: Success!");
	printf("Permissons for %s changed to %s.\n", path, permissions);
}

