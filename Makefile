CC= gcc
CFLAGS= -g

COMMON_C= src/main.c \
src/generate.c \
src/argparse/ap_inter.c \
src/argparse/argparse.c \
src/argparse/extract.c

COMMON_O= main.o \
generate.o \
argparse.o \
ap_inter.o \
extract.o

OUT= bench

all: base

base:
	$(CC) $(CFLAGS) -L src -c $(COMMON_C)
	$(CC) $(CFLAGS) -L src -o $(OUT) $(COMMON_O)
