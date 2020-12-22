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


#include <test_suite_list.h>
#include <aum_test_suite.h>


test_suite_list_t *test_suite_list_append(test_suite_list_t *this, aum_test_suite_t *suite)
{
    return (test_suite_list_t *) list_append(this, suite);
}

static bool _test_suite_has_name(void *element, const char *name)
{
    aum_test_suite_t *test_suite = (aum_test_suite_t *) element;
    return aum_test_suite_has_name(test_suite, name);
}

aum_test_suite_t *test_suite_list_search(test_suite_list_t *this, const char *name)
{
    return list_search(this, _test_suite_has_name, name);
}

void test_suite_list_destroy(test_suite_list_t *this)
{
    list_destroy(this);
}

