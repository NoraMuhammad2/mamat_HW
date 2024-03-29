
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100

	

void mean(FILE *f){
	int grade;
	double avrg=0;
	int retval;
	int line_num=1;
	int error=0;
	int goodgrades=0;
	while(1){
		retval=fscanf(f,"%d",&grade);
		if(retval == EOF){
			break;
		}	
		else if(retval!=1){
			fprintf(stderr,"This is not a number:\%d\"\n",line_num);
			
			exit(1);
		}
		else if(grade>MAX || grade<MIN){
	    fprintf(stderr,"not in our range,line number is:\%d\"\n",line_num);
			exit(1);
				
		}
		avrg+=grade;
		line_num++;
		goodgrades=line_num-error-1;
	}
	fprintf(stdout,"%.2lf	",avrg/goodgrades);
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
	mean(f);

	fclose(f);
}

		
	
		
						
