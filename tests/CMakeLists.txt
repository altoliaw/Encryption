add_executable(Tests
    ./Main.c
    ./Sources/test_Encoders_UU_Encoder.c
    ./Sources/test_Entry.c
)

target_include_directories(Tests PUBLIC ./Headers)

target_link_libraries(Tests
    Mains
    Encoders
    Encryptions
    FileGenerations
    cmocka
    ssl
    crypto
)