project(section_4)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
#add_compile_options("-std=c++20" "-fcoroutines" "-pthread")


add_executable(01_execution_policy 01_execution_policy.cpp)
target_link_libraries(01_execution_policy pthread)
