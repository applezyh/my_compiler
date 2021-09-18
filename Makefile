SOURCE=test
test.out:./asm/print.s ./asm/test.s ./asm/scan.s
	./out/main.out ./${SOURCE}.c>./asm/${SOURCE}.s
	arm-linux-gnueabihf-gcc -g -c ./asm/${SOURCE}.s -static -o ./lib/${SOURCE}.o
	arm-linux-gnueabihf-gcc -g -c ./asm/print.s -static -o ./lib/print.o
	arm-linux-gnueabihf-gcc -g -c ./asm/scan.s -static -o ./lib/scan.o
	arm-linux-gnueabihf-gcc -g ./lib/${SOURCE}.o ./lib/print.o ./lib/scan.o -static -o ./out/${SOURCE}.out
qemu:
	qemu-arm ./out/test.out