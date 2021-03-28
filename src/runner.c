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
#include <mock_library.h>
#include <test_run_report.h>
#include <runner.h>

// TODO do not forget to propagate the error code up!

struct runner_s {
    test_run_report_t *report;
    mock_library_t *mocks;
};

runner_t *runner_create(aum_test_suite_t *test_suites[], unsigned int test_suites_count)
{
    runner_t *this = malloc(sizeof(runner_t));
    if (this == NULL) {
        return NULL;
    }

    test_run_report_t *report = test_run_report_create(test_suites, test_suites_count);
    mock_library_t *mocks = mock_library_create();

    this->report = report;
    this->mocks = mocks;

    if (report == NULL || mocks == NULL) {
        runner_free(this);
        return NULL;
    }

    return this;
}

bool runner_execute_tests(runner_t *this)
{
    test_run_report_run_all_tests(this->report);

    // TODO should propagate an error until here, if there was an allocation error in an assert or in the mock (check if this can happen in the mocks created by aum_mock_create too, because we could longjmp in there too)
    return true;
}

bool runner_print_xml_report(runner_t *this, file_stream_t *output_stream) 
{
    test_run_report_print_xml(this->report, output_stream);
    return file_stream_get_status(output_stream);
}

void runner_vassert(runner_t *this, bool expression, unsigned int line_number, const char *file_name, char *error_message_format, va_list additional_messages)
{
    if (expression) {
        return;
    }

    test_failure_t *failure = test_failure_vcreate(file_name, line_number, error_message_format, additional_messages);
    if (failure == NULL) {
        // TODO should handle the case where the failure creation returns NULL by longjumping and stopping the execution with a message
        //      This can be done via the longjmp return value => add an enum to handle the different error cases
    }

    test_run_report_break_on_failure(this->report, failure);
}

mock_t *runner_search_mock(runner_t *this, const char *name)
{
    return mock_library_search_mock(this->mocks, name);
}

void runner_reset_mocks(runner_t *this)
{
    mock_library_reset(this->mocks);
}

void runner_free(runner_t *this)
{
    // TODO replace destroy by free everywhere (naming)
    test_run_report_destroy(this->report);
    mock_library_destroy(this->mocks);
    free(this);    
}

