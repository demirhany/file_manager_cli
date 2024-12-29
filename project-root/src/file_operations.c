#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include "file_operations.h"
#include "logger.h"

void copy_file(const char *source, const char *destination) {
	int src_fd = open(source, O_RDONLY); // open source file as read only
	if(src_fd == -1) { // check for error while opening source file
		log_error("Failed to open source file, System Call: open()");
		perror("Error opening source file");
		return;
	}

	// the destination path is directory so get the file name from source path
	const char *file_name = strrchr(source, '/');
    	if (file_name != NULL) {
        	file_name++;
    	} else {
        	file_name = source;
    	}

	char full_destination[PATH_MAX];
    	snprintf(full_destination, PATH_MAX, "%s/%s", destination, file_name); // assign file name from source path into full_destination

	int dest_fd = open(full_destination, O_WRONLY | O_CREAT | O_TRUNC, 0644); // open full_destination path: file -> write only | if not exist create | if has content delete content
	if(dest_fd == -1) { // check for error while opening full_destination path
		log_error("Failed to open destination file, System Call: open()");
		perror("Error opening destination file");
		close(src_fd);
		return;
	}

	char buffer[1024]; // create buffer to read data from source file
	ssize_t bytesRead; // create ssize_t bytesRead

	while((bytesRead = read(src_fd, buffer, sizeof(buffer))) > 0) { // loop while data exists in the source file and read it
		if(write(dest_fd, buffer, bytesRead) == -1) { // write the buffer into destination and check if for error.
			log_error("Failed to write into destination file, System Call: write()");
			perror("Error writing to destination file");
			close(src_fd);
			close(dest_fd);
			return;
		}
	}

	if(bytesRead == -1) {
		log_error("Failed to read source file, System Call: read()");
		perror("Error reading source file");
	}

	close(src_fd);
	close(dest_fd);

	log_info("Operation: Copy File, System Calls: write(), read(), open(), Result: Success!");
	printf("File copied successfully!\n");
}

void move_file(const char *source, const char *destination) {
	if(rename(source, destination) == -1) { // move or rename the file with respect to source and destination paths
		log_error("Failed to move/rename file, System Call: rename()");
		perror("Error moving file");
	} else {
		log_info("Operation: Move/Rename File, System Calls: rename(), Result: Success!");
		printf("File moved successfully!\n");
	}
}

void get_file_info(const char *path) {
	struct stat file_status; // a struct for the desired file status
	if(stat(path, &file_status) == -1) { // get file status and check for error
		log_error("Failed to get status information of file, System Call: stat()");
		perror("Error getting innformation of the file");
		return;
	} 

	log_info("Operation: Get Information Of File, System Calls: stat(), Result: Success!");

	// print the informations
	printf("File Information For: %s\n", path); 
	printf("====================\n");
	printf("File size: %ld\n", file_status.st_size);
	printf("Block Numbers: %ld\n", file_status.st_blocks);
	printf("Block Size: %ld\n", file_status.st_blksize);
}

void create_file(const char *path) {
	int fd = creat(path, 0644); // create a file into desired path
	if(fd == -1) { // check for error
		log_error("Failed to create file, System Call: creat()");
		perror("Error creating file!\n");
	} else {
		log_info("Operation: Create File, System Calls: creat(), Result: Success!");
		printf("File successfully created: %s\n", path);
		close(fd);
	}
}

void delete_file(const char *path) {
	if(unlink(path) == -1) { // delete a file using unlink call and check for error
		log_error("Failed to delete file, System Call: unlink()");
		perror("Error deleting file!\n");
	} else {
		log_info("Operation: Delete File, System Calls: unlink(), Result: Success!");
		printf("File successfully deleted: %s\n", path);
	}
}
void display_file(const char *path) {
	int fd = open(path, O_RDONLY); // open the desired file as read only
	if(fd == -1) { // check for error while opening
		log_error("Failed to open file, System Call: open()");
		perror("Error opening file!\n");
		return;
	}

	char buffer[1024]; // create a buffer to store data from source file
	ssize_t bytesRead;

	while((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) { // read bytes from source file and keep it in buffer
		if(write(STDOUT_FILENO, buffer, bytesRead) == -1) { // write the buffer into console and check if for error
			log_error("Failed to write stdout, System Call: write()");
			perror("Error writing to stdout");
			close(fd);
			return;
		}
	}

	if(bytesRead == -1) {
		log_error("Failed to read file, System Call: read()");
		perror("Error reading the file!\n");
	}

	log_info("Operation: Display File, System Calls: open(), read(), write(), Result: Success!");
	close(fd);
}
