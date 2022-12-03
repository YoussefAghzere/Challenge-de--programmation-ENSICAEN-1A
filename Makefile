
PILOT_NAME = lions

CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -Wpedantic -g -I./
LDLIBS = -lm

SANITIZE=off
ifeq ($(SANITIZE),on)
CFLAGS += -fsanitize=address
endif

.PHONY: all clean distclean install try

DRIVERS_PATH = ../drivers

all: $(PILOT_NAME)

install: $(DRIVERS_PATH)/$(PILOT_NAME)

try: install
	cd .. ; ./GrandPrix

$(DRIVERS_PATH)/$(PILOT_NAME): $(PILOT_NAME)
	cp $(PILOT_NAME) $(DRIVERS_PATH)

$(PILOT_NAME): src/$(PILOT_NAME).c src/path.c src/point_2D.c src/list.c src/map.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

distclean: clean
	rm -f $(PILOT_NAME)

clean:
	rm -f *~ *.o
