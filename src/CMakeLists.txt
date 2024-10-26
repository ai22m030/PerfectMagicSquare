########################################################################################################################
### MAGIC SQUARE APPLICATION
########################################################################################################################

add_executable(${MAGIC_SQUARE_PROJECT_NAME}
        ${MAGIC_SQUARE_SRC_DIR}/main.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

find_package(OpenMP REQUIRED)

if (OpenMP_CXX_FOUND)
    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME} PUBLIC
        ${MAGIC_SQUARE_INC_DIR})