cc = gcc

SUB_DIR := FlashInit FlashImageBuilder c_exercise drawTree hackerPic 

all:
	@for n in $(SUB_DIR); do $(MAKE) -C $${n}; done
#	@for n in $(SUB_DIR); do $(shell echo $$(n)); done
#	$(MAKE) -C $(SUB_DIR)
#	$(foreach i, $(SUB_DIR), $(shell echo $(i)))

clean:
	@for n in $(SUB_DIR); do $(MAKE) -C $${n} clean; done
