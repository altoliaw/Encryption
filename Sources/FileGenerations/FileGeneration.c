#include "../../Headers/FileGenerations/FileGeneration.h"

static int FileGeneration_checkFileExisted(unsigned char*);
static int FileGeneration_getProjectPath(unsigned char*);
static int FileGeneration_makeDir(unsigned char*);
static int FileGeneration_writeFile(unsigned char*, unsigned char const*, int, unsigned char*);
static int FileGeneration_readFile(unsigned char*, unsigned char*, unsigned char*, int, int);

// Method definitions
void FileGeneration__constructor(FileGeneration* oFG)
{
    oFG->pf__checkFileExisted = &FileGeneration_checkFileExisted;
    oFG->pf__getProjectPath = &FileGeneration_getProjectPath;
    oFG->pf__makeDir = &FileGeneration_makeDir;
    oFG->pf__writeFile = &FileGeneration_writeFile;
    oFG->pf__readFile = &FileGeneration_readFile;
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

    // Parsing the filePath, and generate the folder location and file name
    // Finding the last appearance of the character '/'
    char* loc = NULL;
    loc = strrchr((char*)filePath, '/');

    unsigned char projectPath[FILE_GENERATION_PROJECT_PATH_SIZE];
    unsigned char* fileNameLoc = NULL;
    FileGeneration_getProjectPath(projectPath);

    // If strrchr finds nothing, then the address of fileNameLoc is equal to the one of filePath.
    if (loc == NULL) {
        fileNameLoc = filePath;
    } else { // Concatenate substring of filePath to projectPath
        int length = 0;
        length = (int)strlen((char*)projectPath);
        projectPath[length++] = (unsigned char)'/';

        for (int i = 0; i < (((unsigned char*)loc) - filePath); i++) {
            projectPath[length] = *(filePath + i);
            length++;
        }
        projectPath[length] = (unsigned char)'\0';
        fileNameLoc = (unsigned char*)(loc + 1);
    }

    int flag = 500;
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
                flag = 200;
                break;
            }

        } while (FindNextFile(handler, &data) != 0);
        FindClose(handler);
    }
#else
    // Linux
    DIR* dirCurrent = opendir((char*)projectPath);
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
            flag = 200;
            break;
        }
    }
    closedir(dirCurrent);
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
 * @param dirPath The path containing the directory
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
    int httpStatus = 200;
    FILE* pFilePtr = NULL;
    pFilePtr = fopen((char*)filePath, (char*)mode);

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
    int httpStatus = 200;
    FILE* pFilePtr = NULL;
    pFilePtr = fopen((char*)filePath, (char*)mode);

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