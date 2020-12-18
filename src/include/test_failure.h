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

#include <stdarg.h>

#include <file_stream.h>


typedef struct test_failure_s test_failure_t;

test_failure_t *test_failure_create(const char *file_name, unsigned int line_number, char *error_message_format, ...);

test_failure_t *test_failure_vcreate(const char *file_name, unsigned int line_number, char *error_message_format, va_list additional_messages);

typedef void test_failure_write_callback_t(void *context, const char *file_name, unsigned int line_number, char *error_message);

void test_failure_print_xml(test_failure_t *this, file_stream_t *output_stream);

void test_failure_print(test_failure_t *this);

void test_failure_destroy(test_failure_t *this);

