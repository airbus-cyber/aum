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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <aum/runner.h>

#include <test_framework.h>
#include <mock_library.h>
#include <mock.h>
#include <test_suite_list.h>
#include <file_stream.h>
#include <runner.h>


struct aum_runner_s {
    test_suite_list_t *suites;
};

static mock_library_t *_mocks;


static void _print_banner(void)
{
    printf("\n\tAUM - All Ur Mocks are belongs to us - Version %s\n", _AUM_VERSION);
    printf("\tCopyright Airbus Defence and Space CyberSecurity\n\n");
}

static aum_runner_result_t _convert_run_result(bool result)
{
    if (!result) {
        return AUM_ERROR;
    }
    if (runner_has_failures()) {
        return AUM_FAILURE;
    }
    return AUM_SUCCESS;
}

static bool _register_suite(aum_runner_t *this, aum_test_suite_t *suite)
{
    this->suites = test_suite_list_append(this->suites, suite);
    return runner_register_suite(suite);
}

static aum_runner_t *_create(aum_test_suite_t *test_suites[], int test_suites_count)
{
    _print_banner();
    if (!runner_initialize()) {
        return NULL;
    }
    _mocks = mock_library_create();
    aum_runner_t *this = (aum_runner_t *) malloc(sizeof(aum_runner_t));
    this->suites = NULL;

    for (int i = 0; i < test_suites_count; i++) {
        // TODO error code not handled here!!!!!!!! (careful of leaks too)
        _register_suite(this, test_suites[i]);
    }

    return this;
}

static aum_runner_result_t _execute_tests(aum_runner_t *this)
{
    int ignored_tests_count = test_suite_list_count_ignored_tests(this->suites);
    bool result = runner_run(ignored_tests_count);
    return _convert_run_result(result);
}

static bool _print_xml_report(aum_runner_t *this, const char *output_filename)
{
    file_stream_t *output_stream = file_stream_create(output_filename);
    if (output_stream == NULL) {
        return false;
    }
    bool result = runner_print_xml_report(output_stream, this->suites);
    file_stream_destroy(output_stream);
    return result;
}

void test_framework_vassert(bool expression, unsigned int line_number, const char * file_name, char *error_message_format, va_list additional_messages)
{
    runner_vassert(expression, line_number, file_name, error_message_format, additional_messages);
}

static void _destroy(aum_runner_t *this)
{
    runner_cleanup();
    test_suite_list_destroy(this->suites);
    mock_library_destroy(_mocks);
    free(this);
}

bool test_framework_run_test_suites(aum_test_suite_t *test_suites[], int test_suites_count, char *xml_output_path) {
    aum_runner_t *runner = _create(test_suites, test_suites_count);
    if (runner == NULL) {
        return false;
    }

    aum_runner_result_t result = _execute_tests(runner);
    if (xml_output_path != NULL) {
        _print_xml_report(runner, xml_output_path);
    }

    _destroy(runner);
    if (result == AUM_ERROR) {
        return false;
    }
    return true;

}

mock_t *test_framework_search_mock(const char *name)
{
    if (_mocks == NULL) {
        return NULL;
    }
    return mock_library_search_mock(_mocks, name);
}

void test_framework_reset_mocks(void)
{
    mock_library_reset(_mocks);
}

