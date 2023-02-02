#	Default makefile!
#	Add info later :p
#


CC = gcc
CX = g++

ln = g++
as = nasm

SFLAGS = -c -O2

CFLAGS += $(SFLAGS)
CXFLAGS += $(SFLAGS)

LFLAGS +=
AFLAGS +=

inc = inc
bin = bin
lib = lib
src = src

tgt = gracp
pth = /usr/bin/$(tgt)

default: all install

restore:
	rm test/counter_c.cpp
	rm test/counter_c.h
	rm $(wildcard test/*.o)

install:
	@ echo --== Installing $(tgt) to $(pth) ==--
	@ cp $(bin)/$(tgt).out $(pth)

all: gracp.o app.o
	$(ln) -o $(bin)/$(tgt).out $(wildcard $(lib)/*.o)


%.o: $(src)/%.c
	@ echo --=== Compiling $(lib)/$(notdir $@) ===--	From: $^
	@ $(CC) $(CFLAGS) -o $(lib)/$(notdir $@) -I $(inc) -L $(lib) $^


%.o: $(src)/%.cpp
	@ echo ++=== Compiling $(lib)/$(notdir $@) ===++	From $^
	@ $(CX) $(CXFLAGS) -o $(lib)/$(notdir $@) -I $(inc) -L $(lib) $^
