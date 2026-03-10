#building "hw3.exe" from main.cpp using "g++"

ld = g++
cc = g++
ccopts = -c -g -Wall
ldopts = -g
req = main.o
tgt = hw3

$(tgt): $(req)
	$(ld) $(ldopts) $(req) -o $(tgt)

main.o: main.cpp
	$(cc) $(ccopts) main.cpp

clean:
	rm $(req)
	rm $(tgt)
