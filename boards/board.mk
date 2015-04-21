RUN_MODE = ROM

OPT = -Os

MMCULIB_DIR = ../../mmculib

BOARD = sam4sbasic

include ../../boards/$(BOARD)/board.mk
include $(MMCULIB_DIR)/mmculib.mk


