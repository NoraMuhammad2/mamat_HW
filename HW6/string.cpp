#include "string.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
const int TRUE=1;
const int FALSE=0;


//Initiates an empty string
String::String(){	
	data=new char[1];//initializing a string (char) with the size 1
	data[0]='\0';//empty string
	length=1;//size of an empty string
}

//Initiates string from other string
String:: String(const String &str){
	length=str.length;
	data=new char[length];//initializing a string (char) with the size of str
	strcpy(data,str.data);
	data[length-1]='\0';
}

//Initiates a string from char array
String:: String(const char *str){
	length=strlen(str)+ 1;//+1 because we need a place for the '\0'
	data=new char[length];
	strcpy(data,str);
	data[length-1]='\0';
}

//destructor
String:: ~String(){
	delete[] this->data;
}

//Changes this from String
String &String::operator=(const String &rhs){
	if(this==&rhs){ 
		return *this;
		}
	delete [] data;
	char* copy_str=new char[rhs.length];//copy string
	strcpy(copy_str,rhs.data);
	copy_str[rhs.length-1]='\0';
	this->length=rhs.length;
	this->data=copy_str;
	return *this;
}

//Changes this from char array
String &String::operator=(const char *str){
	delete [] data;
	this-> length = strlen(str)+1;
	char* copy_str=new char[length];
	strcpy(copy_str,str);
	copy_str[length-1]='\0';
	this->data=copy_str;
	return *this;
}

//Returns true iff the contents of this equals to the
//  contents of rhs

bool String::equals(const String &rhs) const{
	if(this->length != rhs.length){
		return FALSE;
		}
	else if(strcmp(this->data,rhs.data)){//when strcmp failes 1 is returned
		return FALSE;
		}
 	return TRUE;
}


//Returns true iff the contents of this equals to rhs

bool String::equals(const char *rhs) const{	
	if(this->length != (strlen(rhs)+1)){
		return FALSE;
		}
	for(int i=0;i<(int)strlen(rhs);i++){
		if(this->data[i] != rhs[i]){
			return FALSE;
		}
		}
	return TRUE;		
}	

// a function that copies a string to **out
void copy_splited_string_to_out(char* string,String  **output,
	int initial,int last,int index){
	char current[last-initial];//the size of the string to this delimeter
	int start=initial+1;
	int i=0;
	while(start<last){
		current[i]=string[start];
		start++;
		i++;
	}
 	current[i]='\0';
 	(*output)[index]=String(current);
 	return;
} 

//Splits this to several sub-strings according to delimiters.
//Allocates memory for output that the user must delete (using delete[]).
//@note Does not affect this.
//@note If "output" is set to NULL, do not allocated memory, only
//compute "size".
void  String::split(const char *delimiters, String **output, size_t *size)
 const{
	if(this->data == NULL){
        	output = NULL;
        	*size = 0;
        	return;
    	}		
	if(delimiters==NULL){
	return;
	}
	if(size==NULL){
	return;
	}
	// first we want to count how many delimeters there are 
	//in our string in order to know what will be the size of out
	int our_delim=0;
	int lenth = ((int)this-> length);
	int total = ((int)strlen(delimiters));
	for(int i=0;i<lenth;i++){
		for(int j=0;j<total;j++){
			if(this->data[i]==delimiters[j]){
				our_delim++;
			}
		}
 	}
	//if output" is set to NULL, do not allocated memory, only
 	//compute "size". 
	if(output==NULL){
		*size=our_delim+1;
		return;
}
//spliting the strings..	 			
int initial=-1;
int index=0;
*output=new String[our_delim+1];
for(int i=0;i<lenth;i++){
	for(int j=0;j<total;j++){
		if(this->data[i]==delimiters[j]){
			copy_splited_string_to_out(this->data,output,initial,i,index);
			initial=i;
			index++;
			}
		}
 }
 // if we are here then we splited all
 // the strings but the last string remained
 // cause when i=this->length we exit from the
 // for and do not copy the last splited
 //the last splited string,so we have to copy
 // the last string to output	
 copy_splited_string_to_out(this->data,output,initial,lenth,index);
 *size=our_delim+1;	
 return;
}




//convert this to an integer. We can assume that the input
// is valid.
int String::to_integer() const{
	return atoi(this->data);
}


//any leading or trailing white-spaces.//not sure
//Does not change this.
String String::trim() const{
String my_string;
	my_string=this->data;
	int j=0;
	int k=0;
	for(int i=0;i<(int)this->length;i++){
		if(my_string.data[i]==' '){
			j=i+1;
			k=i;
			while(j<(int)this->length){
				my_string.data[k]=my_string.data[j];
				j++;
				k++;
				}
			my_string.length=my_string.length-1;//deleted one space	
			}
		}	
	return my_string;
}

























