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
 * \brief Définition de l'API interne d'abstraction du framework de test externe
 */

#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <aum/test_suite.h>
#include <test_suite_list.h>
#include <file_stream.h>

/*! \brief Initialisation
 *
 * \retval      true  Succès d'initialisation
 * \retval      false     Echec d'initialisation
 */
bool test_framework_initialize(void);

/*! \brief Nettoyage
 */
void test_framework_cleanup(void);

/*! \brief Enregistrement d'une suite de tests
 *
 * \param[in]   suite_name      Nom de la suite
 * \param[in]   tests           Ensemble de tests à enregistrer
 *
 * \retval      true  Succès d'enregistrement de la suite de tests
 * \retval      false     Echec d'enregistrement de la suite de tests
 */
bool test_framework_register_suite(aum_test_suite_t *suite);

/*! \brief Exécution des suites de tests enregistrées
 *
 * \retval      true  L'exécution des suites de tests s'est bien déroulée
 * \retval      false     Erreur pendant l'exécution des suites de tests
 */
bool test_framework_run(int ignored_tests_count);

bool test_framework_print_xml_report(file_stream_t *output, test_suite_list_t *suites) __attribute__ ((warn_unused_result));

bool test_framework_has_failures(void);

bool test_framework_run_single_test(const char *suite_name, const char *test_name);

//FIXME : redéfinir un type pour aum_setup_teardown_t + macro pour déclarer les fonctions
// Cunit has a type for setup/teardown functions, but this type should be encapsulated
// so that it is easier to remove CUnit in the future

void test_framework_vassert(bool expression, unsigned int line_number, const char * file_name, char *error_message_format, va_list additional_messages);
