#
# List data structure makefile
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS  = list.o

ds.o: $(OBJS) subdirs
	$(LD) -r -o $@ $(OBJS)

include $(TOPDIR)/Rules.makefile

### Dependencies ###
list.o: list.cpp /home/d3phys/Code/list/include/log.h \
 /home/d3phys/Code/list/include/config.h \
 /home/d3phys/Code/list/include/list.h
