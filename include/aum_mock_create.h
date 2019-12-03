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
 * \brief Interface pour implémentation des wrappers
 */

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <aum/mock.h>

/******************************************************************************
 * Fonctions publiques                                                        *
 ******************************************************************************/

/*! \brief Enregistrement des arguments et incrément du compteur d'appel 
 *         dans le descripteur de mock associé à la fonction `function_name`
 *
 * \param[in]   function_name,... Nom de la fonction cible, suivi des arguments
 *                                à enregistrer
 */
void *aum_mock_register_call(unsigned long *return_code, const char *function_name, void *real_function, size_t arguments_count, ...);

/*
 * Macros intermédiaires
 */

#define _EXTRACT_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define _COUNT_ARGUMENTS(...) _EXTRACT_N(_0, ## __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define _CONCATENATE(A, B) A ## B

#define _PARAMETER_LIST0() void
#define _PARAMETER_LIST1(__type) __type x1
#define _PARAMETER_LIST2(__type, __types...) __type x2, _PARAMETER_LIST1(__types)
#define _PARAMETER_LIST3(__type, __types...) __type x3, _PARAMETER_LIST2(__types)
#define _PARAMETER_LIST4(__type, __types...) __type x4, _PARAMETER_LIST3(__types)
#define _PARAMETER_LIST5(__type, __types...) __type x5, _PARAMETER_LIST4(__types)
#define _PARAMETER_LIST6(__type, __types...) __type x6, _PARAMETER_LIST5(__types)
#define _PARAMETER_LIST7(__type, __types...) __type x7, _PARAMETER_LIST6(__types)
#define _PARAMETER_LIST8(__type, __types...) __type x8, _PARAMETER_LIST7(__types)
#define _PARAMETER_LIST9(__type, __types...) __type x9, _PARAMETER_LIST8(__types)
#define _PARAMETER_LIST10(__type, __types...) __type x10, _PARAMETER_LIST9(__types)

#define _PARAMETER_LIST(N, __types...) _CONCATENATE(_PARAMETER_LIST, N)(__types)

#define _SIZEOF_LIST0() 
#define _SIZEOF_LIST1(__type) , sizeof(__type), x1
#define _SIZEOF_LIST2(__type, __types...) , sizeof(__type), x2 _SIZEOF_LIST1(__types)
#define _SIZEOF_LIST3(__type, __types...) , sizeof(__type), x3 _SIZEOF_LIST2(__types)
#define _SIZEOF_LIST4(__type, __types...) , sizeof(__type), x4 _SIZEOF_LIST3(__types)
#define _SIZEOF_LIST5(__type, __types...) , sizeof(__type), x5 _SIZEOF_LIST4(__types)
#define _SIZEOF_LIST6(__type, __types...) , sizeof(__type), x6 _SIZEOF_LIST5(__types)
#define _SIZEOF_LIST7(__type, __types...) , sizeof(__type), x7 _SIZEOF_LIST6(__types)
#define _SIZEOF_LIST8(__type, __types...) , sizeof(__type), x8 _SIZEOF_LIST7(__types)
#define _SIZEOF_LIST9(__type, __types...) , sizeof(__type), x9 _SIZEOF_LIST8(__types)
#define _SIZEOF_LIST10(__type, __types...) , sizeof(__type), x10 _SIZEOF_LIST9(__types)

#define _ARGUMENT_LIST0() 
#define _ARGUMENT_LIST1(__type) x1
#define _ARGUMENT_LIST2(__type, __types...) x2, _ARGUMENT_LIST1(__types)
#define _ARGUMENT_LIST3(__type, __types...) x3, _ARGUMENT_LIST2(__types)
#define _ARGUMENT_LIST4(__type, __types...) x4, _ARGUMENT_LIST3(__types)
#define _ARGUMENT_LIST5(__type, __types...) x5, _ARGUMENT_LIST4(__types)
#define _ARGUMENT_LIST6(__type, __types...) x6, _ARGUMENT_LIST5(__types)
#define _ARGUMENT_LIST7(__type, __types...) x7, _ARGUMENT_LIST6(__types)
#define _ARGUMENT_LIST8(__type, __types...) x8, _ARGUMENT_LIST7(__types)
#define _ARGUMENT_LIST9(__type, __types...) x9, _ARGUMENT_LIST8(__types)
#define _ARGUMENT_LIST10(__type, __types...) x10, _ARGUMENT_LIST9(__types)

#define _ARGUMENT_LIST(N, __types...) _CONCATENATE(_ARGUMENT_LIST, N)(__types)

#define _REAL_FUNCTION(__name) __real_ ## __name

/*! \brief Macro helper pour les déclaration nécessaires à un mock */
#define _DECLARE(__ret__, __name, __PARAMETER_LIST)     \
  typedef __ret__ (*__name ## _t) ( __PARAMETER_LIST ); \
  __ret__ _REAL_FUNCTION(__name) ( __PARAMETER_LIST );  \
  __ret__ __wrap_ ## __name ( __PARAMETER_LIST )

#define _WRAPPER_MOCK_REGISTER_CALL(__return_code, __name, N, __types...) \
    aum_mock_register_call(&__return_code, #__name, &_REAL_FUNCTION(__name), N _SIZEOF_LIST ## N(__types) )

/* This instruction is dead code, but it is helpful to signal an error, when a mistake is made in the signature of the mock. */
#define _WRAPPER_CHECK_MOCK_SIGNATURE(__name, __arguments...) return __name( __arguments ); 

#define _WRAPPER_MOCK_CALL(__name, __mock_function, __arguments...) \
    return __mock_function( __arguments );                          \
    _WRAPPER_CHECK_MOCK_SIGNATURE(__name, __arguments)

#define _WRAPPER_BODY(__return_type, __name, N, __types...)                                      \
    unsigned long return_code;                                                                   \
    __name ## _t mock_function = _WRAPPER_MOCK_REGISTER_CALL( return_code, __name, N, __types);  \
    if (mock_function == NULL) {                                                                 \
        return (__return_type) return_code;                                                      \
    }                                                                                            \
    _WRAPPER_MOCK_CALL(__name, mock_function, _ARGUMENT_LIST(N, __types))

#define _CREATE_N(__ret__, __name, N, __types...)          \
  _DECLARE(__ret__, __name, _PARAMETER_LIST(N, __types)) { \
    _WRAPPER_BODY(__ret__, __name, N, __types)             \
  }

/******************************************************************************
 * Macros helper pour la génération semi-automatique des wrappers             *
 ******************************************************************************/

/*! \brief Macro helper création d'un mock de type void (sans arguments). A utiliser si vous compilez sans les extensions GNU. */
#define AUM_MOCK_CREATE_VOID(__ret__, __name) _CREATE_N(__ret__, __name, 0)

/*! \brief Macro helper création d'un mock avec un nombre arbitraire d'arguments */
#define AUM_MOCK_CREATE(__ret__, __name, __types...) _CREATE_N(__ret__, __name, _COUNT_ARGUMENTS(__types), __types)

