#
#  There exist several targets which are by default empty and which can be
#  used for execution of your targets. These targets are usually executed
#  before and after some main targets. They are:
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_PLATFORM_${CONF}       platform name (current configuration)
#     CND_ARTIFACT_DIR_${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_${CONF}   path to package (current configuration)
#
# NOCDDL


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
TP=tp2
BASES_DIR=bases
TRAIN_TEST_DIR=pruebas


# build
build: .build-post

.build-pre:
# Add your pre 'build' code here...

.build-post: .build-impl
# Add your post 'build' code here...


# clean
clean: .clean-post

.clean-pre:
	rm -rf $(BASES_DIR);
	rm -rf $(TRAIN_TEST_DIR);
	rm -f $(TP)
# Add your pre 'clean' code here...

.clean-post: .clean-impl
# Add your post 'clean' code here...


# clobber
clobber: .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post: .clobber-impl
# Add your post 'clobber' code here...


# all
all: .all-post

.all-pre:
# Add your pre 'all' code here...

.all-post: .all-impl
# Add your post 'all' code here...


# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre: build-tests
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...


# help
help: .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post: .help-impl
# Add your post 'help' code here...

tp: all
	cp $(CND_ARTIFACT_PATH_Release) $(TP)

bases:
	$(MKDIR) -p $(BASES_DIR);
	@#rm -f $(BASES_DIR)/basesCaras.csv $(BASES_DIR)/basesCarasRed.csv 
	@#for i in $$(seq 1 10); do for j in $$(seq 1 41); do echo "ImagenesCaras/s$$j/$$i.pgm, id,$$i," >> ; done; done;
	find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $(BASES_DIR)/baseCaras.csv
	find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $(BASES_DIR)/baseCarasRed.csv
	@#find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > bases/baseCaras2.csv
	@#find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, id\2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > bases/baseCarasRed2.csv

folds: sujetos=41
folds: imXsuj=10
folds: base=$(BASES_DIR)/baseCaras.csv
folds: bases
	@$(MKDIR) -p $(TRAIN_TEST_DIR);
	for fold_tam in 1 2 5; do \
		$(MKDIR) -p $(TRAIN_TEST_DIR)/fold_tam_$${fold_tam}; \
		for fold_nro in $$(seq -s' ' 1 $$(( $(imXsuj) / $$fold_tam )) ); do \
			fold_item=$(TRAIN_TEST_DIR)/fold_tam_$${fold_tam}/fold_nro_$${fold_nro}; \
			#echo fold $$fold_item; \
			$(MKDIR) -p $$fold_item; \
			#echo $$fold_tam $$fold_nro; \
			cat $(base) | head -n $$((fold_tam*fold_nro* $(sujetos) )) | tail -n $$((fold_tam*$(sujetos))) > $$fold_item/test.csv; \
			cat $(base) $(base) | tail -n $$(( ($(imXsuj)*2-(fold_tam*fold_nro) )*$(sujetos))) | head -n $$(( ($(imXsuj)-fold_tam) * $(sujetos))) > $$fold_item/train.csv; \
			./$(TP) -m 1 -i $$fold_item/train.csv -q $$fold_item/test.csv -o $$fold_item/classif.csv > $$fold_item/ejecucion.log 2> $$fold_item/error.log; \
		done; \
	done;

# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk
