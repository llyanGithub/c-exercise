cc = gcc

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGETS = $(basename $(SRCS))

.PHONY: all
all: dep $(TARGETS)

mp3:mp3.o
	$(cc) -o mp3 mp3.o

muxRondomEncrypt:muxRondomEncrypt.o
	$(cc) -o muxRondomEncrypt muxRondomEncrypt.o

randomEncrypt:randomEncrypt.o
	$(cc) -o randomEncrypt randomEncrypt.o

queen:queen.o
	$(cc) -o queen queen.o

quickSort:quickSort.o
	$(cc) -o quickSort quickSort.o

dep:
%.d:%.c
	@rm -f $@
	@$(cc) -MM $< > $@

sinclude $(SRCS:.c=.d)

clean:
	@rm -f *.d *.o $(TARGETS)
