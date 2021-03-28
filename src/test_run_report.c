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
#include <aum/test_suite.h>
#include <test_run_report.h>


struct test_run_report_s {
    test_suite_report_t **suites;
    unsigned int suites_count;
    test_suite_report_t *current_suite;
};

static bool _any_is_null(void *array, unsigned int count) {
    void **elements = (void **) array;
    for (unsigned int i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            return true;
        }
    }

    return false;
}

// TODO factor with code in test_suite_report
static void _free_all(void *array, unsigned int count) {
    void **elements = (void **) array;
    for (unsigned int i = 0; i < count; i++) {
        test_suite_report_destroy(elements[i]);
    }
}

static void _destroy_array_of_test_suite_reports(test_suite_report_t **suites, unsigned int suites_count) {
    if (suites == NULL) {
        return;
    }
    _free_all(suites, suites_count);
    free(suites);
}

static test_suite_report_t **_create_array_of_test_suite_reports(aum_test_suite_t *suite_definitions[], unsigned int suites_count) {
    test_suite_report_t **suites = calloc(sizeof(test_suite_report_t *), suites_count);
    if (suites == NULL) {
        return NULL;
    }
    for (unsigned int i = 0; i < suites_count; i++) {
        suites[i] = test_suite_report_create(suite_definitions[i]);
    }
    if (_any_is_null(suites, suites_count)) {
        _free_all(suites, suites_count);
        free(suites);
        return NULL;
    }

    return suites;
}

test_run_report_t *test_run_report_create(aum_test_suite_t *suite_definitions[], unsigned int suites_count) {
    test_suite_report_t **suites = _create_array_of_test_suite_reports(suite_definitions, suites_count);
    test_run_report_t *this = malloc(sizeof(test_run_report_t));

    if (suites == NULL || this == NULL) {
        _destroy_array_of_test_suite_reports(suites, suites_count);
        free(this);
        return NULL;
    }

    this->suites = suites;
    this->suites_count = suites_count;

    return this;
}

static void _run_all_tests(test_run_report_t *this)
{
    for (unsigned int i = 0; i < this->suites_count; i++) {
        this->current_suite = this->suites[i];
        test_suite_report_run(this->current_suite);
    }
}

static void _print_results(test_run_report_t *this)
{
    unsigned int ran_tests_count = 0;
    unsigned int ignored_tests_count = 0;
    unsigned int failed_tests_count = 0;
    for (unsigned int i = 0; i < this->suites_count; i++) {
        test_suite_report_t *suite = this->suites[i];
        test_suite_report_increment_statistics(suite, &ran_tests_count, &ignored_tests_count, &failed_tests_count);
    }
    printf("Test suites: %d\n", this->suites_count);
    printf("Tests failed/executed: %d/%d\n", failed_tests_count, ran_tests_count);
    if (ignored_tests_count != 0) {
        printf("Tests skipped: %d\n", ignored_tests_count);
    }
}

void test_run_report_run_all_tests(test_run_report_t *this)
{
    _run_all_tests(this);
    _print_results(this);
}

void test_run_report_break_on_failure(test_run_report_t *this, test_failure_t *failure)
{
    test_suite_report_break_on_failure(this->current_suite, failure);
}

void test_run_report_print_xml(test_run_report_t *this, file_stream_t *output_stream)
{
    file_stream_write(output_stream, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    file_stream_write(output_stream, "<testsuites>\n");

    for (unsigned int i = 0; i < this->suites_count; i++) {
       test_suite_report_print_xml(this->suites[i], output_stream);
    }

    file_stream_write(output_stream, "</testsuites>\n");
}

void test_run_report_destroy(test_run_report_t *this) {
    if (this == NULL) {
        return;
    }
    _destroy_array_of_test_suite_reports(this->suites, this->suites_count);
    free(this);
}
