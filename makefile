dirinfo: dirinfo.c
	gcc dirinfo.c -g -lm -o dirinfo

run: dirinfo
	./dirinfo

clean:
	rm *~
