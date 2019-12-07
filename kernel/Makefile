
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386



objects = loader.o global_desc_table.o hw_port.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s 
	as $(ASPARAMS) -o $@ $<

mykernal.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects) 

install: mykernal.bin
	sudo cp $< /boot/mykernel.bin


# generate our iso file
mykernel.iso: mykernal.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/mykernel.bin

	# manually create grub.cfg entries
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "poopOS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	#produce the iso image
	grub-mkrescue --output=$@ iso

	rm -rf iso

done: 
	(VBoxManage controlvm poopOS poweroff && sleep 1) || true


# for testing, saves some time
run: mykernel.iso
	(VBoxManage controlvm poopOS poweroff && sleep 1) || true
	VirtualBox --startvm "poopOS" &

.PHONY: clean
clean: 
	rm -f $(objects) mykernal.bin mykernal.iso
