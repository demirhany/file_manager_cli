#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "logger.h" 

static int log_fd;
void initialize_logger(const char *path) {
	log_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(log_fd == -1) {
		perror("Error opening log file");
		exit(EXIT_FAILURE);
	}
}

static void log_message(const char *level, const char *message) {
	if(log_fd == -1) {
		perror("Logger not initialized");
		return;
	}

	time_t now = time(NULL); // get current time
	struct tm *t = localtime(&now);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", t);

	char _log_message[1024];
	snprintf(_log_message, sizeof(_log_message), "[%s] [%s] %s\n", buffer, level, message);

	if(write(log_fd, _log_message, strlen(_log_message)) == -1) {
		perror("Error writing into log file");
	}
}

void log_info(const char *message) {
	log_message("INFO", message);
}

void log_error(const char *message) {
	log_message("ERROR", message);
}

void close_logger() {
	if(log_fd != -1) {
		close(log_fd);
		log_fd = -1;
	}
}
