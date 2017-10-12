export PROJDIR := $(CURDIR)
include makedefs
SUBDIRS := Drivers Tasks System Packages
firmware.axf: firmware.bin
	$(OBJCOPY) -O binary -S -j .text -j .data firmware.bin firmware.axf
firmware.bin: $(SUBDIRS) main.o
	$(LD) $(LDFLAGS) $(NEWLIB)/crt0.o main.o Drivers/*.o Tasks/*.o -L$(NEWLIB) -lc System/*.o -L$(TIVAWARE) -ldriver -L$(SENSORLIB) -lsensor $(FREERTOS)/*.o -lc -L/usr/lib/gcc/arm-none-eabi/5.4.1/armv7e-m/fpu/ -lgcc -o firmware.bin
$(SUBDIRS):
	$(MAKE) -C $@
.PHONY: $(SUBDIRS) clean
clean:
	find $(PROJDIR) -name "*.o" -delete
	rm -fv firmware.bin firmware.axf
