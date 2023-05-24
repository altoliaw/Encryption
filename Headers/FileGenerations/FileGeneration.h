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
#endif
#include <sys/stat.h> // "mkdir" on linux/Windows platform
#include <sys/types.h> // Iteration from a folder on linux platform

#define FILE_GENERATION_PROJECT_PATH_SIZE 512 // 512 bytes
#define DEFAULT_CURRENT_WORKING_DIRECTORY 1 // The status for the current working directory being used;
//0 implies the current working directory is not used.
//Any values except 0 shows the current working directory will be used.

// Class declarations
typedef struct FileGeneration FileGeneration;

// Class body
struct FileGeneration {
  unsigned int defaultCurrentWorkingDirectory;
  unsigned char currentWorkingDirectory[FILE_GENERATION_PROJECT_PATH_SIZE];

  int (*pf__checkFileExisted)(FileGeneration*, unsigned char*);
  int (*pf__setProjectPath)(FileGeneration*, unsigned char*);
  int (*pf__getProjectPath)(FileGeneration*, unsigned char*);
  int (*pf__makeDir)(unsigned char*);
  int (*pf__writeFile)(FileGeneration*, unsigned char*, unsigned char const*, int, unsigned char*);
  int (*pf__readFile)(FileGeneration*, unsigned char*, unsigned char*, unsigned char*, int, int);
  int (*pf__checkDirArchitecture)(FileGeneration*, unsigned char*);
};

// Method declarations
void FileGeneration__constructor(FileGeneration*);
void FileGeneration__destructor(const FileGeneration*);