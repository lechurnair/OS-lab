#!/bin/bash
#cutting out text cut -d ',' -f 1 /home/112001019/Downloads/OS_Lab_group.csv
#thing after d is the delimiter
file=$1
cut -d ',' -f3,4 ${file} | sed 's/"//g'| sed '1d' | sed 's/,/ /g'  >temp.1 

file1="groups/students_list.csv"

declare -A check
file1="groups/students_list.csv"
while read -ra line;
do
    for word in "${line[@]}";
    do
        check[$word]=$word;
    done;
done < $file1

#echo ${check[112001019]};

while read -ra line;
do
    for word in "${line[@]}";
    do
        if [ ${check[$word]} ];
	then
	
		unset check[$word]
		continue	
	else
	{
		echo "ERROR: Invalid / Repeated RollNo: "$word;
		sed -i "/$line/d" temp.1;
		}
	fi

    done;
done < temp.1 >&2

#echo "Heml0" >&2


awk -F" " '{
if($NF == $1)
	print $1;
else if($2<$1)
	print $2"_"$1;
else
	print $1"_"$2;
	
}' temp.1 >group.txt

#This snippet of code was for a previous version of code I wrote
#while read -ra line;
#do
#    for word in "${line[@]}";
#    do
#        if [ $word == "Invalid" ];
#	then
#		echo "${line[@]}";
#		sed -i "/$line/d" group.txt;	
#	else
#		continue
#	fi
#
 #   done;
#done < group.txt >&2

echo "Students who have registered for this course but have not responded to the form"
echo ${check[@]}
 
 
 
