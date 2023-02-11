.PHONY : buildlib utestlib

LIB_NAME := approximation

UTEST_EXEC := lib_unit_tests.exe

LIB_PATH := ./lib
SRC_PATH := ${LIB_PATH}/src
INC_PATH := ${LIB_PATH}/inc
OUT_PATH := ${LIB_PATH}/out

UTEST_PATH := ${LIB_PATH}/unit_tests

LIBARRAY_FILE := ${LIB_PATH}/lib${LIB_NAME}.so
CC := gcc
CFLAGS := -std=c99 -I$(INC_PATH) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
UTEST_FLAGES := -L${LIB_PATH}
LD_FLAGS := -l${LIB_NAME} `pkg-config --cflags --libs check`

ifeq ($(mode), debug)
    CFLAGS += -g3 -DDEBUG
else
    CFLAGS += -O3
endif

SRCS := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(SRCS:$(SRC_PATH)/%.c=$(OUT_PATH)/%.o)

UTEST_SRCS := $(wildcard $(UTEST_PATH)/*.c)
UTEST_OBJS := $(UTEST_SRCS:$(UTEST_PATH)/%.c=$(OUT_PATH)/%.o)

utestlib: $(LIBARRAY_FILE) $(UTEST_EXEC)

buildlib: $(LIBARRAY_FILE)

$(UTEST_EXEC) : $(UTEST_OBJS)
	@export LD_RUN_PATH=$LD_RUN_PATH:${LIB_PATH}
	@export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}
	@$(CC) $(CFLAGS) $(UTEST_FLAGES) -o $@ $^ $(LD_FLAGS)

$(LIBARRAY_FILE): ${OBJS}
	@export LD_RUN_PATH=${LIB_PATH}
	@export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}
	@$(CC) -shared -fPIC -o $@ $^

${OUT_PATH}/%.o: ${SRC_PATH}/%.c outdir 
	@$(CC) $(CFLAGS) -c $< -o $@ 

outdir:
	@mkdir -p $(OUT_PATH)

$(OUT_PATH)/check_%.o : $(UTEST_PATH)/check_%.c outdir
	@$(CC) $(CFLAGS) -o $@ -c $<

$(INC_PATH)/%.h:

clean:
	@rm -rf ${LIBARRAY_FILE}
	@rm -rf ./app/__pycache__
	@rm -f *.exe
	@rm -rf $(OUT_PATH)

