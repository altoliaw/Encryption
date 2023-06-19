# Encryption Readme

Output File Format: .exe
Platform: Debian
Tags: Encryption

the issue was raised on *June 19th, 2023, edited by Nick*

# Prerequisite

The project is designed on `Ubutu 22.10`(Debian series). The details of the environment and tools are listed as follows.

- **Compiler:** `gcc 12 with C99 standard`; all commands are listed in the make file, namely, `Makefile`, in the project
- **Make:** `GNU Make 4.3`
- **OpenSSL:** `3.1.0 14` which belongs to OpenSSL 3
- **Cmake:** `3.24.2`
- **Cmocka:** `1.1`

The first three items in the list above belong to the main encryption components; the last two belong to the unit tests of the project.

# Public Application Interface

The abstract factory pattern is one of the designed patterns for creating application interfaces in OOP. However, in C, to implement an abstract factory pattern can be modeled in public functions because there is no `class` to model an abstract class. For convenience, the author aggregated those functions as interfaces and put those functions into `Entry.c`. In the following, the author will introduce some significant functions of `Entry.c` sequentially.

| API | Returned Value | Parameters Descriptions |
| --- | --- | --- |
| AES-256-GCM Encryption
int ___AES_256_GCM_encryption( const unsigned char* plainText, const int plainTextLen, unsigned char* ciphertext) | The HTTP status code; 200 shows that the function works successfully and 500 shows a failure |  plainText:  The string of the plaintext; the byte[] and char[] are supported
plainTextLen: The length of the plaintext or the size of byte[] or char[]
ciphertext: The encrypted contents

🔔Due to DLL. properties of C, the size of the arguments for parameters shall be defined.

🔔The size of the variable for the parameter ciphertext is equal to plainTextLen+ 28 where 28 is the value that comes from the length of IV (12) and the auth tag (16). For example, if the length of plainTextLen is 15, the size of ciphertext equals $15 + 28 = 43$. Therefore, users shall allocate 43 bytes/chars for the encrypted result. |
| AES-256-GCM Decryption
int ___AES_256_GCM_decryption(
    unsigned char* ciphertext,
    const int ciphertextLen,
    unsigned char* plainText) | The HTTP status code; 200 shows that the function works successfully and 500 shows a failure |  ciphertext:  The ciphertext; the byte[] and char[] are supported
ciphertextLen: The length of the ciphertext or the size of byte[] or char[]
plainText: The plaintext decrypted from the ciphertext

🔔Due to DLL. properties of C, the size of the arguments for parameters shall be defined.

🔔The size of the variable for the parameter plainText is equal to ciphertextLen- 28 where 28 is the value that comes from the length of IV (12) and the auth tag (16). For example, if the length of ciphertextLenis 90, the size of plainText equals $90 - 28 = 62$. Therefore, users shall allocate 62 bytes/chars for the decrypted result. |
| Current Working Directory Setting
int ___setProjectPath(unsigned char* approach, unsigned char* projectPath) | The HTTP status code; 200 shows that the function works successfully and 500 shows a failure | approach: One approach is available. The approach  value is AES_256_GCM
projectPath: The path that users would like to be the current working directory. |

For clarity, all fields and methods are generated from the `Doxygen` application. To see more details, please refer to the `Encryption/docs/html/index.html`.