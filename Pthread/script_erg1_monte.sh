#!/bin/bash

if [ $# -lt "1" ]
then
   echo "Usage script_erg1_monte.sh <number of throws>"
   exit
fi

threads_num='2 4 8 16'
throws=$1

mean=0.000
meanp=0.000

count=0

for j in $threads_num
do
   echo 'run with' $throws "throws" 'and' $j "threads"
   ./monte_carlo $throws $j >> text
   echo
done

while read i1 i2 i3 i4 i5 i6
do

  str="parallel"
  if [ $i4 = $str ] || [ $i4 = "" ]
  then
     mean=`echo "$mean+$i6" | bc`
     meanp=`echo "$meanp+$i3" | bc`

     let "count = count + 1"
  fi

done < text

mean=`echo "$mean/$count" | bc -l`
meanp=`echo "$meanp/$count" | bc -l`

echo "mean p" $meanp "mean time" $mean

