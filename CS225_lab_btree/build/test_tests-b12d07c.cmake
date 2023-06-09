add_test( test_insertion_idx_emp /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_insertion_idx_emp  )
set_tests_properties( test_insertion_idx_emp PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_insertion_idx_small /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_insertion_idx_small  )
set_tests_properties( test_insertion_idx_small PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree3_small /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree3_small  )
set_tests_properties( test_btree3_small PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree3_large_seq /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree3_large_seq  )
set_tests_properties( test_btree3_large_seq PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree3_large_rand /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree3_large_rand  )
set_tests_properties( test_btree3_large_rand PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree64_large_seq /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree64_large_seq  )
set_tests_properties( test_btree64_large_seq PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree64_large_rand /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree64_large_rand  )
set_tests_properties( test_btree64_large_rand PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree128_med_rand /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree128_med_rand  )
set_tests_properties( test_btree128_med_rand PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree256_med_rand /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree256_med_rand  )
set_tests_properties( test_btree256_med_rand PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree12_double /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree12_double  )
set_tests_properties( test_btree12_double PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
add_test( test_btree12_strings /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build/test test_btree12_strings  )
set_tests_properties( test_btree12_strings PROPERTIES WORKING_DIRECTORY /workspaces/CS225/sp23_cs225_aidanyj2/lab_btree/build)
set( test_TESTS test_insertion_idx_emp test_insertion_idx_small test_btree3_small test_btree3_large_seq test_btree3_large_rand test_btree64_large_seq test_btree64_large_rand test_btree128_med_rand test_btree256_med_rand test_btree12_double test_btree12_strings)
