#ifndef DIRECTORY_OPS_H 
#define DIRECTORY_OPS_H

void list_directory(const char *path);
void delete_folder(const char *path);
void create_folder(const char *path);
void search_in_folder(const char *path, const char *file_name);

#endif
