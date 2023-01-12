#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"

const int SIZE=4;
class ip : public  GenericField
{
String my_field;
int IP[SIZE];
int bits_num;// the number after slash(which bits to take)
bool aux_match(String input);
public:

	ip(String p);
   
    bool set_value(String packet);
    bool match(String value);//const cause this function is a getter
    
};

#endif 
