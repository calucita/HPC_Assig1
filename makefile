TARGET	= libmatmult.so
LIBSRCS	= libmatmult.c 
LIBOBJS	= libmatmult.o

OPT	= -g -fast -m64 -xO3 -xrestrict=%all -nprefetch_level=3
PIC	= -fPIC

CC	= suncc
CFLAGS= $(OPT) $(PIC) $(XOPTS)

SOFLAGS = -shared 
XLIBS	= -xlic_lib=sunperf

$(TARGET): $(LIBOBJS)
	$(CC) -o $@ $(SOFLAGS) $(LIBOBJS) $(XLIBS)

clean:
	@/bin/rm -f core core.* $(LIBOBJS) 
