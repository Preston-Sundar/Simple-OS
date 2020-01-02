AS_PARAMS = --32
LD_PARAMS = -melf_i386
C_FLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore

objects =	objects/loader.o 							\
		  	objects/kernel_main.o 						\
		  	objects/hardware/io.o 						\
		  	objects/kernel/kernel_misc.o				\
		  	objects/memory/set_table.o					\
		 	objects/memory/descriptor_table.o			\
		  


objects/%.o: src/%.s
	mkdir -p $(@D)
	as $(AS_PARAMS) -o $@ $<

objects/%.o: src/memory/%.s
	mkdir -p $(@D)
	as $(AS_PARAMS) -o $@ $<

objects/%.o: src/memory/%.c
	mkdir -p $(@D)
	gcc $(C_FLAGS) $< -o $@

objects/%.o: src/%.c
	gcc $(C_FLAGS) $< -o $@

objects/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<


objects/%.o: src/kernel/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<

objects/%.o: src/memory/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<

objects/%.o: src/hardware/%.cpp
	mkdir -p $(@D)
	gcc $(GPPPARAMS) -o $@ -c $<

objects/kernel.elf: src/linker.ld $(objects)
	ld $(LD_PARAMS) -T $< -o $@ $(objects) 


objects/kernel.iso: objects/kernel.elf
	mkdir -p src/kernel/iso/boot/grub
	cp $< src/kernel/iso/boot/kernel.elf
	cp src/kernel/etc/stage2_eltorito src/kernel/iso/boot/grub


	# manually create grub.cfg entries
	echo 'set timeout=0' >> src/kernel/iso/boot/grub/grub.cfg
	echo 'set default=0' >> src/kernel/iso/boot/grub/grub.cfg
	echo '' >> src/kernel/iso/boot/grub/grub.cfg
	echo 'menuentry "simpleOS_t" {' >> src/kernel/iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.elf' >> src/kernel/iso/boot/grub/grub.cfg
	echo '	boot' >> src/kernel/iso/boot/grub/grub.cfg
	echo '}' >> src/kernel/iso/boot/grub/grub.cfg

	grub-mkrescue --output=$@ src/kernel/iso

	rm -r src/kernel/iso


donevb: 
	(VBoxManage controlvm simpleOS poweroff && sleep 1) || true

# for testing, saves some time
runvb: objects/kernel.iso
	(VBoxManage controlvm simpleOS poweroff && sleep 1) || true
	VirtualBox --startvm "simpleOS" &


.PHONY: clean
clean: 
	rm -f bochslog.txt
	rm -f $(objects)
	rm -rf objects
	rm -f src/kernel/kernel.iso
	rm -f src/kernel/kernel.elf
	rm -f src/kernel/kernel_main.o
	rm -f src/kernel/loader.o


vb: clean runvb

# run bochs on the iso
bochs: clean objects/kernel.iso 
	sudo bochs -f src/kernel/etc/boch_cfg.txt -q


# makes testing a little quicker
show: 
	cat bochslog.txt | grep EAX
	cat bochslog.txt | grep EBX
	cat bochslog.txt | grep EDX

showall: 
	cat bochslog.txt