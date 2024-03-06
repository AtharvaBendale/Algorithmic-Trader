#------------------------
# Do not modify this file
#------------------------

all: trader iml

trader: trader.cpp receiver.h pair.h map.h hash_map.h part_two.h part_three.h utils.h
	g++ -g -std=c++20 trader.cpp -o trader

iml: iml.cpp
	g++ -g -std=c++20 iml.cpp -o iml

runpart1: iml trader
	sleep 1
	./trader 1 > output.txt &
	sleep 1
	./iml inputs/data1.txt
	sleep 1
	diff -Bw outputs/out1.txt output.txt

runpart2: iml trader
	sleep 1
	./trader 2 > output.txt &
	sleep 1
	./iml inputs/data2.txt
	sleep 1
	diff -Bw outputs/out2.txt output.txt

runpart3: iml trader
	sleep 1
	./trader 3 > output.txt &
	sleep 1
	./iml inputs/data3.txt
	sleep 1
	diff -Bw outputs/out3.txt output.txt


clean:
	rm -rf output.txt trader iml
	rm -rf *~
