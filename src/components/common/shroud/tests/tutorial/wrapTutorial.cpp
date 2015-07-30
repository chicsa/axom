// wrapTutorial.cpp
// This is generated code, do not edit
// wrapTutorial.cpp
#define EXAMPLE_WRAPPER_IMPL
#include "wrapTutorial.h"
#include "tutorial.hpp"

extern "C" {
namespace tutorial {

void TUT_function1()
{
// splicer begin function.function1
Function1();
return;
// splicer end function.function1
}

double TUT_function2(double arg1, int arg2)
{
// splicer begin function.function2
double rv = Function2(arg1, arg2);
return rv;
// splicer end function.function2
}

bool TUT_function3(bool arg)
{
// splicer begin function.function3
bool rv = Function3(arg);
return rv;
// splicer end function.function3
}

const char * TUT_function4a(const char * arg1, const char * arg2)
{
// splicer begin function.function4a
const std::string & rv = Function4a(arg1, arg2);
return rv.c_str();
// splicer end function.function4a
}

const char * TUT_function4b(const char * arg1, const char * arg2)
{
// splicer begin function.function4b
const std::string & rv = Function4b(arg1, arg2);
return rv.c_str();
// splicer end function.function4b
}

double TUT_function5(double arg1, int arg2)
{
// splicer begin function.function5
double rv = Function5(arg1, arg2);
return rv;
// splicer end function.function5
}

void TUT_function6_0(const char * name)
{
// splicer begin function.function6_0
Function6(name);
return;
// splicer end function.function6_0
}

void TUT_function6_1(int indx)
{
// splicer begin function.function6_1
Function6(indx);
return;
// splicer end function.function6_1
}

// splicer begin additional_functions
// splicer end additional_functions

}  // namespace tutorial
}  // extern "C"
