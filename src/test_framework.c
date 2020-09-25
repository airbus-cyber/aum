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


#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
/* PKG Internal Includes */
#include <test_framework.h>
#include <mock_library.h>
#include <tests.h>

/******************************************************************************
 * Implémentation des fonctions publiques de l'interface                      *
 ******************************************************************************/

bool test_framework_initialize(void)
{
  return (CU_initialize_registry() == CUE_SUCCESS);
}

void test_framework_cleanup(void)
{
    CU_cleanup_registry();
}

// TODO do not forget to propagate the error code up!
// TODO iterate on tests to get the size (until NULL, NULL)
//      then allocate a new array of CU_TestInfo => will need to return an error code
//      copy the elements in there (instead of the cast)
//      after register is done => deallocate the array
bool test_framework_register_suite(aum_test_suite_t *suite)
{
    CU_TestInfo *tests = (CU_TestInfo *) calloc(suite->test_count+1, sizeof(CU_TestInfo));
    if (tests == NULL) {
        return false;
    }
    for (int i = 0, j = 0; i < suite->test_count; i++) {
        aum_test_t *current_test = suite->tests[i];
        if (current_test->ignored) {
            continue;
        }
        tests[j].pName = current_test->name;
        tests[j].pTestFunc = current_test->test_function;
        j++;
    }
    CU_SuiteInfo suite_registry[] = {CU_SUITE_INFO_NULL, CU_SUITE_INFO_NULL};
    suite_registry[0].pName = suite->name;
    suite_registry[0].pTests = tests;
    CU_ErrorCode result = CU_register_suites(suite_registry);
    free(tests);
    return (result == CUE_SUCCESS);
}

/* TODO could build the xml report as a separated function after the test run with this code: */
static int _count_suite_failures(CU_pSuite current_suite, CU_pFailureRecord current_failure)
{
    int result = 0;
    while (current_failure != NULL && current_failure->pSuite == current_suite) {
        result++;
        current_failure = current_failure->pNext;
    }
    return result;
}

static void _print_xml_report_failure(file_stream_t *output_stream, CU_pFailureRecord failure)
{
    file_stream_write(output_stream, "\t\t<failure>\n");
    file_stream_write(output_stream, "Test failed at line %d in file %s: %s\n", failure->uiLineNumber, failure->strFileName, failure->strCondition);
    file_stream_write(output_stream, "\t\t</failure>\n");
}


// TODO I am not 100% fan of the current_failure. Should ideally split in two parts: build a clean report structure. And then print.
static CU_pFailureRecord _print_xml_report_test(file_stream_t *output_stream, char *suite_name, CU_pTest test, CU_pFailureRecord current_failure)
{
    file_stream_write(output_stream, "\t<testcase classname=\"%s\" name=\"%s\" time=\"0.0\">\n", suite_name, test->pName);
    while (current_failure != NULL && current_failure->pTest == test) {
        _print_xml_report_failure(output_stream, current_failure);
        current_failure = current_failure->pNext;
    }
    file_stream_write(output_stream, "\t</testcase>\n");
    return current_failure;
}

static void _print_xml_report_ignored_test(file_stream_t *output_stream, char *suite_name, char *test_name)
{
    file_stream_write(output_stream, "\t<testcase classname=\"%s\" name=\"%s\" time=\"0.0\">\n", suite_name, test_name);
    file_stream_write(output_stream, "\t\t<skipped />\n");
    file_stream_write(output_stream, "\t</testcase>\n");
}

// TODO should move this code out => should just fill the results in the data-structure of a aum_test and then exit
//      would also be cleaner since tests would be printed in the right order (rather than having the ignored tests at the end)
static CU_pFailureRecord _print_xml_report_suite(file_stream_t *output_stream, CU_pSuite cu_suite, CU_pFailureRecord current_failure, aum_test_suite_t *suite)
{
    int ignored_tests_count = aum_test_suite_count_ignored_tests(suite);
    int failure_count = _count_suite_failures(cu_suite, current_failure);
    file_stream_write(output_stream,
          "<testsuite name=\"%s\" tests=\"%d\" errors=\"%d\" failures=\"0\" skipped=\"%d\">\n",
          cu_suite->pName, cu_suite->uiNumberOfTests, failure_count, ignored_tests_count);
    for (CU_pTest current_test = cu_suite->pTest; current_test != NULL; current_test = current_test->pNext) {
        current_failure = _print_xml_report_test(output_stream, cu_suite->pName, current_test, current_failure);
    }
    for (int i = 0; i < suite->test_count; i++) {
        aum_test_t *current_test = suite->tests[i];
        if (!current_test->ignored) {
            continue;
        }
        _print_xml_report_ignored_test(output_stream, cu_suite->pName, current_test->name);
    }
    file_stream_write(output_stream, "</testsuite>\n");
    return current_failure;
}

bool test_framework_has_failures()
{
  return (CU_get_number_of_tests_failed() != 0);
}

static void _stdout_before_suite_handler(const CU_pSuite suite)
{
  printf("Suite: %s...\n", suite->pName);
}

static void _stdout_after_suite_handler(const CU_pSuite __attribute__((unused)) suite,
                                        const CU_pFailureRecord __attribute__((unused)) failure)
{
  printf("\n\n");
}

static void _stdout_before_test_handler(const CU_pTest test,
                                        const CU_pSuite __attribute__((unused)) suite)
{
  printf("\tTest: %s... ", test->pName);
}

static void _stdout_after_test_handler(const CU_pTest __attribute__((unused)) test,
                                       const CU_pSuite __attribute__((unused)) suite,
                                       const CU_pFailureRecord failure)
{
    if (failure == NULL) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
        for (CU_pFailureRecord current_failure = failure; current_failure != NULL; current_failure = current_failure->pNext) {
            printf("\t\t%s:%d - %s\n", current_failure->strFileName, current_failure->uiLineNumber, current_failure->strCondition);
        }
    }
    tests_common_after_test_handler();
}

static void _cunit_print_results(int ignored_tests_count)
{
    CU_pRunSummary run_summary = CU_get_run_summary();
    if (run_summary == NULL) {
        printf("Oooopsss... No run summary found, problem somewhere...\n");
        return;
    }
    printf("Run summary:\tType\tRan\tIgnored\tPassed\tFailed\n");
    printf("            \tsuites\t%d\t0\t%d\t%d\n",
           run_summary->nSuitesRun + run_summary->nSuitesFailed,
           run_summary->nSuitesRun, run_summary->nSuitesFailed);
    printf("            \ttests\t%u\t%u\t%u\t%u\n",
           run_summary->nTestsRun, ignored_tests_count,
           run_summary->nTestsRun - run_summary->nTestsFailed, run_summary->nTestsFailed);
}

bool test_framework_print_xml_report(file_stream_t *output_stream, test_suite_list_t *suites) 
{
    file_stream_write(output_stream, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    file_stream_write(output_stream, "<testsuites>\n");

    CU_pTestRegistry registry = CU_get_registry();
    CU_pFailureRecord current_failure = CU_get_failure_list();
    CU_pSuite current_suite = registry->pSuite;
    while (current_suite != NULL) {
        aum_test_suite_t *suite = test_suite_list_search(suites, current_suite->pName);
        current_failure = _print_xml_report_suite(output_stream, current_suite, current_failure, suite);
        current_suite = current_suite->pNext;
    }

    file_stream_write(output_stream, "</testsuites>\n");
    return file_stream_get_status(output_stream);
}

static void _register_run_handlers(void)
{
    CU_set_test_start_handler(_stdout_before_test_handler);
    CU_set_test_complete_handler(_stdout_after_test_handler);
    CU_set_suite_start_handler(_stdout_before_suite_handler);
    CU_set_suite_complete_handler(_stdout_after_suite_handler);
}

bool test_framework_run(int ignored_tests_count)
{
    _register_run_handlers();
    CU_ErrorCode result = CU_run_all_tests();
    _cunit_print_results(ignored_tests_count);

    return (result == CUE_SUCCESS);
}

bool test_framework_run_single_test(const char *suite_name, const char *test_name)
{
    CU_pTestRegistry registry = CU_get_registry();
    if (registry == NULL) {
        return false;
    }
    CU_pSuite suite = CU_get_suite_by_name(suite_name, registry);
    if (suite == NULL) {
        return false;
    }
    CU_pTest test = CU_get_test_by_name(test_name, suite);
    if (test == NULL) {
        return false;
    }

    _register_run_handlers();
    CU_ErrorCode result = CU_run_test(suite, test);
    _cunit_print_results(0);

    return (result == CUE_SUCCESS);
}

void test_framework_vassert(bool expression, unsigned int line_number, const char *file_name, char *error_message_format, va_list additional_messages) 
{
    char *error_message;
    if (!vasprintf(&error_message, error_message_format, additional_messages)) {
        // log an error in this case?
        error_message = NULL;
    }
    CU_assertImplementation(expression, line_number, error_message, file_name, "", CU_FALSE);
    free(error_message);
    if (!expression) {
        CU_pTest current_test = CU_get_current_test();
        longjmp(*(current_test->pJumpBuf), 1);
    }
}

