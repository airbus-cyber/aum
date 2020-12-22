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
#include <stdarg.h>
#include <file_stream.h>
#include <test_suite_list.h>
#include <mock.h>
#include <aum/test_suite.h>

typedef struct runner_s runner_t;

runner_t *runner_create(aum_test_suite_t *test_suites[], int test_suites_count);

bool runner_execute_tests(runner_t *this);

bool runner_print_xml_report(runner_t *this, file_stream_t *output_stream);

void runner_vassert(runner_t *this, bool expression, unsigned int line_number, const char *file_name, char *error_message_format, va_list additional_messages);

mock_t *runner_search_mock(runner_t *this, const char *name);

void runner_reset_mocks(runner_t *this);

void runner_free(runner_t *this);


