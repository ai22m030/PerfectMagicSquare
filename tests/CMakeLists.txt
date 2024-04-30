########################################################################################################################
### MAGIC SQUARE TESTS
########################################################################################################################

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsThree
        ${MAGIC_SQUARE_TESTS_DIR}/square_three_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsFour
        ${MAGIC_SQUARE_TESTS_DIR}/square_four_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsFive
        ${MAGIC_SQUARE_TESTS_DIR}/square_five_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsSix
        ${MAGIC_SQUARE_TESTS_DIR}/square_six_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsSeven
        ${MAGIC_SQUARE_TESTS_DIR}/square_seven_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsEight
        ${MAGIC_SQUARE_TESTS_DIR}/square_eight_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

add_executable(${MAGIC_SQUARE_PROJECT_NAME}TestsNine
        ${MAGIC_SQUARE_TESTS_DIR}/square_nine_test.cpp
        ${MAGIC_SQUARE_SRC_DIR}/program_options.cpp
        ${MAGIC_SQUARE_SRC_DIR}/magic_square.cpp)

find_package(OpenMP REQUIRED)

if (OpenMP_CXX_FOUND)
    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsThree PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsThree PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsFour PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsFour PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsFive PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsFive PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsSix PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsSix PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsSeven PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsSeven PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsEight PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsEight PUBLIC OpenMP::OpenMP_CXX)

    target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsNine PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${MAGIC_SQUARE_PROJECT_NAME}TestsNine PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsThree PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsFour PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsFive PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsSix PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsSeven PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsEight PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

target_include_directories(${MAGIC_SQUARE_PROJECT_NAME}TestsNine PUBLIC
        ${MAGIC_SQUARE_INC_DIR})

add_test(NAME square_three_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsThree>)

add_test(NAME square_four_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsFour>)

add_test(NAME square_five_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsFive>)

add_test(NAME square_six_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsSix>)

add_test(NAME square_seven_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsSeven>)

add_test(NAME square_eight_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsEight>)

add_test(NAME square_nine_test COMMAND $<TARGET_FILE:${MAGIC_SQUARE_PROJECT_NAME}TestsNine>)
