#include "../../Headers/FileGenerations/FileGeneration.h"

static int FileGeneration_checkFileExisted(char*);
static int FileGeneration_getProjectPath(unsigned char*);
static int FileGeneration_makeDir(const char*);

// Method definitions
void FileGeneration__constructor(FileGeneration* oFG) {
    oFG->pf__checkFileExisted = &FileGeneration_checkFileExisted;
}
void FileGeneration__destructor(const FileGeneration*) {
    // TODO
}

static int FileGeneration_checkFileExisted(char* filePath) {
    // Parsing the filePath, and generate the folder location and file name
    // Finding the last appearance of the character '/'
    char* loc =  NULL;
    loc = strrchr(filePath, '/');

    unsigned char projectPath[256];
    unsigned char* fileNameLoc = NULL;
    FileGeneration_getProjectPath(projectPath);


    if(loc == NULL) { // If strrchr finds nothing, then the address of fileNameLoc is equal to the one of filePath.
        fileNameLoc = (unsigned char*)filePath;
    } else {// Concatenate substring of filePath to projectPath
        int length = 0;
        length = (int)strlen((char*)projectPath);
        projectPath[length++] = '/';
        for(int i = 0; i < (loc - filePath); i++) {
            projectPath[length] = *(filePath + i);
            length++;
        }
        projectPath[length] = '\0';
        fileNameLoc = (unsigned char*)(loc + 1);
    }
    printf("dirLoc is %s\n; and the length is %d\n", projectPath, (int)strlen(projectPath));
    printf("fileNameLoc is %s\n", fileNameLoc);

    int flag = 200;
    #if defined(_WIN32) || defined(_WIN64)
    // Windows

    #else
    // Linux

    #endif
    return flag;
}

/**
 * Obtaining the path of the project (i.e., generally,
 * the location depends on the location of the executable file)
 *
 * @param projectPath The path of the project (calling by the value of the address)
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_getProjectPath(unsigned char* projectPath) {
    int flag = 200;
    char buffer[256];
    #if defined(_WIN32) || defined(_WIN64)
    // Windows
    if(GetCurrentDirectory( 256, buffer) == 0) {
        flag =500;
    }
    #else
    // Linux
    if(getcwd(buffer, sizeof(buffer)) == NULL) {
        flag =500;
    }
    #endif

    if(flag == 200) {
        memcpy(projectPath, buffer, sizeof(buffer));
    }
    return flag;
}

/**
 * Create a new directory
 *
 * @param dirPath The path containing the directory
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_makeDir(const char* dirPath) {

    int flag = 200;
    #if defined(_WIN32) || defined(_WIN64)
    if (mkdir(dirPath) != 0) {
        flag = 500;
    }
    #else
    if (mkdir(dirPath, S_IRWXU | S_IRUSR | S_IRWXO) != 0) {
        flag = 500;
    }
    #endif
    return flag;
}