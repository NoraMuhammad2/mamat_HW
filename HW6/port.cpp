#include "port.h"
#include <iostream>
#include <stddef.h>
#include "string.h"

const int TRUE=1;
const int FALSE=0;
const int LENGTH=2;
const int MAX=65535;
const int ONE=1;


Port ::Port(String pkts) : my_field(pkts)
{
    port_in[LENGTH] = 0;
}
//in this function we are going to use the string.h library we are going
//to use the split function whith the '-' delimiter to get an array that
// is splited like (number-number), we wil use the "to integer" function
// to convert to integers and we will use trim to delete white spaces
bool Port::set_value(String packet){

	char delimiters[ONE]={'-'};//1 place for'-' and one for '\0'
	size_t len =0;
	String *my_string;
	packet.split(delimiters,&my_string,&len);
	
	

	if((int)len!=LENGTH){
		return FALSE;//split failed
 	}
 	for (int i=0; i<(int)len ; i++){
 	if(my_string[i].to_integer()>=0||my_string[i].to_integer()<=MAX){
		port_in[i]=my_string[i].to_integer();
 	}
 	else{ 
 	delete [] my_string;
 	return false;}
 	}
 	delete [] my_string;
	return TRUE;//if we are here then set_value succeded 
	}
	
	bool Port::aux_match(String value){
	int my_number=(value.trim()).to_integer();
	if(port_in[0]>my_number || port_in[ONE]<my_number){
		return false;
	}
	return true;
}		


bool Port::match(String input){
 size_t len;
 bool value = false;
 String *aux_split;

 input.split("=, ", &aux_split, &len);
  if(!len){ 
  delete[] aux_split;
  return false;
  }
 for(size_t i = 0; i < len; i+=LENGTH)
 {

  if(my_field.equals(aux_split[i])){
   value = aux_match(aux_split[i+ONE]);
       break;
     }
    }
   delete[] aux_split;
   return value;
 }

		
		
