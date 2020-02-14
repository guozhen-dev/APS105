#!/bin/bash
for i in {1..10}
do
	echo $i 
	sleep 1
	g++ ./rand.c -o rand 
	./rand > $i.in
	gcc -std=c99 -lm ./std.c -o std
	./std < $i.in > $i.out
	rm rand std
done
