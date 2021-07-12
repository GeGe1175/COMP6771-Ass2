cxx_test(
   TARGET basic_tests
   FILENAME "basic_tests.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET harder_tests
   FILENAME "harder_tests.cpp"
   LINK euclidean_vector
)
