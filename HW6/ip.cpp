#include "ip.h"
#include <iostream>
#include <stddef.h>
#include "string.h"
const int TRUE=1;
const int FALSE=0;
const int MAX_INTERVAL=256;
const int BITS_NUM=32;
const int BYTES=8;
const int DOTS_SIZE=3;
const int SLASH_SIZE=1;
const int ERR=-1;
const int SPLTIP_NUM=4; 
const int TWO=2;
const int ONE=1;



ip ::ip(String p) : my_field(p){
    for(int i=0;i<SPLTIP_NUM;i++){
        this->IP[i] = ERR;
    }
    this->bits_num = 0;
}

int Bits_ToCheck(int check_bits,int value){
    int aux = value;
    for (int i=0; i<(BYTES-check_bits); i++) {
        aux = aux/TWO;
    }
    return aux;
}


bool ip::set_value(String packet){
    char delimeter_dots[] = ".";
    char delimeter_slash[] = "/";
    String *dots;
    String *slash;
    size_t dots_num=DOTS_SIZE;
    size_t slash_num=SLASH_SIZE;
    packet.split(delimeter_slash, &slash, &slash_num);
    packet.split(delimeter_dots, &dots, &dots_num);
    //checking if our number is in the legeal interval
    for (int i=0;i<(int)dots_num;i++) {
        if(dots[i].to_integer() > MAX_INTERVAL 
        || dots[i].to_integer() < 0){
         delete[] dots;
           delete[] slash;
            return FALSE; 
            }
    }
    //checking if the number after the slash is in out bits interval (0-32)
   if(slash[ONE].to_integer() > BITS_NUM 
    || slash[ONE].to_integer()<0){
     delete[] dots;
            delete[] slash;
        return FALSE;
        }

       this->bits_num = slash[ONE].to_integer(); 
    
        for(int i=0; i<(int)dots_num;i++){
         this->IP[i] = dots[i].to_integer();
         }
      delete[] dots;
            delete[] slash;
  return TRUE;
}


bool ip::aux_match(String value){
    char delimeter_dots[] = ".";
    int  check_bits = this->bits_num;
    String *dots;
    value=value.trim();
    
	int aux_splitDots[SPLTIP_NUM];
	for(int i=0;i<SPLTIP_NUM;i++){
	aux_splitDots[i]=this->IP[i];
	}
    size_t dots_num=DOTS_SIZE;
    value.split(delimeter_dots, &dots, &dots_num);
    if(check_bits == 0){
    delete[] dots;
          
        return TRUE;
        }
    int i = 0;
    while (check_bits>0){
        if(check_bits>=BYTES 
        && dots[i].to_integer()!=this->IP[i])
            return FALSE;
        if((check_bits<BYTES) &&
           ((Bits_ToCheck(check_bits,dots[i].to_integer()))
            != (Bits_ToCheck(check_bits,aux_splitDots[i])))){
            delete[] dots;
            return FALSE;
            }
        check_bits = (check_bits - BYTES);
        i++;
    }
   delete[] dots;
    return TRUE;
}


bool ip::match(String input){
 size_t len;
 bool value = false;
 String *aux_split;

 input.split("=, ", &aux_split, &len);
  if(!len){ 
  delete[] aux_split;
  return false;
  }
 for(size_t i = 0; i < len; i+=TWO)
 {

  if(my_field.equals(aux_split[i])){
   value = aux_match(aux_split[i+ONE]);
       break;
     }
    }
   delete[] aux_split;
   return value;
 }











