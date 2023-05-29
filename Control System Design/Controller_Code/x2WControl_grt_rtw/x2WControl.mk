###########################################################################
## Makefile generated for component 'x2WControl'. 
## 
## Makefile     : x2WControl.mk
## Generated on : Mon May 29 16:02:14 2023
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/x2WControl.exe
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# CMD_FILE                Command file

PRODUCT_NAME              = x2WControl
MAKEFILE                  = x2WControl.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2023a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2023a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/sohai/Downloads
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
CMD_FILE                  = x2WControl.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
LIBSSC_SLI_LCC_OBJS       = 
LIBSM_SSCI_LCC_OBJS       = 
LIBSSC_CORE_LCC_OBJS      = 
LIBSSC_ST_LCC_OBJS        = 
LIBMC_LCC_OBJS            = 
LIBSM_LCC_OBJS            = 
LIBPM_MATH_LCC_OBJS       = 
LIBPM_LCC_OBJS            = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   2023a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------
# "Debug" Build Configuration
#--------------------------------

ARFLAGS              = $(ARDEBUG)
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64 \
                       $(CDEBUG)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) \
                       $(LDDEBUG)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE) \
                       $(LDDEBUG)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/x2WControl.exe
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(START_DIR)/x2WControl_grt_rtw -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/extern/physmod/win64/lang/include -I$(MATLAB_ROOT)/extern/physmod/win64/mc/include -I$(MATLAB_ROOT)/extern/physmod/win64/pd/include -I$(MATLAB_ROOT)/extern/physmod/win64/pm/include -I$(MATLAB_ROOT)/extern/physmod/win64/pm_log/include -I$(MATLAB_ROOT)/extern/physmod/win64/pm_math/include -I$(MATLAB_ROOT)/extern/physmod/win64/sm/include -I$(MATLAB_ROOT)/extern/physmod/win64/sm_ssci/include -I$(MATLAB_ROOT)/extern/physmod/win64/ssc_comp/include -I$(MATLAB_ROOT)/extern/physmod/win64/ssc_core/include -I$(MATLAB_ROOT)/extern/physmod/win64/ssc_ds/include -I$(MATLAB_ROOT)/extern/physmod/win64/ssc_sli/include -I$(MATLAB_ROOT)/extern/physmod/win64/ssc_st/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DMAT_FILE=1 -DONESTEPFCN=1 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=1
DEFINES_STANDARD = -DMODEL=x2WControl -DNUMST=2 -DNCSTATES=8 -DHAVESTDIO -DRT -DUSE_RTMODEL

DEFINES = $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_create.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_setParameters.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_asserts.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_deriv.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_checkDynamics.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_compOutputs.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_asm_delegate.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_sim_delegate.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_mode_zero_crossings.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_logging.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_geometries.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_gateway.c $(MATLAB_ROOT)/rtw/c/src/rt_logging.c $(START_DIR)/x2WControl_grt_rtw/rt_backsubrr_dbl.c $(START_DIR)/x2WControl_grt_rtw/rt_forwardsubrr_dbl.c $(START_DIR)/x2WControl_grt_rtw/rt_lu_real.c $(START_DIR)/x2WControl_grt_rtw/rt_matrixlib_dbl.c $(START_DIR)/x2WControl_grt_rtw/rtGetInf.c $(START_DIR)/x2WControl_grt_rtw/rtGetNaN.c $(START_DIR)/x2WControl_grt_rtw/rt_nonfinite.c $(START_DIR)/x2WControl_grt_rtw/x2WControl.c $(START_DIR)/x2WControl_grt_rtw/x2WControl_data.c

MAIN_SRC = $(MATLAB_ROOT)/rtw/c/src/common/rt_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = x2WControl_a151ee3d_1.obj x2WControl_a151ee3d_1_create.obj x2WControl_a151ee3d_1_setParameters.obj x2WControl_a151ee3d_1_asserts.obj x2WControl_a151ee3d_1_deriv.obj x2WControl_a151ee3d_1_checkDynamics.obj x2WControl_a151ee3d_1_compOutputs.obj x2WControl_a151ee3d_1_asm_delegate.obj x2WControl_a151ee3d_1_sim_delegate.obj x2WControl_a151ee3d_1_mode_zero_crossings.obj x2WControl_a151ee3d_1_logging.obj x2WControl_a151ee3d_1_geometries.obj x2WControl_a151ee3d_1_gateway.obj rt_logging.obj rt_backsubrr_dbl.obj rt_forwardsubrr_dbl.obj rt_lu_real.obj rt_matrixlib_dbl.obj rtGetInf.obj rtGetNaN.obj rt_nonfinite.obj x2WControl.obj x2WControl_data.obj

MAIN_OBJ = rt_main.obj

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(MATLAB_ROOT)/extern/physmod/win64/ssc_sli/lib/ssc_sli_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/sm_ssci/lib/sm_ssci_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/ssc_core/lib/ssc_core_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/ssc_st/lib/ssc_st_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/mc/lib/mc_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/sm/lib/sm_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/pm_math/lib/pm_math_lcc.lib $(MATLAB_ROOT)/extern/physmod/win64/pm/lib/pm_lcc.lib

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) @$(CMD_FILE) $(subst /,\,$(LIBS)) $(subst /,\,$(SYSTEM_LIBS)) $(subst /,\,$(TOOLCHAIN_LIBS))
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/mc/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/pm/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/pm_math/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/sm/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/sm_ssci/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/ssc_core/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/ssc_sli/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/extern/physmod/win64/ssc_st/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/x2WControl_grt_rtw/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_create.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_create.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_setParameters.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_setParameters.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_asserts.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_asserts.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_deriv.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_deriv.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_checkDynamics.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_checkDynamics.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_compOutputs.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_compOutputs.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_asm_delegate.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_asm_delegate.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_sim_delegate.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_sim_delegate.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_mode_zero_crossings.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_mode_zero_crossings.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_logging.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_logging.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_geometries.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_geometries.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_a151ee3d_1_gateway.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_a151ee3d_1_gateway.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_logging.obj : $(MATLAB_ROOT)/rtw/c/src/rt_logging.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_backsubrr_dbl.obj : $(START_DIR)/x2WControl_grt_rtw/rt_backsubrr_dbl.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_forwardsubrr_dbl.obj : $(START_DIR)/x2WControl_grt_rtw/rt_forwardsubrr_dbl.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_lu_real.obj : $(START_DIR)/x2WControl_grt_rtw/rt_lu_real.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_matrixlib_dbl.obj : $(START_DIR)/x2WControl_grt_rtw/rt_matrixlib_dbl.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetInf.obj : $(START_DIR)/x2WControl_grt_rtw/rtGetInf.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetNaN.obj : $(START_DIR)/x2WControl_grt_rtw/rtGetNaN.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_nonfinite.obj : $(START_DIR)/x2WControl_grt_rtw/rt_nonfinite.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


x2WControl_data.obj : $(START_DIR)/x2WControl_grt_rtw/x2WControl_data.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_main.obj : $(MATLAB_ROOT)/rtw/c/src/common/rt_main.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


#------------------------
# BUILDABLE LIBRARIES
#------------------------

$(MATLAB_ROOT)/extern/physmod/win64/ssc_sli/lib/ssc_sli_lcc.lib : $(LIBSSC_SLI_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBSSC_SLI_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/sm_ssci/lib/sm_ssci_lcc.lib : $(LIBSM_SSCI_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBSM_SSCI_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/ssc_core/lib/ssc_core_lcc.lib : $(LIBSSC_CORE_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBSSC_CORE_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/ssc_st/lib/ssc_st_lcc.lib : $(LIBSSC_ST_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBSSC_ST_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/mc/lib/mc_lcc.lib : $(LIBMC_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBMC_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/sm/lib/sm_lcc.lib : $(LIBSM_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBSM_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/pm_math/lib/pm_math_lcc.lib : $(LIBPM_MATH_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBPM_MATH_LCC_OBJS)


$(MATLAB_ROOT)/extern/physmod/win64/pm/lib/pm_lcc.lib : $(LIBPM_LCC_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS) /out:$@ $(LIBPM_LCC_OBJS)


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


