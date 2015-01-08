TARGET	= libmatmult.so
LIBSRCS	= libmatmult.c 
LIBOBJS	= libmatmult.o

OPT	= -g 
PIC	= -fPIC

CC	= suncc
CFLAGS= $(OPT) $(PIC) $(XOPTS)

SOFLAGS = -shared 
XLIBS	= -xlic_lib=sunperf

$(TARGET): $(LIBOBJS)
	$(CC) -o $@ $(SOFLAGS) $(LIBOBJS) $(XLIBS)

clean:
	@/bin/rm -f core core.* $(LIBOBJS) 
