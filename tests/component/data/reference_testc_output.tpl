
	AUM - All Ur Mocks are belongs to us - Version {VERSION}
	Copyright Airbus Defence and Space CyberSecurity

Suite: test_suite_simple...
	Test: AUM_FAIL__should_always_fail... FAILED
		tests/component/src/test_suite_simple.c:31 - AUM_FAIL - Echec volontaire du test000
	Test: AUM_ASSERT_EQUAL__should_succeed_with_same_values... SUCCESS
	Test: AUM_ASSERT_EQUAL__should_fail_with_different_values... FAILED
		tests/component/src/test_suite_simple.c:41 - AUM_ASSERT_EQUAL(1, 0) - 
	Test: AUM_ASSERT_STRING_EQUAL__should_succeed_with_same_strings... SUCCESS
	Test: AUM_ASSERT_STRING_EQUAL__should_fail_with_different_strings... FAILED
		tests/component/src/test_suite_simple.c:51 - AUM_ASSERT_STRING_EQUAL("true", "false") - Expected "true", but was "false"
	Test: AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_NULL__should_fail_with_non_NULL_pointer... FAILED
		tests/component/src/test_suite_simple.c:63 - AUM_ASSERT_PTR_NULL(fake_ptr) - Pointer expected to be (nil), but was 0xdeadbeef
	Test: AUM_ASSERT_PTR_NOT_NULL__should_succeed_with_non_NULL_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_NOT_NULL__should_fail_with_NULL_pointer... FAILED
		tests/component/src/test_suite_simple.c:75 - AUM_ASSERT_PTR_NOT_NULL(NULL)
	Test: AUM_ASSERT_PTR_EQUAL__should_succeed_with_same_pointer... SUCCESS
	Test: AUM_ASSERT_PTR_EQUAL__should_fail_with_different_pointers... FAILED
		tests/component/src/test_suite_simple.c:87 - AUM_ASSERT_PTR_EQUAL(NULL, fake_ptr) - Expected (nil), but was 0xdeadbeef
	Test: AUM_FAIL__should_stop_test_execution... FAILED
		tests/component/src/test_suite_simple.c:92 - AUM_FAIL - First failure
	Test: AUM_ASSERT_EQUAL__should_print_runtime_value... FAILED
		tests/component/src/test_suite_simple.c:99 - AUM_ASSERT_EQUAL(1, x) - Expected x to be 1, but was 0
	Test: AUM_FAIL_can_print_a_value... FAILED
		tests/component/src/test_suite_simple.c:109 - AUM_FAIL - The value of x is 0
	Test: AUM_ASSERT_MEMORY_EQUAL__should_succeed_with_same_array_content... SUCCESS
	Test: AUM_ASSERT_MEMORY_EQUAL__should_fail_with_different_array_content... FAILED
		tests/component/src/test_suite_simple.c:121 - AUM_ASSERT_MEMORY_EQUAL("hello", "world") - Expected "hel", but was "wor"


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
		tests/component/src/test_suite_with_mock.c:161 - AUM_ASSERT_WAS_CALLED("malloc") - Function malloc was never called
	Test: AUM_ASSERT_CALL_COUNT_EQUAL__should_succeed... SUCCESS
	Test: aum_mock_arguments_register__should_register_last_call_arguments... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_RAW... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_STRING... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed_with_malloc... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED__should_succeed_with_function_without_arguments... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_succeed_if_matching_call_is_present_once... SUCCESS
	Test: AUM_ASSERT_WAS_CALLED_WITH__should_not_interleave_parameters... FAILED
		tests/component/src/test_suite_with_mock.c:249 - AUM_ASSERT_WAS_CALLED_WITH("chmod", AUM_PARAMETER_STRING("path1"), AUM_PARAMETER_RAW(S_IWUSR))
	Test: AUM_ASSERT_WAS_CALLED_WITH_AT__should_accept_additional_messages_to_print_in_case_of_failure... FAILED
		tests/component/src/test_suite_with_mock.c:260 - AUM_ASSERT_WAS_CALLED_WITH_AT("malloc", 0, AUM_PARAMETER_RAW(expected)) - Expected to be called with 11, but was called with 10, as first argument
	Test: AUM_ASSERT_CALL_COUNT_EQUAL__should_indicated_actual_call_count_on_failure... FAILED
		tests/component/src/test_suite_with_mock.c:265 - AUM_ASSERT_CALL_COUNT_EQUAL("malloc", 1) - Function malloc expected to be called 1 time(s), but was called 0 time(s)
	Test: method_with_va_list_argument__should_not_failed_when_called... WARNING: Unable to store va_list argument. It is ignored... SUCCESS


Test suites: 2
Tests failed/executed: 14/38
Tests skipped: 1
