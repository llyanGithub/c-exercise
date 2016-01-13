cc = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGETS = Tree

.PHONY: all
all: dep $(TARGETS)

$(TARGETS):$(OBJS)
	$(cc) -o $(TARGETS) $(OBJS)

dep:
%.d:%.c
	@rm -f $@
	@$(cc) -MM $< > $@

sinclude $(SRCS:.c=.d)

clean:
	@rm -f *.d $(OBJS) $(TARGETS)
