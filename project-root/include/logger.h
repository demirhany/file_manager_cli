#ifndef LOGGER_H
#define LOGGER_H

void log_info(const char *message);
void log_error(const char *message);
void initialize_logger(const char *path);
void close_logger();

#endif 

