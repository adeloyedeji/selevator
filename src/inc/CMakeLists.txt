add_library(inc INTERFACE)

target_compile_features(inc INTERFACE cxx_std_17)
target_compile_features(inc INTERFACE c_std_11)
target_include_directories(inc INTERFACE ${SELEVATOR_INC_DIR})