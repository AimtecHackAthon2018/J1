# name of the binary to build
TARGET   = upd
CC       = gcc
CROSS_COMPILE = /usr/bin/arm-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc

# These flags are used by the implicit rules for C preprocessor flags,
# C compiler flags, linker flags, and libraries to link (-lfoo options)
# -MD in CPPFLAGS means that the implicit rules for .o files will also
# generate a corresponding .d file that contains the dependencies.
CPPFLAGS = -MD
CFLAGS   = -O2 -g
#LDFLAGS  = --entry=main
#LDLIBS   = -lc -lm

# SRCS is a list of all .c files in the directory, the other two are
# pattern substitution expressions that take SRCS and replace the .c with .o
# and .d, respectively
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAFGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: all clean

# include dep files (if available).
-include $(DEPS)
