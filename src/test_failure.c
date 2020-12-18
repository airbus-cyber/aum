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
#include <test_failure.h>


struct test_failure_s {
    const char *file_name;
    unsigned int line_number;
    char *error_message;
};

static test_failure_t *_test_failure_create(const char *file_name, unsigned int line_number, char *error_message)
{
    test_failure_t *this = (test_failure_t *) malloc(sizeof(test_failure_t));
    if (this == NULL) {
        return NULL;
    }

    this->file_name = file_name;
    this->line_number = line_number;
    this->error_message = error_message;

    return this;
}

test_failure_t *test_failure_vcreate(const char *file_name, unsigned int line_number, char *error_message_format, va_list additional_messages)
{
    char *error_message;
    if (vasprintf(&error_message, error_message_format, additional_messages) < 0) {
        return NULL;
    }

    test_failure_t *this = _test_failure_create(file_name, line_number, error_message);
    if (this == NULL) {
        free(error_message);
    }
    return this;
}

test_failure_t *test_failure_create(const char *file_name, unsigned int line_number, char *error_message_format, ...)
{
    va_list additional_messages;
    va_start(additional_messages, error_message_format);
    test_failure_t *failure = test_failure_vcreate(file_name, line_number, error_message_format, additional_messages);
    va_end(additional_messages);
    return failure;
}

void test_failure_print_xml(test_failure_t *this, file_stream_t *output_stream)
{
    file_stream_write(output_stream, "\t\t<failure>\n");
    file_stream_write(output_stream, "Test failed at line %d in file %s: %s\n", this->line_number, this->file_name, this->error_message);
    file_stream_write(output_stream, "\t\t</failure>\n");
}

// TODO should check the return code of printfs too!!
void test_failure_print(test_failure_t *this)
{
    printf("\t\t%s:%d - %s\n", this->file_name, this->line_number, this->error_message);
}

void test_failure_destroy(test_failure_t *this)
{
    free(this->error_message);
    free(this);
}
