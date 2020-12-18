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
#include <test_suite_report.h>


struct test_suite_report_s {
    char *name;
    test_report_t **tests;
    unsigned int test_count;
    test_report_t *current_test;
};

// TODO factor this method
static bool _any_is_null(void *array, unsigned int count) {
    void **elements = (void **) array;
    for (unsigned int i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return true;
        }
    }

    return false;
}

static void _free_all(void *array, unsigned int count) {
    test_report_t **elements = array;
    for (unsigned int i = 0; i < count; i++) {
        test_report_destroy(elements[i]);
    }
}

// TODO factor with code in test_run_report.c
static bool _free_if_any_is_null(void *elements, unsigned int count) {
    if (_any_is_null(elements, count)) {
        _free_all(elements, count);
        return true;
    }
    return false;
}

static test_report_t **_create_array_of_test_reports(aum_test_suite_t *test_suite, unsigned int test_count) {
    test_report_t **tests = calloc(sizeof(test_report_t *), test_count);
    if (tests == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < test_count; i++) {
        aum_test_t *test = test_suite->tests[i];
        tests[i] = test_report_create(test);
    }

    if (_free_if_any_is_null(tests, test_count)) {
        return NULL;
    }

    return tests;
}

static void _destroy_array_of_test_reports(test_report_t **tests, unsigned int test_count) {
    if (tests == NULL) {
        return;
    }
    _free_all(tests, test_count);
    free(tests);    
}

test_suite_report_t *test_suite_report_create(aum_test_suite_t *test_suite) {
    unsigned int test_count = test_suite->test_count;
    test_report_t **tests = _create_array_of_test_reports(test_suite, test_count);
    test_suite_report_t *this = malloc(sizeof(test_suite_report_t));
    if (tests == NULL || this == NULL) {
        _destroy_array_of_test_reports(tests, test_count);
        free(this);
        return NULL;
    }

    this->name = test_suite->name;
    this->tests = tests;
    this->test_count = test_suite->test_count;

    return this;
}

static void _before_suite(test_suite_report_t *suite)
{
    printf("Suite: %s...\n", suite->name);
}

static void _run_suite(test_suite_report_t *this)
{
    for (unsigned int i = 0; i < this->test_count; i++) {
        this->current_test = this->tests[i];
        test_report_run(this->current_test);
    }
}

static void _after_suite(void)
{
    printf("\n\n");
}

void test_suite_report_run(test_suite_report_t *this)
{
    _before_suite(this);
    _run_suite(this);
    _after_suite();
}

void test_suite_report_break_on_failure(test_suite_report_t *this, test_failure_t *failure)
{
    test_report_break_on_failure(this->current_test, failure);
}

void test_suite_report_increment_statistics(test_suite_report_t *this, unsigned int *ran_tests_count, unsigned int *ignored_tests_count, unsigned int *failed_tests_count)
{
    for (unsigned int i = 0; i < this->test_count; i++) {
        test_report_t *test = this->tests[i];
        if (test_report_is_ignored(test)) {
            (*ignored_tests_count)++;
        } else {
            (*ran_tests_count)++;
        }
        if (test_report_has_failure(test)) {
            (*failed_tests_count)++;
        }
    }
}

void test_suite_report_print_xml(test_suite_report_t *this, file_stream_t *output_stream)
{
    char *suite_name = this->name;
    unsigned int ran_tests_count = 0;
    unsigned int ignored_tests_count = 0;
    unsigned int failed_tests_count = 0;
    test_suite_report_increment_statistics(this, &ran_tests_count, &ignored_tests_count, &failed_tests_count);
    file_stream_write(output_stream,
          "<testsuite name=\"%s\" tests=\"%d\" errors=\"%d\" failures=\"0\" skipped=\"%d\">\n",
          suite_name, ran_tests_count, failed_tests_count, ignored_tests_count);
    for (unsigned int i = 0; i < this->test_count; i++) {
        test_report_print_xml(this->tests[i], output_stream, suite_name);
    }
    file_stream_write(output_stream, "</testsuite>\n");
}

void test_suite_report_destroy(test_suite_report_t *this) {
    _destroy_array_of_test_reports(this->tests, this->test_count);
    free(this);
}
