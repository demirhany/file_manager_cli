#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "directory_ops.h"
#include "logger.h"

void list_directory(const char *path) {
	DIR *dir = opendir(path); // open the directory using system call opendir
	if(dir == NULL) { // check if directory can open
		log_error("Failed to open dir, System Call: opendir()");
		perror("Error opening directory");
		return;
	}

	struct dirent *entry; // create a dirent struct -> dir entry
	printf("Listing files in directory: %s\n", path);
	while((entry = readdir(dir)) != NULL) { // read every entry in the directory and print
		printf("%s\n", entry->d_name);
	}

	log_info("Operation: List Files In Directory, System Calls: opendir(), readdir(), closedir(), Result: Success!");

	closedir(dir); // close
}

void delete_folder(const char *path) {
	int rv = remove(path); // delete directory using system call remove and remove the directory
	if(rv == -1) { // check for error
		log_error("Failed to delete dir, System Call: remove()");
		perror("Error deleting directory");
	} else {
		log_info("Operation: Delete Folder, System Calls: remove(), Result: Success!");
		printf("Directory deleted successfully: %s\n", path);
	}
}

void create_folder(const char *path) { 
	int create = mkdir(path, 0644); // create directory using mkdir system call
	if(create == -1) { // check for error
		log_error("Failed to create dir, System Call: mkdir()");
		perror("Error creating folder");
	} else {
		log_info("Operation: Create Folder, System Calls: mkdir(), Result: Success!");
		printf("Folder created successfully: %s\n", path);
	}
}

void search_in_folder(const char *path, const char *file_name) {
	bool is_file_exist = false; // boolean to determine if file exists
	DIR *dir = opendir(path); // open the directory

	if(dir == NULL) { // check if directory can open
		log_error("Failed to open dir, System Call: opendir()");
		perror("Error opening directory");
		return;
	}
	
	struct dirent *entry; // a struct for directory entries

	while((entry = readdir(dir)) != NULL) { // read every entry in the directory and print
		if(strstr(entry->d_name, file_name)) { // check if the entry has the file_name which is given
                	printf("%s\n", entry->d_name); // print the entry
			is_file_exist = true; // make it true
		}
        }

	if(!is_file_exist) { // check if file exists or not
		printf("File -%s- doesn't exist", file_name);
	} else {
		log_info("Operation: Search In Folder, System Calls: opendir(), readdir(), Result: Success!");	
	}

	closedir(dir); // close the directory
}

