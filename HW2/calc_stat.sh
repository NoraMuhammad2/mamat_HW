#! /bin/bash

ArgNum=1  
courseNum=$1

if [[ ! $# -eq ArgNum ]];
then
         echo "Wrong number of arguments" >&2
         exit 1
 else
          
      if [[ ! -e $courseNum.txt ]];
       then
        echo "Course not found" >&2
         exit 1
      else    
        
         if [[ -d $courseNum"_stat" ]];  
      then
         rm -r $courseNum"_stat"
         fi
         fi
         mkdir $courseNum"_stat"
    fi
      
      gcc -g -Wall hist.c -o hist.exe
      gcc -g -Wall min.c -o min.exe
      gcc -g -Wall max.c -o max.exe
      gcc -g -Wall mean.c -o mean.exe
      gcc -g -Wall median.c -o median.exe
      cat "$courseNum.txt" | ./hist.exe  - -n_bins 10 >> $courseNum"_stat"/histogram.txt
      cat "$courseNum.txt" | ./mean.exe  -  >> $courseNum"_stat"/statistics.txt
      cat "$courseNum.txt" | ./median.exe  -  >> $courseNum"_stat"/statistics.txt
      cat "$courseNum.txt" | ./min.exe  -  >> $courseNum"_stat"/statistics.txt
      cat "$courseNum.txt" | ./max.exe  -  >> $courseNum"_stat"/statistics.txt
      cat "$courseNum.txt" | ./hist.exe - -n_bins 100 >regularhistogram.txt
	input=regularhistogram.txt
	counter=0
	allstudents=0
	succeeded=0
	while read -r line
	do
		mygrade=$(echo "$line" | grep -Eo '^[0-9]+')
		newgrade=$(echo "$line" | grep -Eo '[0-9]+$')
		echo "$grade"
		if [[ $newgrade -gt 0 ]]; then
			(( allstudents=allstudents+1 ))
		fi
		if [[ $mygrade -gt 54 ]]; then
			(( counter=counter+newgrade ))	
		fi	
	done < "$input"
	if [[ ! $allstudents -eq 0 ]]; then
	(( success=($counter*100)"/"$allstudents ))
	
	echo $success"%" >> $courseNum"_stat"/statistics.txt 
	fi
      
     
     
       
     
           
      

