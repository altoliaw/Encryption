add_library(Encryptions
    Encryption.c
    AES_256_GCM.c
    EncryptionDispatcher.c
)

target_include_directories(Encryptions PUBLIC ../../Headers/Encryptions)