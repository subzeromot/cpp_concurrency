project(section_1)

add_executable(01_joinable 01_joinable.cpp)
target_link_libraries(01_joinable pthread)

add_executable(02_detach 02_detach.cpp)
target_link_libraries(02_detach pthread)

add_executable(03_exception 03_exception.cpp)
target_link_libraries(03_exception pthread)

add_executable(04_thread_parameters 04_thread_parameters.cpp)
target_link_libraries(04_thread_parameters pthread)

add_executable(05_pass_by_ref_and_detach 05_pass_by_ref_and_detach.cpp)
target_link_libraries(05_pass_by_ref_and_detach pthread)

add_executable(06_ownership 06_ownership.cpp)
target_link_libraries(06_ownership pthread)