#    AUM: Airbus Unit tests with Mocks for C. AUM is a unit testing framework for C that allows the easy definition and request of mocks.
#    Copyright (C) 2019  Airbus Defence and Space
#
#    You should have received a copy of the AUTHORS.md file which lists all contributors.
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


ifndef NAME
  $(error "Variable NAME should be defined")
endif

ifndef VERSION
  $(error "Variable VERSION should be defined")
endif

ifndef PKG_DEPENDS_LIBRARY_PATH
  $(error "Variable PKG_DEPENDS_LIBRARY_PATH should be defined")
endif

ifndef RESULTS_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

ifndef RESULTS_REPORT_DIR
  $(error "Variable RESULTS_DIR should be defined")
endif

TESTC_DIR=./tests/component
TESTC_SRC_DIR=$(TESTC_DIR)/src
TESTC_INCLUDE_DIR=$(TESTC_SRC_DIR)/include
TESTC_DATA_DIR=$(TESTC_DIR)/data

OUTPUT_TESTC_DIR=$(RESULTS_DIR)/testc
OUTPUT_TESTC_OBJ_DIR=$(OUTPUT_TESTC_DIR)/obj
OUTPUT_TESTC_BIN_DIR=$(OUTPUT_TESTC_DIR)/bin
OUTPUT_TESTC_BINARY_NAME=testc
OUTPUT_TESTC_BINARY=$(OUTPUT_TESTC_BIN_DIR)/$(OUTPUT_TESTC_BINARY_NAME)
OUTPUT_TESTC_RESULT_DIR=$(OUTPUT_TESTC_DIR)/result

TESTC_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(RESULTS_BIN_DIR):$(CONFIG_LIBDIR):$(PKG_DEPENDS_LIBRARY_PATH)

OUTPUT_TESTC_RESULT_FILE=$(OUTPUT_TESTC_RESULT_DIR)/testc_output.txt
RESULTS_TESTC_REPORT=$(OUTPUT_TESTC_RESULT_DIR)/testc_report.xml
OUTPUT_TESTC_REFERENCE_RESULT_FILE=$(OUTPUT_TESTC_RESULT_DIR)/reference_testc_output.tpl
OUTPUT_TESTC_REFERENCE_REPORT=$(TESTC_DATA_DIR)/reference_testc_report.xml

################################################################################
# Sources & compilation objects                                                #
################################################################################

TESTC_SRC=$(wildcard $(TESTC_SRC_DIR)/*.c)
TESTC_OBJ=$(patsubst $(TESTC_SRC_DIR)/%.c,$(OUTPUT_TESTC_OBJ_DIR)/%.o,$(TESTC_SRC))

################################################################################
# Build rules                                                                  #
################################################################################

TESTC_DEPENDS_CFLAGS = $(shell $(PKGCONFIG) --cflags $(TESTC_DEPENDS) 2> /dev/null)
TESTC_DEPENDS_LDFLAGS = $(shell $(PKGCONFIG) --libs $(TESTC_DEPENDS) 2> /dev/null)
TESTC_CFLAGS += $(CFLAGS)
TESTC_CFLAGS += -I$(TESTC_INCLUDE_DIR)
TESTC_LDFLAGS += $(LDFLAGS)
TESTC_LDFLAGS += $(TESTC_DEPENDS_LDFLAGS)
TESTC_LDFLAGS += -L$(RESULTS_BIN_DIR) -l$(NAME)

$(OUTPUT_TESTC_BINARY): $(RESULTS_BINARY) $(TESTC_OBJ) | $(OUTPUT_TESTC_BIN_DIR)
	@ echo "LD	$@"
	$(V) $(LD) $(TESTC_OBJ) $(TESTC_LDFLAGS) -o $@

$(OUTPUT_TESTC_OBJ_DIR)/%.o: $(TESTC_SRC_DIR)/%.c | $(OUTPUT_TESTC_OBJ_DIR)
	@ echo "CC	$<"
	$(V) $(CC) $(TESTC_CFLAGS) -c $< -o $@

$(OUTPUT_TESTC_OBJ_DIR) $(OUTPUT_TESTC_BIN_DIR):
	@ $(MKDIR) $@

################################################################################
# Execution rules                                                              #
################################################################################

TEST_CASES = tests/cases
RESULT_TEST_CASES_DIR = $(RESULTS_DIR)/cases

# TODO component tests are specific and a different animal for every project
runtestc: $(OUTPUT_TESTC_BINARY) | $(OUTPUT_TESTC_RESULT_DIR)
	$(V) LD_LIBRARY_PATH=$(TESTC_LIBRARY_PATH) $(OUTPUT_TESTC_BINARY) > $(OUTPUT_TESTC_RESULT_FILE)
	$(V) sed s/{VERSION}/$(VERSION)/ $(TESTC_DATA_DIR)/reference_testc_output.tpl > $(OUTPUT_TESTC_REFERENCE_RESULT_FILE)
	$(V) LD_LIBRARY_PATH=$(TESTC_LIBRARY_PATH) $(OUTPUT_TESTC_BINARY) -o $(RESULTS_TESTC_REPORT)
	$(V) diff $(OUTPUT_TESTC_REFERENCE_RESULT_FILE) $(OUTPUT_TESTC_RESULT_FILE)
	$(V) diff $(OUTPUT_TESTC_REFERENCE_REPORT) $(RESULTS_TESTC_REPORT)
	$(CC) $(CFLAGS) -c $(TEST_CASES)/test_suite_unused_test.c && exit 1 || echo 'OK'
	$(MKDIR) $(RESULT_TEST_CASES_DIR)
	$(CC) $(TESTC_CFLAGS) -fprofile-arcs -c $(TEST_CASES)/test_suite_aum_should_not_generate_leaks_with_option_fprofile-arcs.c -o $(RESULT_TEST_CASES_DIR)/test_suite_aum_should_not_generate_leaks_with_option_fprofile-arcs.o
	$(LD) $(RESULT_TEST_CASES_DIR)/test_suite_aum_should_not_generate_leaks_with_option_fprofile-arcs.o -Wl,-wrap,fwrite -L$(RESULTS_BIN_DIR) -l$(NAME) -lgcov -coverage -o $(RESULT_TEST_CASES_DIR)/test_suite_aum_should_not_generate_leaks_with_option_fprofile-arcs
# TODO add this test
	LD_LIBRARY_PATH=./results/src/bin valgrind --error-exitcode=1 $(RESULT_TEST_CASES_DIR)/test_suite_aum_should_not_generate_leaks_with_option_fprofile-arcs
	$(CC) $(CFLAGS) -c $(TEST_CASES)/test_suite_invalid_mock_signature.c && exit 1 || echo 'OK'
	$(CC) $(CFLAGS) -c $(TEST_CASES)/test_suite_aum_mock_create_with_many_parameters.c -o $(RESULT_TEST_CASES_DIR)/test_suite_aum_mock_create_with_many_parameters.o
	$(LD) $(RESULT_TEST_CASES_DIR)/test_suite_aum_mock_create_with_many_parameters.o -Wl,-wrap,function_with_many_parameters -L$(RESULTS_BIN_DIR) -l$(NAME) -o $(RESULT_TEST_CASES_DIR)/test_suite_aum_mock_create_with_many_parameters

$(OUTPUT_TESTC_RESULT_DIR):
	@ $(MKDIR) $@

VALGRIND_TESTC_LOG_PATH=$(RESULTS_REPORT_DIR)/$(OUTPUT_TESTC_BINARY_NAME)-valgrind.log
VALGRIND_TESTC_REPORT_PATH=$(RESULTS_REPORT_DIR)/$(OUTPUT_TESTC_BINARY_NAME)-valgrind.xml
VALGRIND_TESTC_OPTIONS=--log-file=$(VALGRIND_TESTC_LOG_PATH) --xml-file=$(VALGRIND_TESTC_REPORT_PATH)
FDLEAK_TESTC_REPORT_PATH=$(RESULTS_REPORT_DIR)/valgrind-testc-fdleak.xml

# TODO clean this up by having a script to wrap call to valgrind...
valgrindc: $(OUTPUT_TESTC_BINARY) $(RESULTS_REPORT_DIR)
	$(V) LD_LIBRARY_PATH=$(TESTC_LIBRARY_PATH) $(VALGRIND) $(VALGRIND_TESTC_OPTIONS) $(OUTPUT_TESTC_BINARY) -o $(RESULTS_TESTC_REPORT)
	$(V) $(CLEAN_VALGRIND_REPORT) $(VALGRIND_TESTC_REPORT_PATH)
	$(V) $(GENERATE_FDLEAK_REPORT) $(VALGRIND_TESTC_LOG_PATH) $(VALGRIND_TESTC_REPORT_PATH) $(FDLEAK_TESTC_REPORT_PATH)

.PHONY: runtestc valgrindc

help::
	$(info runtestc       Runs component tests)
	$(info valgrindc      Runs component tests with Valgrind - Valgrind report: '$(VALGRIND_TESTC_REPORT_PATH)')

help_variables::
	$(info TESTC_LDFLAGS     Linker flags for component tests compilation)

