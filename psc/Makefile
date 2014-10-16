# Pascal Subset Compiler							Makefile
# ----------------------------------------------------------
INCDIR	= inc
SRCDIR	= src
OBJDIR	= obj

CC 		= gcc
LD		= gcc
CFLAGS	= -g -Wall -Wextra -I$(INCDIR)
LDFLAGS	= 
BIN		= psc

SRCS	= $(wildcard $(SRCDIR)/*.c)
OBJS	= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)) )
INCS	= $(wildcard $(INCDIR)/*.h)

all : $(BIN)

$(BIN) : $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $<
	mv -f *.o $(OBJDIR)

clean :
	rm -f $(BIN)

mrproper : clean
	rm -f $(OBJDIR)/*.o

.PHONY : all clean mrproper

depend:
	makedepend -I$(INCDIR) -Y --$(CFLAGS) --$(SRCS) 

# DO NOT DELETE

obj/al.o: inc/al.h inc/err.h inc/ts.h
obj/as.o: inc/inst.h inc/err.h inc/psc.h inc/errt.h inc/cl.h inc/ts.h
obj/as.o: inc/al.h inc/as.h
obj/err.o: inc/errt.h inc/err.h inc/psc.h inc/inst.h inc/cl.h inc/ts.h
obj/inst.o: inc/psc.h inc/inst.h inc/errt.h inc/cl.h inc/ts.h
obj/main.o: inc/inst.h inc/err.h inc/psc.h inc/errt.h inc/cl.h inc/ts.h
obj/main.o: inc/as.h inc/al.h
obj/psc.o: inc/inst.h inc/psc.h inc/errt.h inc/cl.h inc/ts.h inc/err.h
obj/psc.o: inc/al.h
obj/ts.o: inc/ts.h inc/cl.h
