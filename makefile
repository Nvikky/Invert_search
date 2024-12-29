obj:=$(patsubst %.c,%.o,$(wildcard *.c))
res.exe: $(obj)
	gcc -o $@ $^
clean:
	rm -f *.exe *.o