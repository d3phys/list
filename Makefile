#
# Main makefile 
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#


TOPDIR := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)

SUBDIRS = ds tests

# Header files #
HPATH  = $(TOPDIR)/include \
	 $(TOPDIR)/logs
	 
CXX = g++
CXXFLAGS = -I/$(TOPDIR)/dev -I/$(TOPDIR)/ent $(LOGS_FLAGS) $(TXFLAGS) -D DEBUG

LOGS_FILE  = logs.html
LOGS_FLAGS = -D LOGS_COLORS -D LOGS_FILE='"$(LOGS_FILE)"'

make: list.o

list.o: ds.o
	$(LD) -r -o list.o ds/ds.o

test: ds.o logs.o tests.o ent.o dev.o
	$(CXX) $(CXXFLAGS) -o test logs/logs.o tests/tests.o ds/ds.o dev/dev.o ent/ent.o
	./test

%.o:
	cd $(patsubst %.o,%, $@) && $(MAKE) -e

touch:
	@find $(HPATH) -print -exec touch {} \;

.EXPORT_ALL_VARIABLES: LD CXX CXXFLAGS CPP LOGS
include $(TOPDIR)/Rules.makefile

#
# Awesome flags collection
# Copyright (C) 2021, 2022 ded32, the TXLib creator
#
TXFLAGS =  -g --static-pie -std=c++14 -fmax-errors=100 -Wall -Wextra  	   \
	   -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat 	   \
	   -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual 	   \
	   -Wchar-subscripts -Wconditionally-supported -Wconversion        \
	   -Wctor-dtor-privacy -Wempty-body -Wfloat-equal 		   \
	   -Wformat-nonliteral -Wformat-security -Wformat-signedness       \
	   -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op 	           \
	   -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd 	   \
	   -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls \
	   -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192      \
	   -Wstrict-null-sentinel -Wstrict-overflow=2 			   \
	   -Wsuggest-attribute=noreturn -Wsuggest-final-methods 	   \
	   -Wsuggest-final-types -Wsuggest-override -Wswitch-default 	   \
	   -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused   \
	   -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 	   \
	   -Wno-missing-field-initializers -Wno-narrowing 	           \
	   -Wno-old-style-cast -Wno-varargs -fcheck-new 		   \
	   -fsized-deallocation -fstack-check -fstack-protector            \
	   -fstrict-overflow -flto-odr-type-merging 	   		   \
	   -fno-omit-frame-pointer                                         \
	   -fPIE                                                           \
	   -fsanitize=address 	                                           \
	   -fsanitize=alignment                                            \
	   -fsanitize=bool                                                 \
 	   -fsanitize=bounds                                               \
	   -fsanitize=enum                                                 \
	   -fsanitize=float-cast-overflow 	                           \
	   -fsanitize=float-divide-by-zero 			           \
	   -fsanitize=integer-divide-by-zero                               \
	   -fsanitize=leak 	                                           \
	   -fsanitize=nonnull-attribute                                    \
	   -fsanitize=null 	                                           \
	   -fsanitize=object-size                                          \
	   -fsanitize=return 		                                   \
	   -fsanitize=returns-nonnull-attribute                            \
	   -fsanitize=shift                                                \
	   -fsanitize=signed-integer-overflow                              \
	   -fsanitize=undefined                                            \
	   -fsanitize=unreachable                                          \
	   -fsanitize=vla-bound                                            \
	   -fsanitize=vptr                                                 \
	   -lm -pie                                          

### Dependencies ###
