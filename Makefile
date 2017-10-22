export PROJDIR := $(CURDIR)
include makedefs
SUBDIRS := Drivers Tasks System Packages
firmware.axf: firmware.bin
	$(OBJCOPY) -O binary -S -j .text -j .data firmware.bin firmware.axf
firmware.bin: $(SUBDIRS) main.o
	$(LD) $(LDFLAGS) $(NEWLIB)/crt0.o main.o Drivers/*.o Tasks/*.o -L$(NEWLIB) -lc System/*.o -L$(TIVAWARE) -ldriver -L$(SENSORLIB) -lsensor $(FREERTOS)/*.o -lc -lm -L/usr/lib/gcc/arm-none-eabi/6.3.1/thumb/v7e-m/fpv4-sp/hard/ -lgcc -o firmware.bin
$(SUBDIRS):
	$(MAKE) -C $@
.PHONY: $(SUBDIRS) clean docs
clean:
	find $(PROJDIR) -regextype posix-extended -regex ".*\.(o|pdf|aux|log)" -delete -print
	rm -fv firmware.bin firmware.axf
docs:
	$(MAKE) -C Documentation