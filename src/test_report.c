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
#include <stdio.h>
#include <setjmp.h>
#include <file_stream.h>
#include <test_report.h>
#include <aum/mock.h>


struct test_report_s {
    char *name;
    aum_test_function_t *test_function;
    bool ignored;
    test_failure_t *failure;
    jmp_buf environment_before_test;
};

test_report_t *test_report_create(aum_test_t *test)
{
    test_report_t *this = malloc(sizeof(test_report_t));
    if (this == NULL) {
        return NULL;
    }

    this->name = test->name;
    this->test_function = test->test_function;

    this->ignored = test->ignored;
    this->failure = NULL;

    return this;
}

static void _before_test(test_report_t *this)
{
    printf("\tTest: %s... ", this->name);
}

static void _run_test(test_report_t *this)
{
    if (setjmp(this->environment_before_test) == 0) {
        this->test_function();
    }
}

// TODO should check the return code of printfs too!!
static void _after_test(test_report_t *this)
{
    test_failure_t *failure = this->failure;
    if (failure == NULL) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
        test_failure_print(failure);
    }
    aum_mock_reset();
}

void test_report_run(test_report_t *this)
{
    if (this->ignored) {
        return;
    }
    _before_test(this);
    _run_test(this);
    _after_test(this);
}

void test_report_break_on_failure(test_report_t *this, test_failure_t *failure)
{
    this->failure = failure;
    longjmp(this->environment_before_test, 1);
}

void test_report_print_xml(test_report_t *this, file_stream_t *output_stream, char *suite_name)
{
    file_stream_write(output_stream, "\t<testcase classname=\"%s\" name=\"%s\" time=\"0.0\">\n", suite_name, this->name);
    if (this->ignored) {
        file_stream_write(output_stream, "\t\t<skipped />\n");
    }
    test_failure_t *failure = this->failure;
    if (failure != NULL) {
        test_failure_print_xml(failure, output_stream);
    }
    file_stream_write(output_stream, "\t</testcase>\n");
}

bool test_report_is_ignored(test_report_t *this)
{
    return this->ignored;
}

bool test_report_has_failure(test_report_t *this)
{
    return this->failure != NULL;
}


void test_report_destroy(test_report_t *this)
{
    if (this->failure != NULL) {
        test_failure_destroy(this->failure);
    }
    free(this);
}

