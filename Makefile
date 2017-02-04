all: x32 x64

x32: 
	gcc -m32 -c -x c -fPIC -o CPUx32.o CPU.c
	gcc -m32 -o CPUx32.so -shared CPUx32.o
	
x64:
	gcc -m64 -c -x c -fPIC -o CPUx64.o CPU.c
	gcc -m64 -o CPUx64.so -shared CPUx64.o
	
clean:
	rm CPU*.o
