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


/*!
 * \file
 * \brief Interface fournissant les macros d'assertion à utiliser dans les tests
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/******************************************************************************
 * Types & Structures                                                         *
 ******************************************************************************/
typedef enum aum_parameter_type_e {
  AUM_PARAMETER_TYPE_STRING = 0,
  AUM_PARAMETER_TYPE_RAW
} aum_parameter_type_t;

typedef struct aum_parameter_s {
  aum_parameter_type_t type;
  union {
    unsigned long  raw;
    void          *ptr;
  } value;
} aum_parameter_t;

/******************************************************************************
 * Constantes                                                                 *
 ******************************************************************************/

#define AUM_PARAMETER_STRING(_s) (aum_parameter_t *)(&(aum_parameter_t){AUM_PARAMETER_TYPE_STRING, {.ptr = _s}})
#define AUM_PARAMETER_RAW(_r) (aum_parameter_t *)(&(aum_parameter_t){AUM_PARAMETER_TYPE_RAW, {_r}})

/******************************************************************************
 * Fonctions publiques de l'interface                                         *
 * Ces fonctions sont destinées à être utilisées dans les tests               *
 ******************************************************************************/

/*! \brief Assertion
 *
 * \param[in]           expression        Valeur de l'assertion
 * \param[in]           line_number       Ligne de l'assertion
 * \param[in]           condition         Condition testée
 * \param[in]           file_name         Nom du fichier contenant l'assertion
 */
void aum_assert(bool expression, unsigned int line_number, const char *file_name, char *format, ...);


/*! \def AUM_FAIL(message...)
 *
 * Echec du test courant avec affichage du message d'erreur \a msg
 */
#define AUM_FAIL(message...) aum_assert(false, __LINE__, __FILE__, "AUM_FAIL - " message)

/*! \def AUM_ASSERT_EQUAL(expected, actual)
 *
 * Succès si actual == expected
 */
#define AUM_ASSERT_EQUAL(expected, actual, additional_message...) \
    aum_assert(expected == actual, __LINE__, __FILE__, "AUM_ASSERT_EQUAL(" #expected ", " #actual ") - " additional_message)

/*! \def AUM_ASSERT_STRING_EQUAL(expected, actual)
 *
 * Succès si les deux chaines de caratères actual et expected sont identiques
 */
#define AUM_ASSERT_STRING_EQUAL(expected, actual) \
  aum_assert(!strcmp(expected, actual), __LINE__, __FILE__, "AUM_ASSERT_STRING_EQUAL(" #expected ", "  #actual ") - Expected \"%s\", but was \"%s\"", expected, actual)

/*! \def AUM_ASSERT_STRING_EQUAL(expected, actual, n)
 *
 * Succès si les deux tableaux ont les n premiers caractères identiques
 */
#define AUM_ASSERT_MEMORY_EQUAL(expected, actual, n) \
    aum_assert(memcmp(actual, expected, n) == 0, __LINE__, __FILE__, "AUM_ASSERT_MEMORY_EQUAL(" #expected ", " #actual ") - Expected \"%.*s\", but was \"%.*s\"", n, expected, n, actual)

/*! \def AUM_ASSERT_PTR_NULL(ptr)
 *
 * Succès si le pointeur ptr est NULL
 */
#define AUM_ASSERT_PTR_NULL(ptr) aum_assert(ptr == NULL, __LINE__, __FILE__, "AUM_ASSERT_PTR_NULL(" #ptr ") - Pointer expected to be %p, but was %p", NULL, ptr)

/*! \def AUM_ASSERT_PTR_NOT_NULL(ptr)
 *
 * Succès si le pointeur ptr est non NULL
 */
#define AUM_ASSERT_PTR_NOT_NULL(ptr) aum_assert((ptr) != NULL, __LINE__, __FILE__, "AUM_ASSERT_PTR_NOT_NULL(" #ptr ")")

/*! \def AUM_ASSERT_PTR_EQUAL(expected, actual)
 *
 * Succès si les valeurs des pointeurs expected et actual sont identiques
 */
#define AUM_ASSERT_PTR_EQUAL(expected, actual) aum_assert(expected == actual, __LINE__, __FILE__, "AUM_ASSERT_PTR_EQUAL(" #expected ", " #actual ") - Expected %p, but was %p", expected, actual)

/*! \def AUM_ASSERT_WAS_CALLED(func)
 *
 * Succès si la fonction func a été appelée
 */
#define AUM_ASSERT_WAS_CALLED(func) \
    aum_assert(aum_mock_get_call_count(func) != 0, __LINE__, __FILE__, "AUM_ASSERT_WAS_CALLED(" #func ") - Function %s was never called", func)

/*! \def AUM_ASSERT_CALL_COUNT_EQUAL(func, expected)
 *
 * Succès si la fonction func a été appelée expected fois
 */
#define AUM_ASSERT_CALL_COUNT_EQUAL(func, expected) \
    aum_assert(aum_mock_get_call_count(func) == expected, __LINE__, __FILE__, "AUM_ASSERT_CALL_COUNT_EQUAL(" #func ", " #expected ") - Function %s expected to be called %d time(s), but was called %d time(s)", func, expected, aum_mock_get_call_count(func))

/*! \def AUM_ASSERT_WAS_CALLED_WITH_AT(func, position, expected)
 *
 * Succès si la fonction func a été appelée avec expected comme valeur de
 * l'argument position
 */
#define AUM_ASSERT_WAS_CALLED_WITH_AT(func, position, expected, additional_message...) \
    aum_assert(aum_mock_was_called_with_at(func, position, expected), __LINE__, __FILE__, "AUM_ASSERT_WAS_CALLED_WITH_AT(" #func ", " #position ", " #expected ")" additional_message)

/*! \def AUM_ASSERT_WAS_CALLED_WITH(func, ...)
 *
 * Succès si la fonction func a été appelée avec les paramètres spécifiés
 */
#define AUM_ASSERT_WAS_CALLED_WITH(func, parameters...) \
    aum_assert(aum_mock_was_called_with(func, parameters), __LINE__, __FILE__, "AUM_ASSERT_WAS_CALLED_WITH(" #func ", " #parameters ")")

