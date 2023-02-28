########################################################################################################################
### MAGIC SQUARE APPLICATION
########################################################################################################################

add_executable(${MAGIC_SQUARE_PROJECT_NAME}
        ${MAGIC_SQUARE_SRC_DIR}/main.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME} PUBLIC
        ${MAGIC_SQUARE_INC_DIR})