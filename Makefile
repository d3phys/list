#
# Main makefile 
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

#
# Configuration 
#
include CONFIG

#
# Awesome flags collection
# Copyright (C) 2021, 2022 ded32, the TXLib creator
#
CXXFLAGS = -g --static-pie -std=c++14 -fmax-errors=100 -Wall -Wextra  	   \
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

ifdef CONFIG_LIST_DEV
CXXFLAGS += -D DEBUG
endif

SUBDIRS = ds tests dev

CXX = g++
CPP = $(CXX) -E 

TOPDIR	:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)

#
# Header files
#
HPATH  = $(TOPDIR)/include

DEBUG := false 

make: subdirs
	$(OBJS)

llist: subdirs ds/main.o
	$(CXX) $(CXXFLAGS) -o list ds/main.o ds/ds.o

test: subdirs
	cd tests && $(MAKE)
	$(CXX) $(CXXFLAGS) -o test tests/test.o ds/ds.o dev/dev.o
	./test

touch:
	@find $(HPATH) -print -exec touch {} \;

.EXPORT_ALL_VARIABLES: CXX CXXFLAGS CPP DEBUG

include $(TOPDIR)/Rules.makefile

### Dependencies ###
