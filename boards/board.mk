RUN_MODE = ROM

OPT = -Os

MMCULIB_DIR = ../../mmculib

ifndef BOARD
BOARD = sam4sbasic
endif

include ../../boards/$(BOARD)/board.mk
include $(MMCULIB_DIR)/mmculib.mk


