# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
CC := gcc

TARGET := all

DEBUG := 1
OPT := -O1
BUILD_DIR := build


# ------------------------------------------------------------------- #
CORE_DIR_REL := ./Core
CORE_DIR := $(abspath $(CORE_DIR_REL))

LIB_DIR_REL := ./lib
LIB_DIR := $(abspath $(LIB_DIR_REL))


# ------------------------------------------------------------------- #
INCLUDE_DIRS += -I${CORE_DIR}/Inc
INCLUDE_DIRS += -I${LIB_DIR}

SOURCE_FILES := $(wildcard ${CORE_DIR}/Src/*.c)
SOURCE_FILES += $(wildcard ${LIB_DIR}/*.c)

ifeq ($(DEBUG), 1)
	C_DEFS += -DDEBUG
	CFLAGS += -g -gdwarf-2
endif

C_DEFS += -D_REENTRANT

CFLAGS += ${OPT} $(C_DEFS) -Wall


# ------------------------------------------------------------------- #
LIBS = -lpthread

LDFLAGS := -ggdb3 -O0 -pthread

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)


# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
${TARGET} : $(BUILD_DIR)/$(TARGET)

${BUILD_DIR}/%.o : %.c
	-mkdir -p $(@D)
	$(CC) ${INCLUDE_DIRS} $(CFLAGS) -c $< -o $@

-include ${DEP_FILE}

${BUILD_DIR}/${TARGET} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ $(INCLUDE_DIRS) $(CFLAGS) ${LDFLAGS} -o $@ $(LIBS)


# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
# ------------------------------------------------------------------- #
clean:
	-rm -rf $(BUILD_DIR)

