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


#pragma once

#include <aum/test_suite.h>
#include <test_report.h>


typedef struct test_suite_report_s test_suite_report_t;

test_suite_report_t *test_suite_report_create(aum_test_suite_t *test_suite);

void test_suite_report_increment_statistics(test_suite_report_t *this, unsigned int *ran_tests_count, unsigned int *ignored_tests_count, unsigned int *failed_tests_count);

void test_suite_report_print_xml(test_suite_report_t *this, file_stream_t *output_stream);

void test_suite_report_run(test_suite_report_t *this);

void test_suite_report_break_on_failure(test_suite_report_t *this, test_failure_t *failure);

void test_suite_report_destroy(test_suite_report_t *this);

