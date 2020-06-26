/*
 * lib/operators.cpp
 */

#include <stdio.h>
#include "operators.h"
#include <stdlib.h>

void* operator new(size_t sz) throw()
{
//    cerr << "allocating " << sz << " bytes\n";
    void* mem = calloc(1, sz);
    if (mem)
        return mem;
    else
        return NULL;
}


void operator delete(void* ptr) throw()
{
//    cerr << "deallocating at " << ptr << endl;
    if(ptr)
        free(ptr);
}




