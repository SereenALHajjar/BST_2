

CPMAddPackage("gh:doctest/doctest#v2.4.12")


add_executable(bst_tests bst_tests.cpp)
target_link_libraries(bst_tests doctest bst)

