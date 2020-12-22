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
#include <stddef.h>
#include <stdint.h>

// FIXME : DELETE ONCE aum_parameter_t has been moved from asserts.h
#include <aum/asserts.h>

// FIXME : WARN on 32 bits no 64 bits types !!!
typedef unsigned long mock_argument_t;

typedef struct mock_s mock_t;

void aum_mock_will_return(const char *function_name, unsigned long return_value);

/*! \brief Configures a mock so that it does nothing when called. Valid only for mock of functions with a void return type.
 *
 * \param[in]   function_name   Named of the mocked function
 */
void aum_mock_will_skip(const char *function_name);

void aum_mock_will_return_at(const char *function_name, unsigned long return_value, size_t call_number);

void aum_mock_will_execute(const char *function_name, void *function_ptr);

void aum_mock_reset(void);

size_t aum_mock_get_call_count(const char *function_name);

mock_argument_t aum_mock_get_parameter_at(const char *function_name, unsigned int position);

bool aum_mock_was_called_with_at(const char *function_name, unsigned int position, aum_parameter_t *param);

bool aum_mock_was_called_with(const char *function_name, ...);

