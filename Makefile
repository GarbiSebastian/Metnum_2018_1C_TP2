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
TRAIN_TEST_DIR=folds
DIR_RESULTADOS=resultados


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
	@$(MKDIR) -p $(BASES_DIR);
	@#rm -f $(BASES_DIR)/basesCaras.csv $(BASES_DIR)/basesCarasRed.csv
	@#for i in $$(seq 1 10); do for j in $$(seq 1 41); do echo "ImagenesCaras/s$$j/$$i.pgm, id,$$i," >> ; done; done;
	@find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $(BASES_DIR)/baseCaras.csv
	@find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\3 0\2 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > $(BASES_DIR)/baseCarasRed.csv
	@#find ImagenesCaras | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > bases/baseCaras2.csv
	@#find ImagenesCarasRed | grep .pgm | sed -r -e 's#(.*s([0-9]+)/([0-9]+).*)#0\2 0\3 &, \2,#' -e 's/0*([0-9]{2})/\1/g' | sort | sed -r -e 's/.*(Im.*)/\1/' > bases/baseCarasRed2.csv
	@echo $@ finalizado;

folds: bases
	@sujetos=41;\
	imagenes=10;\
	base=$(BASES_DIR)/baseCaras.csv;\
	for k_fold in 2 5 10; do \
		fold_tam=$$((imagenes/k_fold));\
		for iteracion in $$(seq -s' ' 1 $$k_fold); do \
			fold_dir=$(TRAIN_TEST_DIR)/k_fold_$$k_fold/iteracion_$$iteracion;\
			$(MKDIR) -p $$fold_dir;\
			cat $$base | head -n $$((fold_tam*iteracion*sujetos )) | tail -n $$((fold_tam*sujetos)) > $$fold_dir/test.csv; \
			cat $$base $$base | tail -n $$(( (imagenes*2-(fold_tam*iteracion) )*sujetos)) | head -n $$(( (imagenes-fold_tam)*sujetos)) > $$fold_dir/train.csv; \
		done;																																				\
	done;
	@echo $@ finalizado;

knn_folds: folds tp
	@for k in 1 2 3 5 7 11; do \
		for k_fold in 2 5 10; do \
			for iteracion in $$(seq -s' ' 1 $$k_fold); do \
				fold_dir=$(TRAIN_TEST_DIR)/k_fold_$$k_fold/iteracion_$$iteracion;\
				dir=$(DIR_RESULTADOS)/knn/k_$$k/k_fold_$$k_fold/iteracion_$$iteracion;\
				$(MKDIR) -p $$dir;\
				echo $$dir;\
				./$(TP) -m 0 -i $$fold_dir/train.csv -q $$fold_dir/test.csv -o $$dir/clasif.csv -k $$k > $$dir/ejecucion.log 2> $$dir/error.log;\
			done;\
		done;\
	done;
	@echo $@ finalizado;

pca_knn_folds: folds tp
	@for k_fold in 2 5 10; do \
		for iteracion in $$(seq -s' ' 1 $$k_fold); do \
			fold_dir=$(TRAIN_TEST_DIR)/k_fold_$$k_fold/iteracion_$$iteracion;\
			for k in 1 2 3 5 7 11; do \
				for alfa in 1 2 3 5 7 10 20 30 50 70 100 200 300 500 700; do \
					dir=$(DIR_RESULTADOS)/pca_knn/k_$$k/alfa_$$alfa/k_fold_$$k_fold/iteracion_$$iteracion;\
						$(MKDIR) -p $$dir;\
						echo $$dir;\
						./$(TP) -m 1 -i $$fold_dir/train.csv -q $$fold_dir/test.csv -o $$dir/clasif.csv -k $$k -a $$alfa > $$dir/ejecucion.log 2> $$dir/error.log;\
			done;\
		done;\
	done;
	@echo $@ finalizado;

# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk
