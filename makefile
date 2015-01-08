TARGET	= libmatmult.so
LIBSRCS	= libmatmult.c 
LIBOBJS	= libmatmult.o

OPT	= -g 
PIC	= -fPIC

CC	= cc
CFLAGS= $(OPT) $(PIC) $(XOPTS)

SOFLAGS = -shared 
XLIBS	= -xlib_lib=sunperf 

$(TARGET): $(LIBOBJS)
	$(CC) -o $@ $(SOFLAGS) $(LIBOBJS)

$(LIBOBJS): $(LIBSRCS)
	$(CC) -c $(LIBSRCS) $(XLIBS)

clean:
	@/bin/rm -f core core.* $(LIBOBJS)

 
