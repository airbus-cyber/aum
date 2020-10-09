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
#include <mock_library.h>
#include <mock_list.h>

// TODO should remove the static here and put it somewhere else to group together the whole global state with its API
static mock_list_t *_mock_list = NULL;
// TODO why is this boolean needed?
static bool _is_initialized = false;

void mock_library_initialize(void)
{
    _is_initialized = true;
}

void mock_library_reset(void)
{
    mock_list_destroy(_mock_list);
    _mock_list = NULL;
}

void mock_library_destroy(void)
{
    mock_list_destroy(_mock_list);
    _mock_list = NULL;
    _is_initialized = false;
}

static mock_t *_add_mock(const char *function_name)
{
    mock_t *mock = mock_alloc(function_name);
    if (mock == NULL) {
        return NULL;
    }
    mock_list_t *new_mock_list = mock_list_append(_mock_list, mock);
    if (new_mock_list == NULL) {
        mock_free(mock);
        return NULL;
    }
    _mock_list = new_mock_list;
    return mock;
}

mock_t *mock_library_search_mock(const char *name)
{
    if (!_is_initialized) {
        return NULL;
    }
    mock_t *mock = mock_list_search(_mock_list, name);
    if (mock == NULL) {
        mock = _add_mock(name);
    }
    return mock;
}

