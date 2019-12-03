
	AUM - All Ur Mocks are belongs to us - Version {VERSION}
	Copyright Airbus Defence and Space CyberSecurity

Execution of all tests
Suite: test_suite_simple...
	Test: AUM_FAIL__should_always_fail... FAILED
		tests/component/src/test_suite_simple.c:9 - AUM_FAIL - Echec volontaire du test000
	Test: AUM_ASSERT_EQUAL__should_succeed_with_same_values... SUCCESS
	Test: AUM_ASSERT_EQUAL__should_fail_with_different_values... FAILED
		tests/component/src/test_suite_simple.c:19 - AUM_ASSERT_EQUAL(1, 0) - 
	Test: AUM_ASSERT_STRING_EQUAL__should_succeed_with_same_strings... SUCCESS
	Test: AUM_ASSERT_STRING_EQUAL__should_fail_with_different_strings... FAILED
		tests/component/src/test_suite_simple.c:29 - AUM_ASSERT_STRING_EQUAL("true", "false") - Expected "true", but was "false"
	Test: AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_NULL__should_fail_with_non_NULL_pointer... FAILED
		tests/component/src/test_suite_simple.c:41 - AUM_ASSERT_PTR_NULL(fake_ptr) - Pointer expected to be (nil), but was 0xdeadbeef
	Test: AUM_ASSERT_PTR_NOT_NULL__should_succeed_with_non_NULL_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_NOT_NULL__should_fail_with_NULL_pointer... FAILED
		tests/component/src/test_suite_simple.c:53 - AUM_ASSERT_PTR_NOT_NULL(NULL)
	Test: AUM_ASSERT_PTR_EQUAL__should_succeed_with_same_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_EQUAL__should_fail_with_different_pointers... FAILED
		tests/component/src/test_suite_simple.c:65 - AUM_ASSERT_PTR_EQUAL(NULL, fake_ptr) - Expected (nil), but was 0xdeadbeef
	Test: AUM_FAIL__should_stop_test_execution... FAILED
		tests/component/src/test_suite_simple.c:70 - AUM_FAIL - First failure
	Test: AUM_ASSERT_EQUAL__should_print_runtime_value... FAILED
		tests/component/src/test_suite_simple.c:77 - AUM_ASSERT_EQUAL(1, x) - Expected x to be 1, but was 0
	Test: AUM_FAIL_can_print_a_value... FAILED
		tests/component/src/test_suite_simple.c:87 - AUM_FAIL - The value of x is 0
	Test: AUM_ASSERT_MEMORY_EQUAL__should_succeed_with_same_array_content... SUCCESS
	Test: AUM_ASSERT_MEMORY_EQUAL__should_fail_with_different_array_content... FAILED
		tests/component/src/test_suite_simple.c:99 - AUM_ASSERT_MEMORY_EQUAL("hello", "world") - Expected "hel", but was "wor"


Suite: test_suite_with_mock...
	Test: aum_mock_will_return__should_succeed... SUCCESS
	Test: aum_mock_will_return__should_modify_behavior_of_all_subsequent_calls... SUCCESS
	Test: aum_mock_reset__should_clean_will_return... SUCCESS
	Test: aum_mock_will_return_at_third_call__should_succeed... SUCCESS
	Test: aum_mock_will_return_at__should_ignore_preceding_calls_to_the_mock... SUCCESS
	Test: aum_mock_will_execute__should_install_fake_function... SUCCESS
	Test: aum_mock_get_call_count__should_count_function_calls... SUCCESS
	Test: aum_mock_reset__should_clean_call_count... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED__should_succeed_if_function_called... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED__should_failed_if_function_not_called... FAILED
		tests/component/src/test_suite_with_mock.c:137 - AUM_ASSERT_WAS_CALLED("malloc") - Function malloc was never called
	Test: AUM_ASSERT_CALL_COUNT_EQUAL__should_succeed... SUCCESS
	Test: aum_mock_arguments_register__should_register_last_call_arguments... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_RAW... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_STRING... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed_with_malloc... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED__should_succeed_with_function_without_arguments... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed_if_matching_call_is_present_once... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_not_interleave_parameters... FAILED
		tests/component/src/test_suite_with_mock.c:225 - AUM_ASSERT_WAS_CALLED_WITH("chmod", AUM_PARAMETER_STRING("path1"), AUM_PARAMETER_RAW(S_IWUSR))
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_accept_additional_messages_to_print_in_case_of_failure... FAILED
		tests/component/src/test_suite_with_mock.c:236 - AUM_ASSERT_WAS_CALLED_WITH_AT("malloc", 0, AUM_PARAMETER_RAW(expected)) - Expected to be called with 11, but was called with 10, as first argument
	Test: AUM_ASSERT_CALL_COUNT_EQUAL__should_indicated_actual_call_count_on_failure... FAILED
		tests/component/src/test_suite_with_mock.c:241 - AUM_ASSERT_CALL_COUNT_EQUAL("malloc", 1) - Function malloc expected to be called 1 time(s), but was called 0 time(s)


Run summary:	Type	Ran	Ignored	Passed	Failed
            	suites	2	0	2	0
            	tests	37	1	23	14


Execution of a single test
Suite: test_suite_simple...
	Test: AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer... SUCCESS


Run summary:	Type	Ran	Ignored	Passed	Failed
            	suites	0	0	0	0
            	tests	1	0	1	0
