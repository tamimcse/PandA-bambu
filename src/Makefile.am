METASOURCES = AUTO
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(all_includes) -I$(BOOST_DIR) -I$(ABSEIL_DIR)
AM_LDFLAGS += $(BOOST_LDFLAGS)

# main list of binary produced
bin_PROGRAMS =
noinst_LTLIBRARIES =

noinst_HEADERS = Parameter.hpp constant_strings.hpp

Parameter.cpp : branch_name.hpp revision_hash.hpp

if INSIDE_GIT
branch_name.hpp : $(GIT_WORKTREE_PATH)/HEAD $(GIT_WORKTREE_PATH)/index
	@echo "\"`git --git-dir $(GIT_WORKTREE_PATH) rev-parse --abbrev-ref HEAD`\"" >$@

revision_hash.hpp : $(GIT_WORKTREE_PATH)/HEAD $(GIT_WORKTREE_PATH)/index
	@echo "\"`git --git-dir $(GIT_WORKTREE_PATH) rev-parse HEAD`\"" > $@

else

branch_name.hpp :
	echo "" > $@

revision_hash.hpp :
	cat $(top_srcdir)/dist_revision_hash > $@

endif

SUBDIRS = 
DIST_SUBDIRS =
EXTRA_DIST =
PRJ_DOC = src.doc

include $(top_srcdir)/src/constants/constants.am

if BUILD_LIB_ALGORITHMS
include $(top_srcdir)/src/algorithms/algorithms.am
endif

if BUILD_LIB_BDD
  SUBDIRS += bdd
  DIST_SUBDIRS += bdd
endif

if BUILD_LIB_BEHAVIOR
include $(top_srcdir)/src/behavior/behavior.am
endif

if BUILD_LIB_CIRCUIT
include $(top_srcdir)/src/circuit/circuit.am
endif

if BUILD_LIB_DESIGN_ANALYSIS
  SUBDIRS += design_analysis
  DIST_SUBDIRS += design_analysis
endif

if BUILD_LIB_DESIGN_FLOWS
include $(top_srcdir)/src/design_flows/design_flows.am
endif

if BUILD_LIB_FRONTEND_ANALYSIS
include $(top_srcdir)/src/frontend_analysis/frontend_analysis.am
endif

if BUILD_LIB_GRAPH
include $(top_srcdir)/src/graph/graph.am
  AM_CPPFLAGS += -I$(top_srcdir)/src/graph
endif

if BUILD_LIB_HLS
  SUBDIRS += HLS
  DIST_SUBDIRS += HLS
endif

if BUILD_LIB_INTERMEDIATE_REPRESENTATIONS
include $(top_srcdir)/src/intermediate_representations/intermediate_representations.am
endif

if BUILD_LIB_FROM_IPXACT
  SUBDIRS += ip_xact
  DIST_SUBDIRS += ip_xact
endif

if BUILD_LIB_ILP
include $(top_srcdir)/src/ilp/ilp.am
endif

if BUILD_LIB_LOGIC_SYNTHESIS
  SUBDIRS += logic_synthesis
  DIST_SUBDIRS += logic_synthesis
endif

if BUILD_LIB_ARCH
  SUBDIRS += machine
  DIST_SUBDIRS += machine
endif

if BUILD_LIB_PARSER
  SUBDIRS += parser
  DIST_SUBDIRS += parser
if BUILD_LIB_FROM_C
  AM_CPPFLAGS += \
     -I$(top_srcdir)/src/parser/treegcc
endif
endif

if BUILD_LIB_POLIXML
include $(top_srcdir)/src/polixml/polixml.am
AM_CPPFLAGS += -I$(top_srcdir)/src/polixml \
                 -I$(top_srcdir)/src/parser/polixml
endif

if BUILD_LIB_PRAGMA
include $(top_srcdir)/src/pragma/pragma.am
endif

if BUILD_LIB_TREE
include $(top_srcdir)/src/tree/tree.am
endif

if BUILD_LIB_WRAPPER
include $(top_srcdir)/src/wrapper/wrapper.am
endif

if BUILD_LIB_2LEV
  SUBDIRS += logic_synthesis
  DIST_SUBDIRS += logic_synthesis
endif

if BUILD_LIB_RTL
  SUBDIRS += rtl
  DIST_SUBDIRS += rtl
endif

if BUILD_LIB_TECHNOLOGY
include $(top_srcdir)/src/technology/technology.am
endif

if BUILD_LIB_UTILITY
include $(top_srcdir)/src/utility/utility.am
AM_CPPFLAGS += -I$(top_srcdir)/src/utility
endif

#################################### Spider ####################################
if BUILD_SPIDER
include $(top_srcdir)/src/spider.am
endif

############################### tree-panda-gcc #################################
if BUILD_TREE_PANDA_GCC
include $(top_srcdir)/src/tree-panda-gcc.am
endif

########################### EUCALYPTUS SECTION ###########################
if BUILD_EUCALYPTUS
include $(top_srcdir)/src/eucalyptus.am
endif

########################### BAMBU SECTION ###########################
if BUILD_BAMBU
include $(top_srcdir)/src/bambu.am
endif

########################### DOC SECTION ###########################	
DOX_TAGFILES = src/tree src/graph src/behavior src/technology src/utility src/parser src/edif src/algorithms src/circuit src/ilp src/regularity src/backend src/design_flows/backend/ToHDL src/codesign src/HLS src/HLS/module_allocation src/HLS/binding src/HLS/controller src/HLS/datapath src/HLS/estimation src/HLS/hls_flow src/HLS/target src/HLS/scheduling

EXTRA_DIST += $(PRJ_DOC)

#do not touch the following line

