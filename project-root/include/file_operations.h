#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void copy_file(const char *source, const char *destination);
void move_file(const char *source, const char *destination);
void create_file(const char *path);
void delete_file(const char *path);
void get_file_info(const char *path);
void display_file(const char *path); 

#endif 

