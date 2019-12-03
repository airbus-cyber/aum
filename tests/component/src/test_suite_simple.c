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


#include <aum.h>
#include <test/test_suites.h>
/******************************************************************************
 * Implémentation des tests de la suite "Suite Simple"                        *
 ******************************************************************************/

AUM_TEST(AUM_FAIL__should_always_fail)
{
  AUM_FAIL("Echec volontaire du test000");
}

AUM_TEST(AUM_ASSERT_EQUAL__should_succeed_with_same_values)
{
  AUM_ASSERT_EQUAL(1, 1);
}

AUM_TEST(AUM_ASSERT_EQUAL__should_fail_with_different_values)
{
  AUM_ASSERT_EQUAL(1, 0);
}

AUM_TEST(AUM_ASSERT_STRING_EQUAL__should_succeed_with_same_strings)
{
  AUM_ASSERT_STRING_EQUAL(__func__, __func__);
}

AUM_TEST(AUM_ASSERT_STRING_EQUAL__should_fail_with_different_strings)
{
  AUM_ASSERT_STRING_EQUAL("true", "false");
}

AUM_TEST(AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer)
{
  AUM_ASSERT_PTR_NULL(NULL);
}

AUM_TEST(AUM_ASSERT_PTR_NULL__should_fail_with_non_NULL_pointer)
{
  void *fake_ptr = (void *)0xdeadbeef;

  AUM_ASSERT_PTR_NULL(fake_ptr);
}

AUM_TEST(AUM_ASSERT_PTR_NOT_NULL__should_succeed_with_non_NULL_pointer)
{
  void *fake_ptr = (void *)0xdeadbeef;

  AUM_ASSERT_PTR_NOT_NULL(fake_ptr);
}

AUM_TEST(AUM_ASSERT_PTR_NOT_NULL__should_fail_with_NULL_pointer)
{
  AUM_ASSERT_PTR_NOT_NULL(NULL);
}

AUM_TEST(AUM_ASSERT_PTR_EQUAL__should_succeed_with_same_pointer)
{
  AUM_ASSERT_PTR_EQUAL(NULL, NULL);
}

AUM_TEST(AUM_ASSERT_PTR_EQUAL__should_fail_with_different_pointers)
{
  void *fake_ptr = (void *)0xdeadbeef;

  AUM_ASSERT_PTR_EQUAL(NULL, fake_ptr);
}

AUM_TEST(AUM_FAIL__should_stop_test_execution)
{
  AUM_FAIL("First failure");
  AUM_FAIL("Should not print this\n");
}

AUM_TEST(AUM_ASSERT_EQUAL__should_print_runtime_value)
{
  int x = 0;
  AUM_ASSERT_EQUAL(1, x, "Expected x to be 1, but was %d", x);
}

AUM_TEST_IGNORE(AUM_TEST_IGNORE__should_skip_the_test)
{
}

AUM_TEST(AUM_FAIL_can_print_a_value)
{
  int x = 0;
  AUM_FAIL("The value of x is %d", x);
}

AUM_TEST(AUM_ASSERT_MEMORY_EQUAL__should_succeed_with_same_array_content)
{
    char a[] = { 1, 2, 3 };
    char b[] = { 1, 2, 3 };
    AUM_ASSERT_MEMORY_EQUAL(a, b, 3);
}

AUM_TEST(AUM_ASSERT_MEMORY_EQUAL__should_fail_with_different_array_content)
{
    AUM_ASSERT_MEMORY_EQUAL("hello", "world", 3);
}

/******************************************************************************
 * Déclaration et enregistrement de la suite de tests                         *
 ******************************************************************************/

AUM_TEST_SUITE(test_suite_simple,
               &AUM_FAIL__should_always_fail,
               &AUM_ASSERT_EQUAL__should_succeed_with_same_values,
               &AUM_ASSERT_EQUAL__should_fail_with_different_values,
               &AUM_ASSERT_STRING_EQUAL__should_succeed_with_same_strings,
               &AUM_ASSERT_STRING_EQUAL__should_fail_with_different_strings,
               &AUM_ASSERT_PTR_NULL__should_succeed_with_NULL_pointer,
               &AUM_ASSERT_PTR_NULL__should_fail_with_non_NULL_pointer,
               &AUM_ASSERT_PTR_NOT_NULL__should_succeed_with_non_NULL_pointer,
               &AUM_ASSERT_PTR_NOT_NULL__should_fail_with_NULL_pointer,
               &AUM_ASSERT_PTR_EQUAL__should_succeed_with_same_pointer,
               &AUM_ASSERT_PTR_EQUAL__should_fail_with_different_pointers,
               &AUM_FAIL__should_stop_test_execution,
               &AUM_ASSERT_EQUAL__should_print_runtime_value,
               &AUM_TEST_IGNORE__should_skip_the_test,
               &AUM_FAIL_can_print_a_value,
               &AUM_ASSERT_MEMORY_EQUAL__should_succeed_with_same_array_content,
               &AUM_ASSERT_MEMORY_EQUAL__should_fail_with_different_array_content);

