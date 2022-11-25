#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100

	

void max(FILE *f){
	int max=0;
	int retval;
	int line_number=1;
	int grade;
	while(1){
		retval=fscanf(f,"%d",&grade);
		if(retval == EOF){
			break;
		}	
		else if(retval!=1){
			fprintf(stderr,"This is not a number: \%d\"\n",line_number);
			exit(1);
		}
		else if(grade>MAX || grade<MIN){
			fprintf(stderr,"This is not in our range , line number is: \%d\"\n",line_number);
		}
		 else if(grade>max){
		max=grade;
		}
		line_number++ ;
	}
	fprintf(stdout,"%d	",max);
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
		return 1; /*failed*/
	}
	max(f);

	fclose(f);
}
