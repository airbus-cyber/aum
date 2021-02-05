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

#include <aum.h>
#include <aum_mock_create.h>

#include <test_suite_mock_list.h>
#include <test_suite_test_failure.h>
#include <test_suite_test_report.h>
#include <test_suite_test_suite_report.h>
#include <test_suite_test_run_report.h>
#include <test_suite_test_framework.h>


AUM_MOCK_CREATE(int, vasprintf, char **, const char *, va_list);

static bool is_within_malloc_mock = false;


typedef void *(*malloc_t)(size_t size);

void *__real_malloc(size_t size);

void *__wrap_malloc (size_t size) {
    if (is_within_malloc_mock) {
        return __real_malloc(size);
    }
    is_within_malloc_mock = true;
    unsigned long return_code;
    mock_argument_t values[] = { (mock_argument_t) size };
    malloc_t mock_function = aum_mock_register_call(&return_code, "malloc", &__real_malloc, 1, values);
    is_within_malloc_mock = false;
    if (mock_function == NULL) {
        return (void *) return_code;
    }
    return mock_function(size);
}


AUM_MAIN_RUN(&test_suite_mock_list,
    &test_suite_test_failure,
    &test_suite_test_report,
    &test_suite_test_suite_report,
    &test_suite_test_run_report,
    &test_suite_test_framework
);

