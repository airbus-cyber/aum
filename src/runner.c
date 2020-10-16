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

#include <test_framework.h>
#include <mock_library.h>
#include <mock.h>
#include <test_suite_list.h>
#include <file_stream.h>
#include <runner.h>


struct aum_runner_s {
    test_suite_list_t *suites;
};


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
    if (test_framework_has_failures()) {
        return AUM_FAILURE;
    }
    return AUM_SUCCESS;
}


aum_runner_t *runner_create(aum_test_suite_t *test_suites[], int test_suites_count)
{
    _print_banner();
    if (!test_framework_initialize()) {
        return NULL;
    }
    mock_library_initialize();
    aum_runner_t *this = (aum_runner_t *) malloc(sizeof(aum_runner_t));
    this->suites = NULL;

    for (int i = 0; i < test_suites_count; i++) {
        // TODO error code not handled here!!!!!!!! (careful of leaks too)
        runner_register_suite(this, test_suites[i]);
    }

    return this;
}

bool runner_register_suite(aum_runner_t *this, aum_test_suite_t *suite)
{
    this->suites = test_suite_list_append(this->suites, suite);
    return test_framework_register_suite(suite);
}

aum_runner_result_t runner_execute_tests(aum_runner_t *this)
{
    int ignored_tests_count = test_suite_list_count_ignored_tests(this->suites);
    bool result = test_framework_run(ignored_tests_count);
    return _convert_run_result(result);
}

bool runner_print_xml_report(aum_runner_t *this, const char *output_filename)
{
    file_stream_t *output_stream = file_stream_create(output_filename);
    if (output_stream == NULL) {
        return false;
    }
    bool result = test_framework_print_xml_report(output_stream, this->suites);
    file_stream_destroy(output_stream);
    return result;
}

void runner_destroy(aum_runner_t *this)
{
    test_framework_cleanup();
    test_suite_list_destroy(this->suites);
    mock_library_destroy();
    free(this);
}

aum_runner_t *aum_runner_create()
{
    return runner_create(NULL, 0);
}

bool aum_runner_register_suite(aum_runner_t *this, aum_test_suite_t *suite)
{
    return runner_register_suite(this, suite);
}

aum_runner_result_t aum_runner_execute_tests(aum_runner_t *this)
{
    return runner_execute_tests(this);
}

aum_runner_result_t aum_runner_execute_single_test(__attribute__((unused)) aum_runner_t *this, const char *suite_name, const char *test_name)
{
    bool result = test_framework_run_single_test(suite_name, test_name);
    return _convert_run_result(result);
}

bool aum_runner_print_xml_report(aum_runner_t *this, const char *output_filename)
{
    return runner_print_xml_report(this, output_filename);
}

void aum_runner_destroy(aum_runner_t *this)
{
    runner_destroy(this);
}

