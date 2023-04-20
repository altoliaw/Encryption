#pragma once
/**
 * A header of FileGenerations class
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

// Class declarations
typedef struct FileGeneration FileGeneration;

// Class body
struct FileGeneration {
  int (*pf__checkFileExisted)(char* fileName);
};

// Method declarations
void FileGeneration__constructor(FileGeneration*);
void FileGeneration__destructor(const FileGeneration*);