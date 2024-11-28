KERNELDIR ?= ~/kernel-compiling/linux
PWD := $(shell pwd)
obj-m := hc_sr04.o

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
