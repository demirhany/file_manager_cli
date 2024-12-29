# File Manager Program

A simple command-line file manager program written in C. This program provides various operations for managing files and directories, such as creating, copying, moving, deleting files and directories, changing file permissions, and displaying file contents. It is designed to help users manage their files more efficiently.

### Features

#### File Operations:
- `fdisplay <path>`: View the content of a file.
- `fcopy <source> <destination>`: Copy a file to a desired directory.
- `fmove <source> <destination>`: Move (or rename) a file.
- `fcreate <path>`: Create a new file in the specified directory.
- `fstat <path>`: Get information about a specified file.
- `fdelete <path>`: Delete a file.
- `fsearch <path> <file_name>`: Search for a file within the specified directory.

#### Directory Operations:
- `dlist <path>`: List the files in the specified directory.
- `ddelete <path>`: Delete the specified directory.
- `dcreate <path>`: Create a new directory.

#### Permissions:
- `fdchmod <path> <permissions>`: Change the permissions of a file or folder.

#### Help:
- `--help`: Display the list of available commands.
- `exit`: Exit the program.

### Project Structure

- `project-root`
  - `bin`
    - `directory_ops.o`
    - `file_manager`
    - `file_operations.o`
    - `logger.o`
    - `main.o`
    - `permission.o`
  - `include`
    - `directory_ops.h`
    - `file_operations.h`
    - `logger.h`
    - `permissions.h`
  - `logs`
  - `makefile`
  - `src`
    - `directory_ops.c`
    - `file_operations.c`
    - `logger.c`
    - `main.c`
    - `permission.c`


- `bin/`: Contains the compiled object files and the final executable (`file_manager`).
- `include/`: Contains the header files for file operations, directory operations, permissions, and logging.
- `logs/`: Directory for storing log files.
- `src/`: Contains the source files for each module: file operations, directory operations, permissions, logger, and the main program.
- `makefile`: Used to compile and link the program.

### Compilation

To compile the project, run the following command:

```bash
make
```

### Running

```bash
./bin/file_manager
```
