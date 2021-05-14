test_static_lib : test_static_lib.c libmymath.a
	gcc $^ -o $@

libmymath.a : add.o sub.o multiply.o div.o
	ar rcs $@ $^

%.o : %.c
	gcc $< -o %@

run:
	make clean && ./test_static_lib

clean :
	-rm *.o *.a

