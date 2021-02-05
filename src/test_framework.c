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

#include <runner.h>
#include <mock_library.h>
#include <mock.h>
#include <test_suite_list.h>
#include <file_stream.h>
#include <test_framework.h>


// This is the only global in the whole program and it should remain so
static runner_t *_runner;

static void _print_banner(void)
{
    printf("\n\tAUM - All Ur Mocks are belongs to us - Version %s\n", _AUM_VERSION);
    printf("\tCopyright Airbus Defence and Space CyberSecurity\n\n");
}

static bool _initialize(aum_test_suite_t *test_suites[], unsigned int test_suites_count)
{
    _runner = runner_create(test_suites, test_suites_count);
    if (_runner == NULL) {
        return false;
    }
    _print_banner();

    return true;
}

static bool _execute_tests(void)
{
    return runner_execute_tests(_runner);
}

static bool _print_xml_report(const char *output_filename)
{
    file_stream_t *output_stream = file_stream_create(output_filename);
    if (output_stream == NULL) {
        return false;
    }
    bool result = runner_print_xml_report(_runner, output_stream);
    file_stream_destroy(output_stream);
    return result;
}

static void _cleanup(void)
{
    runner_free(_runner);
    _runner = NULL;
}

bool test_framework_run_test_suites(aum_test_suite_t *test_suites[], unsigned int test_suites_count, char *xml_output_path)
{
    if (!_initialize(test_suites, test_suites_count)) {
        return false;
    }

    bool result = _execute_tests();
    if (xml_output_path != NULL) {
        _print_xml_report(xml_output_path);
    }

    _cleanup();
    return result;
}

void test_framework_vassert(bool expression, unsigned int line_number, const char *file_name, char *error_message_format, va_list additional_messages)
{
    runner_vassert(_runner, expression, line_number, file_name, error_message_format, additional_messages);
}

mock_t *test_framework_search_mock(const char *name)
{
    if (_runner == NULL) {
        return NULL;
    }
    return runner_search_mock(_runner, name);
}

void test_framework_reset_mocks(void)
{
    runner_reset_mocks(_runner);
}

