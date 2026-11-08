#include <iostream>
#include "Register.h"

Register::Register()  
{
    value = 0;
}

int Register::read() const
{
    return value;
}

void Register::write(int v)
{
    value = v;
}
