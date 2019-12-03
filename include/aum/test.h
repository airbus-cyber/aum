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

typedef struct {
    char *name;
    void (*test_function)(void);
    bool ignored;
} aum_test_t;

#define _TEST_FUNCTION_NAME(__test_name__) _test_##__test_name__

#define _TEST_FUNCTION_DECLARATION(__test_name__) static void _TEST_FUNCTION_NAME(__test_name__)(void)

#define _TEST_DECLARATION(__test_name__, __ignored__)        \
    _TEST_FUNCTION_DECLARATION(__test_name__);               \
    static aum_test_t __test_name__ = {                      \
        .name = #__test_name__,                              \
        .test_function = _TEST_FUNCTION_NAME(__test_name__), \
        .ignored = __ignored__                               \
    };                                                       \
    _TEST_FUNCTION_DECLARATION(__test_name__)

/*! \brief Création d'un test */
#define AUM_TEST(__test_name__) _TEST_DECLARATION(__test_name__, false)

#define AUM_TEST_IGNORE(__test_name__) _TEST_DECLARATION(__test_name__, true)

