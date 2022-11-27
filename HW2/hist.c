
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 0
#define MAX 100
#define NBINS 10

	

void hist(FILE *f, int binschar){
	int retval;
	int line_num=1;
	int grade;
	double pace;
	int right;
	int left;
	int *bins =malloc(sizeof(int)*(binschar+1));
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
		else{
		int n = grade/(MAX/ binschar) ;
		if(n<binschar){
		bins[n]++;
		}
		else if(n == binschar){
		bins[n-1]++;
		}
		}
		line_num++;
	}
	 pace=MAX / binschar; 	 
	 for(int i=0;i<binschar; i++) {
	 	left = pace*i;
	 	if(i<binschar-1 && i==0){
	 	   	right= ((i+1)*(pace-1));
	 	 }
	 	 else if((i>0) && (i<binschar-1)){
	 		 right= left+pace-1;
	 	 }
	 	else if(binschar==MAX && i==(MAX-1)){
	 		right=left;
	 		fprintf(stdout,"%d-%d	%d\n",left,right,bins[i]);
	 		fprintf(stdout,"%d-%d	%d\n",left+1,right+1,bins[i+1]);
	 		break;
	   	}	
	 	else right=MAX; 
	 	fprintf(stdout,"%d-%d	%d\n",left,right,bins[i]);
	}
		free(bins);
}
int main(int argc, char**argv){
	FILE *f;
	f=stdin;
	int nbins=10;
	for(int i=1 ; i<argc-1; i++)
	{
	if(!strcmp(argv[i],"-"))
	  {
	  f=stdin;
	  }
	  else if(!strcmp(argv[i],"-n_bins"))
	  {
	  nbins= i<argc-1 ? atoi(argv[i+1]):NBINS;
	  i++;
	  }
	  else
	  {
	  f=fopen(argv[i], "r");
	  }
	}
	
	if(!f)
	{
	fprintf(stderr,"Find not found: \%s\"\n",argv[1]);
	return 1;
	}
	hist(f,nbins);
	fclose(f);
	return 0;
}
