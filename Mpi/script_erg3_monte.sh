#!/bin/bash

if [ $# -lt "2" ]
then
   echo "Usage script_erg3_monte.sh <number of throws> <number of processes>"
   exit
fi

numofnodes='-1 -2 -4 -8 -16'

mean=0
meanp=0
count=0

for i in $numofnodes
do

   head $i machines > text
   echo $1 | mpiexec -f text -np $2 ./mpi_monte_carlo >> text3
   rm text
done

sed '/Give number of iterations:/d' text3 > text2

rm text3

while read i1 i2 i3 i4 i5 i6 i7
do

   str="parallel"
   if [ $i4 = $str ]
   then
      mean=`echo "$mean+$i7" | bc -l | sed 's/^\./0./'`
      meanp=`echo "$meanp+$i3" | bc`

      let "count = count + 1"
   fi

done < text2

mean=`echo "$mean/$count" | bc -l | sed 's/^\./0./'`
meanp=`echo "$meanp/$count" | bc -l`

echo "mean p" $meanp "mean time" $mean
