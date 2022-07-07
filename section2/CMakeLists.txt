project(section_2)

add_executable(1_mutex 1_mutex.cpp)
target_link_libraries(1_mutex pthread)

add_executable(3_thread_safe_stack 3_thread_safe_stack.cpp)
target_link_libraries(3_thread_safe_stack pthread)

add_executable(04_deadlock 04_deadlock.cpp)
target_link_libraries(04_deadlock pthread)

add_executable(05_unique_lock 05_unique_lock.cpp)
target_link_libraries(05_unique_lock pthread)