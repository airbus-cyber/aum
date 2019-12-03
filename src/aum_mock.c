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
#include <aum/mock.h>
#include <aum/asserts.h>
/* PKG Private Includes */
#include <mock_library.h>
#include <mock_call_sequence.h>
#include <error.h>

static mock_t *_search_mock(const char *function_name)
{
    mock_t *result = mock_library_search_mock(function_name);
    if (result == NULL) {
        error("%s: failed to find %s in the registered mocks\n", __func__, function_name);
    }
    return result;
}

void aum_mock_will_execute(const char *function_name, void *function_ptr)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_fake_function_set(target_mock, function_ptr);
}

void aum_mock_will_return(const char *function_name, unsigned long return_value)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_return_set(target_mock, return_value);
}

void aum_mock_will_return_at(const char *function_name, unsigned long return_value, size_t call_number)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_return_set_at(target_mock, return_value, call_number);
}

void aum_mock_reset(void)
{
    mock_library_reset();
}

size_t aum_mock_get_call_count(const char *function_name)
{
    mock_t *target_mock = _search_mock(function_name);
    return mock_call_count_get(target_mock);
}

mock_argument_t aum_mock_get_parameter_at(const char *function_name, int position)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_argument_t argument;
    if (!mock_get_argument(target_mock, position, &argument)) {
        error("Function '%s' was never called. Failed to retrieve argument at position %d.", function_name, position);
    }
    return argument;
}

bool aum_mock_was_called_with_at(const char *function_name, int position, aum_parameter_t * param)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_call_sequence_t *calls = mock_get_calls(target_mock);
    return mock_call_sequence_contains_at(calls, param, position);
}

static bool _vaum_mock_was_called_with(const char *function_name, va_list arguments)
{
    mock_t *target_mock = _search_mock(function_name);
    mock_call_sequence_t *calls = mock_get_calls(target_mock);
    return mock_call_sequence_contains(calls, arguments);
}

// TODO we make the assumption that the number of parameters passed is equal to the number of parameters expected by the function => document
bool aum_mock_was_called_with(const char *function_name, ...)
{
    va_list arguments;
    va_start(arguments, function_name);
    bool result = _vaum_mock_was_called_with(function_name, arguments);
    va_end(arguments);
    return result;
}
