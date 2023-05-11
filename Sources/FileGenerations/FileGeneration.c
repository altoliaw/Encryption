#include "../../Headers/FileGenerations/FileGeneration.h"

static int FileGeneration_checkFileExisted(unsigned char*);
static int FileGeneration_getProjectPath(unsigned char*);
static int FileGeneration_makeDir(unsigned char*);
static int FileGeneration_writeFile(unsigned char*, unsigned char const*, int, unsigned char*);
static int FileGeneration_readFile(unsigned char*, unsigned char*, unsigned char*, int, int);
static int FileGeneration_checkDirArchitecture(unsigned char*);

// Method definitions
void FileGeneration__constructor(FileGeneration* oFG)
{
    oFG->pf__checkFileExisted = &FileGeneration_checkFileExisted;
    oFG->pf__getProjectPath = &FileGeneration_getProjectPath;
    oFG->pf__makeDir = &FileGeneration_makeDir;
    oFG->pf__writeFile = &FileGeneration_writeFile;
    oFG->pf__readFile = &FileGeneration_readFile;
    oFG->pf__checkDirArchitecture = &FileGeneration_checkDirArchitecture;
}
void FileGeneration__destructor(const FileGeneration*)
{
    // TODO
}

/**
 * Checking the file existence. If the file exists
 * @param filePath unsigned char* The path of the file
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_checkFileExisted(unsigned char* filePath)
{
    // Variables for obtaining the project path and file name location(index)
    unsigned char projectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
    unsigned char* fileNameLoc = NULL;
    FileGeneration_getProjectPath(projectPath);

    // Parsing the filePath, and generate the folder location and file name
    // Finding the last appearance of the character '/'
    char* loc = NULL;
    loc = strrchr((char*)filePath, '/');

    // If strrchr finds nothing, then the address of fileNameLoc is equal to the one of filePath.
    if (loc == NULL) {
        fileNameLoc = filePath;
    } else { // Concatenate substring of filePath to projectPath
        int length = 0;
        length = (int)strlen((char*)projectPath);
        projectPath[length++] = (unsigned char)'/';

        for (int i = 0; i < (((unsigned char*)loc) - filePath); i++) {
            // (((unsigned char*)loc) - filePath) implies the address
            projectPath[length] = *(filePath + i);
            length++;
        }
        projectPath[length] = (unsigned char)'\0';
        fileNameLoc = (unsigned char*)(loc + 1);
    }
    // Now, the projectPath will contain the folders' names of the filePath and
    // the last two characters are (1) any character except '/' and (2) '\0'.
    // e.g., the projectPath is "/C/home/user/myproject\0"

    int httpStatus = 500;
#if defined(_WIN32) || defined(_WIN64)
    // Windows
    int length = 0;
    length = (int)strlen((char*)projectPath);
    projectPath[length++] = '/';
    projectPath[length++] = '*';
    projectPath[length++] = '\0';

    WIN32_FIND_DATA data;
    HANDLE handler = NULL;

    // If there exist files in the directory
    if ((handler = FindFirstFile((char*)projectPath, &data)) != INVALID_HANDLE_VALUE) {
        do {
            char* individualFile = data.cFileName;
            if (strcmp(individualFile, ".") == 0 || strcmp(individualFile, "..") == 0) {
                continue;
            }
            // Assemble the file name
            unsigned char tempProjectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
            memcpy(tempProjectPath, projectPath, (sizeof(unsigned char) * sizeof(projectPath)));
            int length = 0;
            length = (int)strlen((char*)tempProjectPath);
            tempProjectPath[length - 1] = (unsigned char)'\0';
            strcat((char*)tempProjectPath, (char*)fileNameLoc);

            // Determining items; there are two types of items; one is folder type, the other is file type.
            const int dir = (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
            if (dir == 1) {
                continue;
            } else {
                if (strcmp(individualFile, (char*)fileNameLoc) == 0) {
                    httpStatus = 200;
                    break;
                }
            }

        } while (FindNextFile(handler, &data) != 0);
        FindClose(handler);
    }
#else
    // Linux
    DIR* dirCurrent = opendir((char*)projectPath);
    if(dirCurrent == NULL) {
        httpStatus = 500;
        return httpStatus;
    }
    const struct dirent* dirent = NULL;
    struct stat status;

    // Iterations of the directory that users specified
    while ((dirent = readdir(dirCurrent)) != NULL) {
        // Fetching all the files in the directory
        const char* individualFile = dirent->d_name;
        if (strcmp(individualFile, ".") == 0 || strcmp(individualFile, "..") == 0) {
            continue;
        }

        // Simulations of the path of the directory
        unsigned char tempProjectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
        memcpy(tempProjectPath, projectPath, (sizeof(unsigned char) * sizeof(projectPath)));
        int length = 0;
        length = (int)strlen((char*)tempProjectPath);
        tempProjectPath[length++] = (unsigned char)'/';
        tempProjectPath[length] = (unsigned char)'\0';
        strcat((char*)tempProjectPath, (char*)fileNameLoc);

        // If the file path does not exist (stat will return -1; otherwise 0).
        if (stat((char*)tempProjectPath, &status) == -1) {
            continue;
        }

        // Determining the stuff of the path shall not belong to the folder type
        const int isDir = (status.st_mode & __S_IFDIR) != 0;
        if (isDir == 0) {
            httpStatus = 200;
            break;
        }
    }
    closedir(dirCurrent);
#endif
    return httpStatus;
}

/**
 * Obtaining the path of the project (i.e., the current working directory)
 *
 * @param projectPath The path of the project (calling by the value of the address)
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_getProjectPath(unsigned char* projectPath)
{
    int httpStatus = 200;
    char buffer[FILE_GENERATION_PROJECT_PATH_SIZE];
#if defined(_WIN32) || defined(_WIN64)
    // Windows
    if ((int)GetCurrentDirectory(sizeof(char) * sizeof(buffer), buffer) == 0) {
        httpStatus = 500;
    }
#else
    // Linux
    if (getcwd(buffer, sizeof(char) * sizeof(buffer)) == NULL) {
        httpStatus = 500;
    }
#endif

    if (httpStatus == 200) {
        memcpy(projectPath, buffer, (sizeof(buffer) * sizeof(char)));
    }
    return httpStatus;
}

/**
 * Creating a new directory
 *
 * @param dirPath The path shall contain the directory which users want to create
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_makeDir(unsigned char* dirPath)
{
    int httpStatus = 200;
#if defined(_WIN32) || defined(_WIN64)
    if (mkdir((char*)dirPath) != 0) {
        httpStatus = 500;
    }
#else
    if (mkdir((char*)dirPath, S_IRWXU | S_IRUSR | S_IRWXO) != 0) {
        httpStatus = 500;
    }
#endif
    return httpStatus;
}

/**
 * Writing the contents into the specified directory.
 *
 * @param filePath unsigned char* The path of the file for writing
 * @param contents unsigned char* The contents
 * @param mode unsigned char* The fwrite mode in C
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_writeFile(
    unsigned char* filePath,
    unsigned char const* contents,
    int contentsLen,
    unsigned char* mode)
{
    // Generating current working directory path
    unsigned char projectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
    memset(projectPath, (unsigned char)'\0', FILE_GENERATION_PROJECT_PATH_SIZE);
    FileGeneration_getProjectPath(projectPath);

    // Generating complete file path
    int length = 0;
    length = (int)strlen((char*)projectPath);
    projectPath[length++] = (unsigned char)'/';
    projectPath[length++] = (unsigned char)'\0';
    memcpy((projectPath + length - 1), filePath, (int)strlen((char*)filePath));

    // Opening file by using fopen function
    int httpStatus = 200;
    FILE* pFilePtr = NULL;
    pFilePtr = fopen((char*)projectPath, (char*)mode);

    if (pFilePtr == NULL) {
        httpStatus = 500;
    } else {
        fwrite(contents, 1, contentsLen, pFilePtr);
        fclose(pFilePtr);
    }

    return httpStatus;
}

/**
 * Reading the contents into the specified directory.
 *
 * @param filePath unsigned char* The path of the file for writing
 * @param buffer unsigned char* The contents in the file by using call-by the value of address,
 * the buffer size shall be defined in the calling function.
 * @param mode unsigned char* The fopen mode in C
 * @param startPos int The start position in the file; the value is generally to be 1.
 * @param contentsLen int The length that users want to read from the file
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_readFile(
    unsigned char* filePath,
    unsigned char* buffer,
    unsigned char* mode,
    int startPos,
    int contentsLen)
{
    // Generating current working directory path
    unsigned char projectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
    memset(projectPath, (unsigned char)'\0', FILE_GENERATION_PROJECT_PATH_SIZE);
    FileGeneration_getProjectPath(projectPath);

    // Generating complete file path
    int length = 0;
    length = (int)strlen((char*)projectPath);
    projectPath[length++] = (unsigned char)'/';
    projectPath[length++] = (unsigned char)'\0';
    memcpy((projectPath + length - 1), filePath, (int)strlen((char*)filePath));

    // Opening file by using fopen function
    int httpStatus = 200;
    FILE* pFilePtr = NULL;
    pFilePtr = fopen((char*)projectPath, (char*)mode);

    if (pFilePtr == NULL) {
        httpStatus = 500;
    } else {
        httpStatus = (int)fread(buffer, startPos, contentsLen, pFilePtr);
        fclose(pFilePtr);
        if (httpStatus >= 0) {
            httpStatus = 200;
        } else {
            httpStatus = 500;
        }
    }

    return httpStatus;
}

/**
 * A process to maintain the directories from the path
 *
 * @param filePath unsigned char* The path of the file for directory maintenance
 * @return int HTTP response status codes, more information can be referred
 * in the following URL: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
 */
static int FileGeneration_checkDirArchitecture(unsigned char* filePath) {
    int httpStatus = 200;
    // Variables for obtaining the project path and file name location(index)
    unsigned char projectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
    FileGeneration_getProjectPath(projectPath);

    // Parsing the filePath, and generate the folder location in the path string
    char* loc = NULL;
    char* prevLoc = NULL;
    prevLoc = (char*)filePath;
    loc = strchr((char*)filePath, '/');
    int length = 0;
    length = (int)strlen((char*)projectPath);
    struct stat status;
    unsigned char tempProjectPath[FILE_GENERATION_PROJECT_PATH_SIZE];

    while (loc != NULL && httpStatus == 200) {
        projectPath[length++] = (unsigned char)'/';
        for (int i = 0; i < ((unsigned char*)loc - (unsigned char*)prevLoc); i++) {
            // ((unsigned char*)loc - (unsigned char*)prevLoc) implies the address
            projectPath[length++] = *(prevLoc + i);
        }
        projectPath[length] = '\0';
        int tempLength = 0;
        tempLength = length;
        memcpy(tempProjectPath, projectPath, (sizeof(unsigned char) * sizeof(projectPath)));
        tempProjectPath[tempLength++]= '/';
        tempProjectPath[tempLength++]= '\0';

        // Move the two pointers
        prevLoc = loc + 1;
        loc = strchr(prevLoc, '/');

        // Upon successful completion, 0 is returned. Otherwise, -1.
        if (stat((char*)tempProjectPath, &status) != 0) {
            httpStatus = FileGeneration_makeDir(projectPath);
        } else {
            // Determining the stuff of the path shall not belong to the folder type
        #if defined(_WIN32) || defined(_WIN64)
            int isDir = (status.st_mode & S_IFDIR) != 0;
        #else
            int isDir = (status.st_mode & __S_IFDIR) != 0;
        #endif
            if(isDir == 0){
                httpStatus = FileGeneration_makeDir(projectPath);
            }
        }
    }

    return httpStatus;
}