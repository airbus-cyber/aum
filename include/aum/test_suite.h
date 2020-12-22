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
#include <aum/test.h>


// TODO all the field should be const (char * const name, etc...) Do it in the other non opaque structure too.
typedef struct {
    char *name;
    aum_test_t **tests;
    unsigned int test_count;
} aum_test_suite_t;

#define _ARRAY_LENGTH(__array) sizeof(__array)/sizeof(*__array)

#define _TESTS_ARRAY(__name) _ ## __name ## _array

/*! \brief Enregistement d'une suite de tests
 *
 * FIXME Explications sur le format des arguments
 * FIXME : dégager les parametres __setup, __teardown à récupérer automatiquement
 */
#define AUM_TEST_SUITE(__name, __tests...)                 \
static aum_test_t* _TESTS_ARRAY(__name)[] = { __tests };   \
     aum_test_suite_t __name = {                           \
         .name = #__name,                                  \
         .tests = _TESTS_ARRAY(__name),                    \
         .test_count = _ARRAY_LENGTH(_TESTS_ARRAY(__name)) \
     };

