#include <iostream>
#include "Register.h"

Register::Register()  
{
    value = 0;
}

 void Register::Setvalue(int v)
{
    value = v;    
}

int Register::Getvalue()
{
    return value;
}
