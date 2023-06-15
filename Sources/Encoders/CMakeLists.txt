add_library(Encoders Encoder.c UU_Encode.c)

target_include_directories(Encoders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Headers/Encoders)