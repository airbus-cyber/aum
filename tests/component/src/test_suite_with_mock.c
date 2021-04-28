/*
    AUM: Airbus Unit tests with Mocks for C. AUM is a unit testing framework for C that allows the easy definition and request of mocks.
    Copyright (C) 2019  Airbus Defence and Space

    You should have received a copy of the AUTHORS.md file which lists all contributors.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <setjmp.h>

#include <aum.h>
#include <test/test_suites.h>

/******************************************************************************
 * Implémentation des tests de la suite "Suite with Mock"                     *
 ******************************************************************************/

AUM_TEST(aum_mock_will_return__should_succeed)
{
  aum_mock_will_return("malloc", 0);

  char *test_ptr = malloc(10 * sizeof(char));
  AUM_ASSERT_PTR_NULL(test_ptr);
}

AUM_TEST(aum_mock_will_return__should_modify_behavior_of_all_subsequent_calls)
{
  aum_mock_will_return("malloc", 0);

  char *result_ptr = malloc(10 * sizeof(char));
  result_ptr = malloc(10 * sizeof(char));
  AUM_ASSERT_PTR_NULL(result_ptr);
}

AUM_TEST(aum_mock_reset__should_clean_will_return)
{
  aum_mock_will_return("malloc", 0);

  char *test_ptr = malloc(10 * sizeof(char));
  AUM_ASSERT_PTR_NULL(test_ptr);

  aum_mock_reset();

  test_ptr = malloc(10 * sizeof(char));
  AUM_ASSERT_PTR_NOT_NULL(test_ptr);
  if (test_ptr != NULL) free(test_ptr);
}

AUM_TEST(aum_mock_will_return_at_third_call__should_succeed)
{
  aum_mock_will_return_at("malloc", 0, 3);

  char *ptr1 = malloc(sizeof(char) * 10);
  AUM_ASSERT_PTR_NOT_NULL(ptr1);

  char *ptr2 = malloc(sizeof(char) * 10);
  AUM_ASSERT_PTR_NOT_NULL(ptr2);

  char *ptr3 = malloc(sizeof(char) * 10);
  AUM_ASSERT_PTR_NULL(ptr3);

  free(ptr1);
  free(ptr2);
}

AUM_TEST(aum_mock_will_return_at__should_ignore_preceding_calls_to_the_mock)
{
  char *ptr1 = malloc(sizeof(char) * 10);
  // note: if this assert is removed, some environment will optimize the call to malloc away
  AUM_ASSERT_PTR_NOT_NULL(ptr1);

  aum_mock_will_return_at("malloc", 0, 2);

  char *ptr2 = malloc(sizeof(char) * 10);
  AUM_ASSERT_PTR_NOT_NULL(ptr2);

  char *ptr3 = malloc(sizeof(char) * 10);
  AUM_ASSERT_PTR_NULL(ptr3);

  free(ptr1);
  free(ptr2);
}

#define _FAKE_PTR (void *)((unsigned long)(0x1000 & 0xffffffff))
static bool _fake_malloc_was_called = false;
static void *_fake_malloc(size_t __attribute__((unused)) size)
{
  _fake_malloc_was_called = true;
  return _FAKE_PTR;
}

AUM_TEST(aum_mock_will_execute__should_install_fake_function)
{
  aum_mock_will_execute("malloc", _fake_malloc);

  char *test_ptr = malloc(10 * sizeof(char));

  AUM_ASSERT_PTR_EQUAL(test_ptr, _FAKE_PTR);
  AUM_ASSERT_EQUAL(_fake_malloc_was_called, true);
}

#define MALLOC_CALL_COUNT 10
AUM_TEST(aum_mock_get_call_count__should_count_function_calls)
{
  char *test_ptr_table[MALLOC_CALL_COUNT];
  int i;

  for (i = 0; i < MALLOC_CALL_COUNT; i++) {
    test_ptr_table[i] = malloc(10 * sizeof(char));
    AUM_ASSERT_PTR_NOT_NULL(test_ptr_table[i]);
  }

  AUM_ASSERT_EQUAL(aum_mock_get_call_count("malloc"), MALLOC_CALL_COUNT);

  for (i = 0; i < MALLOC_CALL_COUNT; i++) free(test_ptr_table[i]);
}

AUM_TEST(aum_mock_reset__should_clean_call_count)
{
  char *test_ptr_table[MALLOC_CALL_COUNT];
  int i;

  for (i = 0; i < MALLOC_CALL_COUNT; i++) {
    test_ptr_table[i] = malloc(10 * sizeof(char));
    free(test_ptr_table[i]);
  }

  aum_mock_reset();
  AUM_ASSERT_EQUAL(aum_mock_get_call_count("malloc"), 0);
}

AUM_TEST(AUM_ASSERT_WAS_CALLED__should_succeed_if_function_called)
{
  char *test_ptr = malloc(10 * sizeof(char));
  AUM_ASSERT_PTR_NOT_NULL(test_ptr);

  AUM_ASSERT_WAS_CALLED("malloc");

  free(test_ptr);
}

AUM_TEST(AUM_ASSERT_WAS_CALLED__should_failed_if_function_not_called)
{
  AUM_ASSERT_WAS_CALLED("malloc");
}

AUM_TEST(AUM_ASSERT_CALL_COUNT_EQUAL__should_succeed)
{
  char *test_ptr_table[MALLOC_CALL_COUNT];
  int i;

  for (i = 0; i < MALLOC_CALL_COUNT; i++) {
    test_ptr_table[i] = malloc(10 * sizeof(char));
    AUM_ASSERT_PTR_NOT_NULL(test_ptr_table[i]);
  }

  AUM_ASSERT_CALL_COUNT_EQUAL("malloc", MALLOC_CALL_COUNT);

  for (i = 0; i < MALLOC_CALL_COUNT; i++) free(test_ptr_table[i]);
}

#define TEST_PTR_SIZE (10 * sizeof(char))
AUM_TEST(aum_mock_arguments_register__should_register_last_call_arguments)
{
  char *test_ptr = malloc(TEST_PTR_SIZE);
  AUM_ASSERT_PTR_NOT_NULL(test_ptr);

  AUM_ASSERT_EQUAL(aum_mock_get_parameter_at("malloc", 0), TEST_PTR_SIZE);

  free(test_ptr);
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_RAW)
{
  char *test_ptr = malloc(TEST_PTR_SIZE);
  AUM_ASSERT_PTR_NOT_NULL(test_ptr);

  AUM_ASSERT_WAS_CALLED_WITH_AT("malloc", 0, AUM_PARAMETER_RAW(TEST_PTR_SIZE));

  free(test_ptr);
}

#define CHMOD_FAKE_PATH "/path/for/chmod"
#define CHMOD_FAKE_MODE (S_IRUSR | S_IWUSR)
AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_STRING)
{
  chmod(CHMOD_FAKE_PATH, CHMOD_FAKE_MODE);

  AUM_ASSERT_WAS_CALLED_WITH_AT("chmod", 0, AUM_PARAMETER_STRING(CHMOD_FAKE_PATH));
  AUM_ASSERT_WAS_CALLED_WITH_AT("chmod", 1, AUM_PARAMETER_RAW(CHMOD_FAKE_MODE));
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH__should_succeed)
{
    chmod(CHMOD_FAKE_PATH, CHMOD_FAKE_MODE);
    AUM_ASSERT_WAS_CALLED_WITH("chmod",
			       AUM_PARAMETER_STRING(CHMOD_FAKE_PATH),
			       AUM_PARAMETER_RAW(CHMOD_FAKE_MODE));
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH__should_succeed_with_malloc)
{
    char *test_ptr = malloc(10);
    AUM_ASSERT_PTR_NOT_NULL(test_ptr);

    AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
    free(test_ptr);
}

AUM_TEST(AUM_ASSERT_WAS_CALLED__should_succeed_with_function_without_arguments)
{
  getuid();
  AUM_ASSERT_WAS_CALLED("getuid");
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH__should_succeed_if_matching_call_is_present_once)
{
    char *test_ptr1 = malloc(0);
    AUM_ASSERT_PTR_NOT_NULL(test_ptr1);
    char *test_ptr2 = malloc(10);
    AUM_ASSERT_PTR_NOT_NULL(test_ptr2);

    AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
    free(test_ptr2);
    free(test_ptr1);
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH__should_not_interleave_parameters)
{
    chmod("path1", S_IRUSR);
    chmod("path2", S_IWUSR);
    AUM_ASSERT_WAS_CALLED_WITH("chmod", AUM_PARAMETER_STRING("path1"), AUM_PARAMETER_RAW(S_IWUSR));
}

AUM_TEST(AUM_ASSERT_WAS_CALLED_WITH_AT__should_accept_additional_messages_to_print_in_case_of_failure)
{
  char *test_ptr = malloc(TEST_PTR_SIZE);
  // this assert is necessary, otherwise the compiler may optimize the allocation away!
  AUM_ASSERT_PTR_NOT_NULL(test_ptr);
  free(test_ptr);
  int expected = TEST_PTR_SIZE + 1;
  AUM_ASSERT_WAS_CALLED_WITH_AT("malloc", 0, AUM_PARAMETER_RAW(expected), " - Expected to be called with %d, but was called with %d, as first argument", expected, aum_mock_get_parameter_at("malloc", 0));
}

AUM_TEST(AUM_ASSERT_CALL_COUNT_EQUAL__should_indicated_actual_call_count_on_failure)
{
  AUM_ASSERT_CALL_COUNT_EQUAL("malloc", 1);
}

static void _vasprintf(const char *fmt, ...)
{
    char *strp;
    va_list additional_messages;
    va_start(additional_messages, fmt);
    vasprintf(&strp, fmt, additional_messages);
    va_end(additional_messages);
    free(strp);
}

AUM_TEST(method_with_va_list_argument__should_not_fail_when_called)
{
    _vasprintf("");
}

AUM_TEST(longjmp_mock__should_not_fail_when_called)
{
    jmp_buf env;
    if (setjmp(env) == 0) {
        longjmp(env, 1);
    }
}

AUM_TEST(longjmp_mock__should_define_mock_to_do_nothing)
{
    aum_mock_will_skip("longjmp");
    jmp_buf env;
    if (setjmp(env) == 0) {
        longjmp(env, 1);
    }
}

/******************************************************************************
 * Suite de tests                                                             *
 ******************************************************************************/


AUM_TEST_SUITE(test_suite_with_mock,
               &aum_mock_will_return__should_succeed,
               &aum_mock_will_return__should_modify_behavior_of_all_subsequent_calls,
               &aum_mock_reset__should_clean_will_return,
               &aum_mock_will_return_at_third_call__should_succeed,
               &aum_mock_will_return_at__should_ignore_preceding_calls_to_the_mock,
               &aum_mock_will_execute__should_install_fake_function,
               &aum_mock_get_call_count__should_count_function_calls,
               &aum_mock_reset__should_clean_call_count,
               &AUM_ASSERT_WAS_CALLED__should_succeed_if_function_called,
               &AUM_ASSERT_WAS_CALLED__should_failed_if_function_not_called,
               &AUM_ASSERT_CALL_COUNT_EQUAL__should_succeed,
               &aum_mock_arguments_register__should_register_last_call_arguments,
               &AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_RAW,
               &AUM_ASSERT_WAS_CALLED_WITH_AT__should_succeed_with_STRING,
               &AUM_ASSERT_WAS_CALLED_WITH__should_succeed,
               &AUM_ASSERT_WAS_CALLED_WITH__should_succeed_with_malloc,
               &AUM_ASSERT_WAS_CALLED__should_succeed_with_function_without_arguments,
               &AUM_ASSERT_WAS_CALLED_WITH__should_succeed_if_matching_call_is_present_once,
               &AUM_ASSERT_WAS_CALLED_WITH__should_not_interleave_parameters,
               &AUM_ASSERT_WAS_CALLED_WITH_AT__should_accept_additional_messages_to_print_in_case_of_failure,
               &AUM_ASSERT_CALL_COUNT_EQUAL__should_indicated_actual_call_count_on_failure,
               &method_with_va_list_argument__should_not_fail_when_called,
               &longjmp_mock__should_not_fail_when_called,
               &longjmp_mock__should_define_mock_to_do_nothing);

