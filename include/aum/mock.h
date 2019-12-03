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
 * \brief Interface sur les mocks pour utilisation dans les tests
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//FIXME : DELETE ONCE aum_parameter_t has been moved from asserts.h
#include <aum/asserts.h>

/******************************************************************************
 * Types & Structures                                                         *
 ******************************************************************************/
/*! \brief Type utilisé pour le stockage des arguments
 *
 * FIXME : WARN on 32 bits no 64 bits types !!!
 */
typedef unsigned long mock_argument_t;

/*! \brief Descripteur de mock */
typedef struct mock_s mock_t;

/******************************************************************************
 * Fonctions publiques de l'interface                                         *
 * Ces fonctions sont destinées à être utilisées dans les tests               *
 ******************************************************************************/

/*! \brief Configure un mock pour exécuter une fonction
 *
 * \param[in]   function_name   Nom de la fonction mockée
 * \param[in]   function_ptr    Fonction à exécuter lors d'un appel à function_name
 */
void            aum_mock_will_execute(const char *function_name, void *function_ptr);

/*! \brief Configure un mock pour retourner une valeur précise
 *
 * \param[in]   function_name   Nom de la fonction mockée
 * \param[in]   return_value    Valeur à retourner lors d'un appel à function_name
 */
void            aum_mock_will_return(const char    *function_name,
                                     unsigned long  return_value);

/*! \brief Configure un mock pour retourner une valeur précise à un appel précis.
 *         Une seule valeur peut être configurée à la fois et cette fonction ne 
 *         peut pas être utilisée en combinaison avec aum_mock_will_return.
 *
 * \param[in]   function_name   Nom de la fonction mockée
 * \param[in]   return_value    Valeur à retourner lors d'un appel à function_name
 * \param[in]   call_number     Identifie l'appel pour lequel forcer le retour
 */
void            aum_mock_will_return_at(const char    *function_name,
                                        unsigned long  return_value,
                                        size_t         call_number);

/*! \brief Réinitialisation de l'ensemble des mocks */
void            aum_mock_reset(void);

/*! \brief Récupération du compteur d'appel à une fonction mockée
 *
 * \param[in]   function_name   Nom de la fonction mockée
 *
 * \return      Nombre d'appels effectués à function_name
 */
size_t          aum_mock_get_call_count(const char *function_name);

/*! \brief Récupération d'un argument passé à une fonction mockée au dernier appel
 *         Attention, le si la fonction mockée n'a jamais été appelée.
 *
 * \param[in]   function_name   Nom de la fonction mockée
 * \param[in]   position        Position de l'argument à récupérer
 *
 * \return      Valeur brute de l'argument
 */
mock_argument_t aum_mock_get_parameter_at(const char *function_name, int position);

/*! \brief FIXME
 *
 * \param[in]   function_name           FIXME
 * \param[in]   position                FIXME
 * \param[in]   param                   FIXME
 *
 * \retval      FIXME
 * \retval      FIXME
 */
bool		aum_mock_was_called_with_at(const char      *function_name,
					    int              position,
					    aum_parameter_t *param);

/*! \brief FIXME
 *
 * \param[in]   function_name,...       FIXME
 *
 * \retval      FIXME
 * \retval      FIXME
 */
bool            aum_mock_was_called_with(const char *function_name, ...);


//FIXME besoin réel ou non ? --> pas mal, par macro
/* void aum_mock_call_real(const char *function, ...); */
