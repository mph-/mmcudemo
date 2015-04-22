# Note, the default board can be specified on the fly using an
# environment variable.  For example:
# BOARD=sam4sbasic1 make

RUN_MODE = ROM

OPT = -Os

MMCULIB_DIR = ../../mmculib

ifndef BOARD
BOARD = sam4sbasic2
endif

include ../../boards/$(BOARD)/board.mk
include $(MMCULIB_DIR)/mmculib.mk


