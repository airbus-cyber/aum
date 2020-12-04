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


/* PKG Public Includes */
#include <aum/asserts.h>
#include <aum_mock_create.h>
/* PKG Private Includes */
#include <mock_library.h>
#include <error.h>

static void *_get_fake(mock_t *mock, unsigned long *return_code, void *real_function)
{
    if (mock_return_get(mock, return_code)) {
        return NULL;
    }
    void *fake_function = mock_fake_function_get(mock);
    if (fake_function != NULL) {
        return fake_function;
    }
    return real_function;
}

static void _register_call(mock_t *mock, size_t arguments_count, mock_argument_t *values)
{
    mock_call_count_increment(mock);
    bool register_rc = mock_register_arguments(mock, arguments_count, values);
    if (!register_rc) {
        const char *function_name = mock_get_function_name(mock);
        error("Failed to register arguments for function '%s'\n", function_name);
    }
}

void *aum_mock_register_call(unsigned long *return_code, const char *function_name, void *real_function, size_t arguments_count, mock_argument_t *values)
{
    mock_t *mock = mock_library_search_mock(function_name);
    if (mock == NULL) {
        return real_function;
    }
    _register_call(mock, arguments_count, values);
    return _get_fake(mock, return_code, real_function);
}

