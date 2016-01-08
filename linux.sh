#!/bin/sh

echo "hello world"
echo "input two strings:"
#echo `expr 5 \* 3`
#echo `expr \3`
#read a b c d e
#product=`expr \( $a + $b + $c + $d + $e \) / 5`
#echo "The average is $product"
------------------------------------
#read file1
#if test -f $file1
#then
	#echo "file exists"
#else
	#echo "invalid file"

#fi----------------------------------
read str1 str2
if [ $str1 = $str2 ]
then
	echo "equal"
else
	echo "not equal"

fi-----------------------------------

#case
echo "input a number:"
read a
case $a in
	1) echo "normal";;
	2) echo "paranormal";;	
	3) echo "abnormal";;
	*) echo "ambot";;
esac---------------------------------

#forloop
for x in hello 1 * 2 goodbye
do 
	echo "looping ...x is set to $x"
done----------------------------------

for (( x=0 ; x<5 ; x++ ))
do
	echo "x is $x"
done

-------------------------------------

#while loop
while test -d $dir
do 
	echo "input another"
	read dir
done
------------------------------------

while [ "$input" != "bye" ]
do 
	echo "Please try something (bye to quit)"
	read input
	echo "You typed: $input"
done
------------------------------------

use test or [] for expression

------------------------------------
while [ "$input" != "bye" ]
do 
	echo "Please try something (bye to quit)"
	read input
	echo "You typed: $input"
done
-----------------------------------
#until

echo "input a number"
read dir

until test -d $dir
do
	echo "input another"
	read dir
done
----------------------------------
 #[ $x -lt 5 ]
x=0

until test $x -lt 5 
do
	echo "x is $x"
	x=`expr $x + 1`
	if [ $x -eq 5 ]; then
		echo "x is 5"
	fi
done
-----------------------------------
#!/bin/sh

echo "hello world"
echo "input file1 :"
read file1
echo "input file2 :"
read file2

if [ ! -f "$file1" ];
then
	echo "$file1 does not exist"

elif [ ! -f "$file2" ];
then
	echo "$file2 does not exist"
else
	f1=`ls -l $file1 | cut -c 1-10`
	f2=`ls -l $file2 | cut -c 1-10`
	if [ "$f1" = "$f2" ];
	then
		echo "The files are identical!"
		echo "$file1 : $f1"
		echo "$file2 : $f2"
	else
		echo "The files are not identical!"
		echo "$file1 : $f1"
		echo "$file2 : $f2"
	fi
	
fi
---------------------
special variables examples (shift command)
#!/bin/sh

echo "I was called the $# parameter"
echo "My name is $0"
echo "My first paramenter is $1"
echo "My second paramenter is $2"
echo "All parameters are $@"

if [ $# -gt 2 ];then
	echo "you sent more than two parameters"
else
	echo "success"
fi

while [ "$#" -gt 0 ]
do
	echo "\$1 is $1"; shift
done
------------------------------
($? command)---give an error message and redirect to other file
/usr/local/bin/my-command 2> net

if [ "$?" -ne 0 ]; then
	echo "sorry, we had a problem there!"
fi
-------------------------------
(process variable)
old_IFS="$IFS"
IFS=*
echo "Please input three data separated by colon"
read x y z
IFS=$old_IFS
echo "x is $x y is $y z is $z"
---------------------------------------
(arrays)
#bash filename


Unix[0]='Debian'
Unix[1]='Red Hat'
Unix[2]='Ubuntu'
Unix[3]='Suse'

echo ${Unix[2]}

//echo ${Unix[@]}    //display all of the index
//echo ${#Unix[@]}   // display the length of the array
//echo ${#Unix[1]}   //display the number of elements of the index
//echo ${Unix[@]:3:2}   //extraction by offset andlength for an array
//echo ${Unix[1]:0:4}
//echo ${Unix[@]/Ubuntu/SCO Unix}  //search and replace
----------------------------------
