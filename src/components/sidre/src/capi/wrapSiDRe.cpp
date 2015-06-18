//
// Copyright (c) 2015, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory.
//
// All rights reserved.
//
// This source code cannot be distributed without permission and
// further review from Lawrence Livermore National Laboratory.
//
// wrapSiDRe.cpp
#define EXAMPLE_WRAPPER_IMPL
#include "wrapSiDRe.h"

extern "C" {
namespace asctoolkit {
namespace sidre {

bool ATK_name_is_valid(const char * name)
{

// splicer begin ATK_name_is_valid
bool rv = nameIsValid(name);
return rv;
// splicer end ATK_name_is_valid
}

}  // namespace asctoolkit
}  // namespace sidre
}  // extern "C"
