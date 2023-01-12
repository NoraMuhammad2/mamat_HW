#ifndef PORT_H
#define PORT_H


#include "generic-field.h"
#include "string.h"

const int SIZEPRT=2;

class Port : public  GenericField
{
String my_field;
public:
    Port(String pkts);
    int port_in[SIZEPRT];
    bool aux_match(String input);
    bool set_value(String packet);
    bool match(String value);
};

#endif 
