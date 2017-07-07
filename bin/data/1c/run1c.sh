#! /bin/bash

../.././md.e t 300000

for i in {2..9}
do
	((j=$i**3))
	../.././md.e c 14 0.7 2 40000 2000 $j
done