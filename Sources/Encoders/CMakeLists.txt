add_library(Encoders
    Encoder.c
    UU_Encode.c
    EncoderDispatcher.c
)

target_include_directories(Encoders PUBLIC ../../Headers/Encoders)