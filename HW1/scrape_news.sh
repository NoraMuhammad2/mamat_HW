#! /bin/bash

wget https://www.ynetnews.com/category/3082

articles=`grep -oP "https://(www.)?ynetnews.com/article/[a-zA-Z0-9]+" 3082| sort | uniq`

wget -iO - $articles
echo "$(echo "$articles" | wc -l)" >> results.csv
for line in $articles ;
  do
  articles2=$(echo "$line" | grep -o '[^/]\+$')
   printf "\n" >> results.csv
   N=$(grep -o "Netanyahu" "$articles2"| wc -w)
   G=$(grep -o "Gantz" "$articles2"| wc -w)
   L=$(grep -o "Lapid" "$articles2"| wc -w)
   B=$(grep -o "Ben-Gvir" "$articles2"| wc -w)
  
   if (( (( $N==0 )) && (( $L==0 )) && (( $B==0 )) && (( $G==0 )) )); then
echo "$line"", -" >> results.csv 
			
	else
		
echo "$line", "Netanyahu,"" $N"", Gantz,"" $G"", Lapid,"" $L"", Ben-gvir,"" $B" >> results.csv

fi

done 
