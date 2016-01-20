// wrapstrings.cpp
// This is generated code, do not edit
// wrapstrings.cpp
#include "wrapstrings.h"
#include <string>
#include "shroudrt.hpp"
#include "strings.hpp"

extern "C" {

// const string & getName()+pure
// function_index=0
/**
 * \brief return a string as argument
 *
 */
const char * STR_get_name()
{
// splicer begin function.get_name
const std::string & rv = getName();
// check for error
if (rv.empty()) {
    return NULL;
}

return rv.c_str();
// splicer end function.get_name
}

// void getName(string_result_as_arg & output+intent(out)+len(Loutput))+pure
// function_index=1
/**
 * \brief return a string as argument
 *
 */
void STR_get_name_bufferify(char * output, int Loutput)
{
// splicer begin function.get_name_bufferify
const std::string & rv = getName();
// check for error
if (rv.empty()) {
    std::memset(output, ' ', Loutput);
    return;
}

asctoolkit::shroud::FccCopy(output, Loutput, rv.c_str());
return;
// splicer end function.get_name_bufferify
}

// splicer begin additional_functions
// splicer end additional_functions

}  // extern "C"
