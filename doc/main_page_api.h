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
 * \file main_page.h
 * \brief Page principale de la documentation API
 *
 * \mainpage AUM : All Ur Mocks are belong to us
 *
 * \section aum_intro Introduction
 *
 * Le paquet AUM fournit une bibliothèque implémentant un framework de tests unitaires en C avec une
 * fonctionnalité de mock.
 *
 * \section aum_tuto Tutoriel
 *
 * \subsection pkg_config Quelques mots sur pkg-config
 * 
 * L'installation dépose un fichier \c aum.pc dans le répertoire \c /usr/local/lib/pkgconfig/. 
 * Ainsi, il devrait être possible de récupérer les drapeaux nécéssaires à la compilation et à l'édition de liens à l'aide de pkg-config :\code{.sh}
$ AUM_CFLAGS=$(pkg-config --cflags aum)
$ echo ${AUM_CFLAGS}
-I/usr/local/include
$ AUM_LDFLAGS=$(pkg-config --libs aum)
$ echo ${AUM_LDFLAGS}
-L/usr/local/lib -laum -lcunit
\endcode
 *
 * \subsection aum_tuto_first Premier test
 *
 * Voici le code source d'une première suite de test :
 * \code{.c}
#include <aum.h>

AUM_TEST(AUM_FAIL__should_fail)
{
  AUM_FAIL("Voluntary test failure\n");
}

AUM_TEST_SUITE(simple_suite, &AUM_FAIL__should_fail);

int main(int argc, char **args) {
    aum_runner_t *runner = aum_runner_create();
    if (runner == NULL) {
        return AUM_ERROR;
    }
    aum_runner_register_suite(runner, &simple_suite);

    aum_runner_result_t result = aum_runner_execute_tests(runner);
    aum_runner_destroy(runner);
    return result;
}
\endcode
 *
 * Pour compiler, linker et exécuter le test :
 *\code{.sh}
$ gcc -c test.c -o test.o ${AUM_CFLAGS}
$ gcc test.o -o test.out ${AUM_LDFLAGS}
$ ./test.out
\endcode
 *
 * L'assertion utilisée ici est \c AUM_FAIL. La liste de toutes les assertions fournies par aum peut être trouvée dans le header aum/asserts.h.
 *
 * \subsection aum_tuto_xunit Une sortie utilisable par Jenkins
 * 
 * L'intégration continue permet d'être prévenu au plus tôt de l'introduction d'une régression dans le code. 
 * Avec Jenkins, il est possible de contrôler le statut d'un job en fonction des résultats de tests unitaires 
 * et d'afficher leur courbe d'évolution au cours des constructions. 
 * Pour cela il suffit de fournir à Jenkins un rapport de test au format xunit.
 *
 * Aum peut générer le rapport de tests dans ce format. Il suffit d'appeler la fonction \c aum_runner_print_xml_report avec le chemin du fichier rapport en argument. Dans l'exemple précédent, la fonction \c main, devient ainsi :\code{.c}
int main(int argc, char **args) {
    aum_runner_t *runner = aum_runner_create();
    if (runner == NULL) {
        return AUM_ERROR;
    }
    aum_runner_register_suite(runner, &simple_suite);

    aum_runner_result_t result = aum_runner_execute_tests(runner);
    aum_runner_print_xml_report(runner, "./aum_test_results.xml");
    aum_runner_destroy(runner);
    return result;
}
\endcode
 *
 * Maintenant, l'exécution du test crée un fichier \c aum_test_results.xml compatible au format junit.
 *
 * \subsection aum_tuto_mock Un premier mock
 *
 * Voici le code d'une suite de test utilisant un mock :
 * \code{.c}
#include <aum.h>
#include <aum_mock_create.h>
#include <stdlib.h>

AUM_MOCK_CREATE(void *, malloc, size_t);

AUM_TEST(aum_mock_will_return__should_set_return_code)
{
  aum_mock_will_return("malloc", 0);

  char *result = malloc(10 * sizeof(char));
  AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
}

AUM_TEST_SUITE(suite_with_mock, &aum_mock_will_return__should_set_return_code);

int main(int argc, char **args) {
    aum_runner_t *runner = aum_runner_create();
    if (runner == NULL) {
        return AUM_ERROR;
    }
    aum_runner_register_suite(runner, &suite_with_mock);

    aum_runner_result_t result = aum_runner_execute_tests(runner);
    aum_runner_destroy(runner);
    return result;
}
\endcode
 *
 * Cette fois-ci, pour compiler, linker et exécuter ce test, il faut faire :
 *\code{.sh}
$ gcc -c test_with_mock.c -o test_with_mock.o ${AUM_CFLAGS}
$ gcc test_with_mock.o -o test_with_mock.out ${AUM_LDFLAGS} -Wl,-wrap,malloc
$ ./test_with_mock.out
\endcode
 *
 * Lors de la phase de link, l'option <code>-Wl,-wrap,malloc</code> est nécessaire. 
 * Avec cette option, l'éditeur de lien transfert tous les appels à \c malloc à la fonction \c __wrap_malloc. 
 * C'est la base technique permettant à Aum d'intercepter et redéfinir le comportement des fonctions mockées.
 *
 * Il y a deux étapes dans ce test :
 * \li la déclaration du mock pour \c malloc,
 * \li l'exploitation des mocks.
 *
 * La déclaration du mock se fait par l'usage de la macro :
 * \code{.c}
AUM_MOCK_CREATE(void *, malloc, size_t);
\endcode
 * Cette macro attend le type de retour, le nom de la fonction, et le type de chaque paramètre.
 *
 * Enfin, l'exploitation des mocks se fait dans chaque tests. Il y a deux grands usages :
 * \li définir le comportement du mock lors de l'exécution du test,
 * \li vérifier la façon dont le mock a été appelé durant le test.
 *
 * Dans l'exemple, la fonction \c malloc est configurée pour retourner 0 à chaque appel :
 * \code{.c}
  aum_mock_will_return("malloc", 0);
\endcode
 * A la fin du test, il est vérifié que \c malloc a été appelé avec la valeur \c 10 :
 * \code{.c}
  AUM_ASSERT_WAS_CALLED_WITH("malloc", AUM_PARAMETER_RAW(10));
\endcode
 * 
 * Les fonctions permettant de déclarer les mocks sont dans le header aum_mock_create.h. 
 * La liste des fonctions permettant de définir le comportement des mocks est dans aum/mock.h.
 * Enfin la liste des assertions sur les mocks est dans le header aum/asserts.h.
 *
 * \subsection aum_tuto_organisation Organiser ses suites de tests
 * 
 * Pour des ensembles de tests plus riches, il est conseillé de structurer ses tests en utilisant les types de fichiers suivants :
 * \li collection de mocks,
 * \li suite de tests,
 * \li l'exécuteur des suites de tests.
 *
 * Un fichier de type "collection de mocks" contient la définition des mocks (à l'aide des macros \c AUM_MOCK_CREATE). 
 * Ce type de fichier est écrit une seule fois et peut être réutilisé à chaque fois qu'on a besoin de mocker une des fonctions fournies par la collection.
 *
 * Un fichier de type "suite de tests" contient un ensemble de tests (définis à l'aide de la macro \c AUM_TEST). 
 * Il exporte une fonction (définie par la macro \c AUM_TEST_SUITE) qui permet de tous les enregistrer.
 *
 * Le fichier d'exécution des suites de tests contient la fonction \c main qui effectue les tâches suivantes :
 * \li l'initialisation de \c AUM par l'appel à \c aum_runner_create,
 * \li l'enregistrement des suites de tests,
 * \li l'exécution des tests par l'appel à \c aum_runner_execute_tests,
 * \li éventuellement la sortie des résultats des tests au formal xunit \c aum_runner_print_xml_report.
 *
 * \subsection aum_limitations Limites connues
 *
 * Elles découlent des limites inhérentes à l'usage de l'option \c -wrap du linker permettant de dérouter les appels aux fonctions vers le mock:
 * \li le linker ne détourne pas les appels qui sont effectués au sein de la même unité de compilation. Ainsi, il n'est pas possible de mocker les appels à une fonction qui sont effectués depuis le même module.
 * \li il est conseillé de compiler les tests unitaires sans optimisation (option -O0). En effet, certaines optimisation suppriment les appels inutiles ou remplacent une fonction par une autre. Par exemple, un appel à \c malloc immédiatement suivi de \c free peut être éliminé par le compilateur. De la même manière, un appel à \c malloc suivi d'un \c memset à 0 peut être transformé en un appel à \c calloc. 
 * \li AUM ne gère pas les fonctions variadiques. Ainsi les fonctions de type \c printf avec un nombre arbitraire d'arguments ne peuvent pas être mockées. Pour chaque fonction variadique, il est conseillé d'avoir une version, dont le nom démarre par \c v, et qui accepte une \c va_list en dernier argument à la place d'un nombre arbitraire d'argument. Cette fonction réalise le coeur de l'opération, la fonction variadique se contentant de transformer ses arguments en \c va_list. On pourra mocker cette fonction. Pour plus de détails, voir : http://c-faq.com/varargs/handoff.html. 
 * \li il faut être vigilant lors de la déclaration de mocks à l'aide de la macro \c AUM_MOCK_CREATE. En effet, le nombre et le type d'arguments déclarés pour le mock doit correspondre à la signature de la vrai fonction. Normalement la macro \c AUM_MOCK_CREATE est écrite de telle manière à ce que ce type d'erreur soit signalé par le compilateur.
 *
 */
