#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100

void median(FILE* f) {
	int counter = 0;
	int students=0;
	int grade;
	int hist[100]={0};
	int badgrades=0;
	int linenumber=1;
	int retval=0;
	int mediangrade=0;
	int median=0;
		
	
	while(1){
	retval=fscanf(f,"%d",&grade);
	if(retval == EOF){
		break;
	}	
	else if(retval!=1){
		badgrades++;
		fprintf(stderr,"This is not a number: \%d\"\n",linenumber);
		exit(1);
	}
	else if(grade>MAX || grade<MIN){
		badgrades++;
		fprintf(stderr,"This is not in our range , line number is: \%d\"\n",linenumber);
	}
	hist[grade]++;
	linenumber++;
	}
	students=linenumber-badgrades-1;
	median= (students+1)/2;
	for (int i = 0; i < 100; i++) {
		counter += hist[i];
		if(counter>=median){
			mediangrade=i;
			break;					
		}
	}
	fprintf(stdout,"%d	",mediangrade);

}

int main(int argc, char**argv){
	FILE *f;
	if(argc == 1 || !strcmp("-",argv[1])){
		f=stdin;
	}	
	else{
		f=fopen(argv[1], "r" );
	}
	/*check errors*/
	if(!f){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1 ;/*failed*/
	}
	median(f);

	fclose(f);
}
