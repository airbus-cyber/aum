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

#include <stdbool.h>

#include <test_failure.h>
#include <file_stream.h>
#include <aum/test.h>

typedef struct test_report_s test_report_t;

typedef void test_report_function_t(test_report_t *this, void *context);

test_report_t *test_report_create(aum_test_t *test);

void test_report_run(test_report_t *this);

void test_report_break_on_failure(test_report_t *this, test_failure_t *failure);

void test_report_print_xml(test_report_t *this, file_stream_t *output_stream, char *suite_name);

bool test_report_is_ignored(test_report_t *this);

bool test_report_has_failure(test_report_t *this);

void test_report_destroy(test_report_t *this);

