#
# Development makefile
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS = 

ifdef CONFIG_LIST_DEV
OBJS += listdev.o
endif

#
# I'll fix this 'dummy' style... Later...
#
dev.o: $(OBJS) subdirs
	@touch dummy.cpp
	$(LD) -r -o $@ $(OBJS) dummy.cpp
	@rm dummy.cpp
	

include $(TOPDIR)/Rules.makefile

### Dependencies ###
listdev.o: listdev.cpp /home/d3phys/Code/list/include/list.h \
 /home/d3phys/Code/list/include/log.h \
 /home/d3phys/Code/list/include/config.h
