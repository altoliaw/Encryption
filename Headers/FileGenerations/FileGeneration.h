#pragma once
/**
 * A header of FileGenerations class; in the class, some methods related to directory
 * and file generation are proposed. They include directory checking, file checking,
 * file generation and directory generation. All methods are listed in the following
 * declarations.
 *
 * @author Nick
 * @date 2023/4/20
 */

// Libraries included
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h> // mkdir on win platform
#include <windows.h> // Iteration from a folder on win platform
#else
#include <unistd.h> // For obtaining the location in the system
#include <dirent.h> // Iteration from a folder on linux platform
#include <sys/stat.h> // "mkdir" on linux platform
#include <sys/types.h> // Iteration from a folder on linux platform
#endif

#define FILE_GENERATION_PROJECT_PATH_SIZE 256 // 256 bits

// Class declarations
typedef struct FileGeneration FileGeneration;

// Class body
struct FileGeneration {
  int (*pf__checkFileExisted)(unsigned char*);
  int (*pf__getProjectPath)(unsigned char*);
  int (*pf__makeDir)(unsigned char*);
  int (*pf__writeFile)(unsigned char*, unsigned char const*, int, unsigned char*);
  int (*pf__readFile)(unsigned char*, unsigned char*, unsigned char*, int, int);
};

// Method declarations
void FileGeneration__constructor(FileGeneration*);
void FileGeneration__destructor(const FileGeneration*);