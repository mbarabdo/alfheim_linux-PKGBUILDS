#
# Do not edit this file -- it gets generated from Makefile.inc.in.
# Your changes will be lost the next time ./configure is run.
#
OMNETPP_PRODUCT = OMNeT++
OMNETPP_RELEASE = omnetpp-5.2
OMNETPP_VERSION = 5.2
OMNETPP_BUILDID = 170818-f9241c2
OMNETPP_EDITION = Academic Public License -- NOT FOR COMMERCIAL USE

#
# Optional features (set to "yes" to enable the feature)
#
WITH_QTENV ?= yes
WITH_OSG ?= yes
WITH_OSGEARTH ?= yes
WITH_NETBUILDER ?= yes
WITH_PARSIM ?= yes
WITH_SYSTEMC ?= no
WITH_TKENV ?= yes
EMBED_TCL_CODE ?= yes
PREFER_SQLITE_RESULT_FILES ?= no

#
# SHARED_LIBS determines whether omnetpp is built as shared or static libs
# By default we use shared libs
#
SHARED_LIBS ?= yes

#
# Directories
#

# NOTE: it is important to evaluate the current path immediately in this file using :=
OMNETPP_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
OMNETPP_IMAGE_PATH := ./bitmaps:./images:$(OMNETPP_ROOT)/images
OMNETPP_BIN_DIR = $(OMNETPP_ROOT)/bin
OMNETPP_INCL_DIR = $(OMNETPP_ROOT)/include
OMNETPP_LIB_DIR = $(OMNETPP_ROOT)/lib$(OUTPUT_PREFIX)
OMNETPP_OUT_DIR = $(OMNETPP_ROOT)/out$(OUTPUT_PREFIX)
OMNETPP_SRC_DIR = $(OMNETPP_ROOT)/src
OMNETPP_UTILS_DIR = $(OMNETPP_SRC_DIR)/utils
OMNETPP_TKENV_DIR = $(OMNETPP_SRC_DIR)/tkenv
OMNETPP_UI_DIR = $(OMNETPP_ROOT)/ui
OMNETPP_DOC_DIR = $(OMNETPP_ROOT)/doc
OMNETPP_SAMPLES_DIR = $(OMNETPP_ROOT)/samples
OMNETPP_TEST_DIR = $(OMNETPP_ROOT)/test

PLATFORM = linux.x86_64
# platform specific code
ifeq ($(PLATFORM),win32.x86_64)
  OMNETPP_TOOLS_DIR = $(OMNETPP_ROOT)/tools/win64
  OMNETPP_IMAGE_PATH := $(shell cygpath -p -m '$(OMNETPP_IMAGE_PATH)')
else ifeq ($(PLATFORM),macosx)
  OMNETPP_TOOLS_DIR = $(OMNETPP_ROOT)/tools/macosx
else
  # Linux and other platforms do not have a tools directory
endif

#
# Configure MODE specific flags/suffixes
#
ifeq ($(MODE),debug)
  CFLAGS=$(CFLAGS_DEBUG)
  D=_dbg
else
  # by default assume release mode
  MODE=release
  CFLAGS=$(CFLAGS_RELEASE)
  D=
endif

# use statically built omnetpp if we are building the IDE native helper library
ifeq ($(BUILDING_UILIBS),yes)
  SHARED_LIBS=no
  OUTPUT_PREFIX=/ui
endif

#
# Configname determines where (in which subdirectory of out/)
# makemake-generated makefiles create object files and other
# build artifacts.
#
CONFIGNAME ?= $(TOOLCHAIN_NAME)-$(MODE)

#
# Control verbosity. Specifiying V=1 will make the build output verbose. You can use:
# $(Q) to hide commands only in quiet mode
# $(qecho) to print out something only in quite mode
# $(vecho) to print out something only in verbose mode
#
ifeq ($(V),1)
  Q :=
  vecho = @echo
  qecho = @true
else
  Q := @
  vecho = @true
  qecho = @echo
endif

# Recursive wildcard function. Call like: $(call opp_rwildcard, src/, *.c *.h)
opp_rwildcard=$(foreach d,$(wildcard $1*),$(call opp_rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

#
# tools, libraries and compiler flags detected by ./configure
#
PERL = perl
YACC = bison -y
LEX = flex
CC = clang
CXX = clang++
TOOLCHAIN_NAME = clang
DEFINES = -DHAVE_SWAPCONTEXT -DWITH_MPI
CFLAGS_DEBUG = -g -Wall
CFLAGS_RELEASE = -O3 -march=native -mtune=native -DNDEBUG=1
CFLAGS += -MMD -MP -MF $(basename $@).d  -fPIC  -Wno-deprecated-register -Wno-unused-function -fno-stack-protector $(DEFINES)
CXXFLAGS =  -std=c++11
LDFLAG_LIBPATH = -L
LDFLAG_INCLUDE = -Wl,-u,
LDFLAG_LIB = -l
LDFLAG_IMPLIB = -Wl,--out-implib,
LDFLAGS =  -Wl,-rpath,$(OMNETPP_LIB_DIR) -Wl,-rpath,$(OMNETPP_TOOLS_DIR)/lib -Wl,-rpath,.  -Wl,--export-dynamic $(LDFLAG_LIBPATH)$(OMNETPP_LIB_DIR)
WHOLE_ARCHIVE_ON = -Wl,--whole-archive
WHOLE_ARCHIVE_OFF = -Wl,--no-whole-archive
AS_NEEDED_ON = -Wl,--as-needed
AS_NEEDED_OFF = -Wl,--no-as-needed
PIC_FLAGS = -fPIC
MSGC = opp_msgc
SMC = opp_smc
NEDTOOL = nedtool
AS = as
AR = ar cr
ARFLAG_OUT = 
RANLIB = ranlib
SHLIB_LD = clang++ -shared -fPIC
DLLTOOL = dlltool
STRIP = strip
WISH = wish
MAKEDEPEND = opp_makedep -Y --objdirtree
LN = ln -f
MKPATH = mkdir -p
SHLIB_POSTPROCESS = opp_shlib_postprocess
SWIG = swig
QMAKE = /usr/bin/qmake
MOC=/usr/bin/moc
UIC=/usr/bin/uic
RCC=/usr/bin/rcc

HAVE_DLOPEN = 1
SYS_LIBS = -ldl -lstdc++ 
TK_CFLAGS = 
TK_LIBS = -ltk8.6 -ltcl8.6
QT_CFLAGS = -isystem /usr/include/qt -isystem /usr/include/qt/QtCore -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtOpenGL -isystem /usr/include/qt/QtPrintSupport
QT_LIBS = -lQt5Gui -lQt5Core -lQt5Widgets -lQt5PrintSupport -lQt5OpenGL -L/usr/lib -Wl,-rpath=/usr/lib
QTENV_LDFLAGS = -Wl,-rpath-link=/usr/lib
OSG_CFLAGS = 
OSG_LIBS = -losg -losgDB -losgGA -losgViewer -losgUtil -lOpenThreads
OSGEARTH_CFLAGS = 
OSGEARTH_LIBS = -losgEarth -losgEarthUtil
ZLIB_CFLAGS = 
ZLIB_LIBS = -lz
MPI_CFLAGS = -pthread
MPI_LIBS = -pthread -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags -L/usr/lib/openmpi -lmpi_cxx -lmpi
PTHREAD_CFLAGS = 
PTHREAD_LIBS = -lpthread
XMLPARSER = expat
XML_CFLAGS = 
XML_LIBS = -lexpat
DEFINES += -DXMLPARSER=$(XMLPARSER)
AKAROA_CFLAGS = -I/usr/local/akaroa/include
AKAROA_LIBS = -L/usr/local/akaroa/lib -lakaroa -lfl
JNILIBS_IF_POSSIBLE = jnilibs
JAVA_CFLAGS = 
JAVA_LIBS = 

#
# platform specific library and executable prefixes and extensions
#
A_LIB_SUFFIX = .a
SO_LIB_SUFFIX = .so
DLL_LIB_SUFFIX = .dll
JNI_LIB_SUFFIX = $(SO_LIB_SUFFIX)
EXE_SUFFIX = 
LIB_PREFIX = lib
SHARED_LIB_SUFFIX = $(SO_LIB_SUFFIX)

#
# omnetpp and system libraries linked with the simulations
#
TKENV_LIBS = $(LDFLAG_INCLUDE)_tkenv_lib $(AS_NEEDED_OFF) -lopptkenv$D -loppenvir$D -lopplayout$D
QTENV_LIBS = $(LDFLAG_INCLUDE)_qtenv_lib $(AS_NEEDED_OFF) $(QTENV_LDFLAGS) -loppqtenv$D -loppenvir$D -lopplayout$D
CMDENV_LIBS = $(LDFLAG_INCLUDE)_cmdenv_lib $(AS_NEEDED_OFF) -loppcmdenv$D -loppenvir$D
ALL_ENV_LIBS = $(CMDENV_LIBS)
KERNEL_LIBS = -loppsim$D
OPPMAIN_LIB = $(LDFLAG_LIB)oppmain$D

#
# flags and libraries required for Qtenv
#
ifeq ($(WITH_QTENV),yes)
  DEFINES += -DPREFER_QTENV -DWITH_QTENV
  # libraries required for static linking
  ifneq ($(SHARED_LIBS),yes)
    QTENV_LIBS += $(QT_LIBS)
    ifeq ($(WITH_OSG),yes)
      QTENV_LIBS += $(OSG_LIBS)
      KERNEL_LIBS += -losg -lOpenThreads
    endif
    ifeq ($(WITH_OSGEARTH),yes)
      QTENV_LIBS += $(OSGEARTH_LIBS)
      KERNEL_LIBS += -losgEarth
    endif
    ifeq ($(PLATFORM),macosx)
      QTENV_LIBS += -framework Carbon
    endif
  endif
  ALL_ENV_LIBS += $(QTENV_LIBS)
endif

#
# flags and libraries required for Ttenv
#
ifeq ($(WITH_TKENV),yes)
  DEFINES += -DWITH_TKENV
  # libraries required for static linking
  ifneq ($(SHARED_LIBS),yes)
    TKENV_LIBS += $(TK_LIBS) $(ZLIB_LIBS)
    ifeq ($(PLATFORM),macosx)
      TKENV_LIBS += -framework Carbon
    endif
  endif
  ALL_ENV_LIBS += $(TKENV_LIBS)
endif

#
# Other defines
#
ifeq ($(WITH_PARSIM),yes)
  DEFINES += -DWITH_PARSIM
  # extra libs needed during static building
  ifneq ($(SHARED_LIBS),yes)
    KERNEL_LIBS += $(MPI_LIBS)
  endif
endif

ifeq ($(WITH_NETBUILDER),yes)
  DEFINES += -DWITH_NETBUILDER
endif

# note: defines for OSG and osgEarth must be available even if WITH_QTENV=no
ifeq ($(WITH_OSG),yes)
  DEFINES += -DWITH_OSG
endif

ifeq ($(WITH_OSGEARTH),yes)
  DEFINES += -DWITH_OSGEARTH
endif


#
# toolchain specific flags and options
#
ifeq ($(TOOLCHAIN_NAME),clangc2)
  # this macro can be used to pass EXPORT macros to the compiler if omnet is built as shared library
  ifeq ($(SHARED_LIBS),yes)
    IMPORT_DEFINES = -DOMNETPPLIBS_IMPORT
    EXPORT_DEFINES = $(EXPORT_MACRO)
  endif
endif

#
# handle differences between shared and static lib builds
#
ifeq ($(SHARED_LIBS),yes)
  LIB_SUFFIX =  $(SHARED_LIB_SUFFIX)
else
  LIB_SUFFIX = $(A_LIB_SUFFIX)
  # extra libraries needed when statically linking (because of indirect dependencies)
  KERNEL_LIBS += -loppnedxml$D -loppcommon$D $(XML_LIBS)
endif
