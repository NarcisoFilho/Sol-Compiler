#ifndef __BOOLEAN_H_
#define __BOOLEAN_H_
    // Bring bool format to C, maintaining compatibility with C++ compilers(I hope, at least)
    #ifndef bool
        typedef enum {false, true} bool;        
    #endif
#endif