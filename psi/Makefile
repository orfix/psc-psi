# Pascal Subset Interpreter							Makefile
# ----------------------------------------------------------
INCDIR	= inc
SRCDIR	= src
OBJDIR	= obj

CC 		= gcc
LD		= gcc
CFLAGS	= -g -Wall -Wextra -I$(INCDIR)
LDFLAGS	= 
BIN		= psi

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

obj/as.o: inc/err.h inc/psi.h inc/cl.h inc/inst.h inc/pile.h inc/errt.h
obj/as.o: inc/al.h inc/as.h
obj/err.o: inc/errt.h inc/err.h inc/psi.h inc/cl.h inc/inst.h inc/pile.h
obj/inst.o: inc/psi.h inc/cl.h inc/inst.h inc/pile.h inc/errt.h
obj/main.o: inc/err.h inc/psi.h inc/cl.h inc/inst.h inc/pile.h inc/errt.h
obj/main.o: inc/al.h inc/as.h
obj/pile.o: inc/pile.h
obj/psi.o: inc/err.h inc/psi.h inc/cl.h inc/inst.h inc/pile.h inc/errt.h
obj/psi.o: inc/al.h
