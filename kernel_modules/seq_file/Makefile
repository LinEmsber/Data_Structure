# Makefile

obj-m                   += seq_file.o


K_DIR := /lib/modules/$(shell uname -r)/build

PWD:=$(shell pwd)

all:
	$(MAKE) -C $(K_DIR)  M=$(PWD) modules
clean:
	rm -rf *.o *~ .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers
