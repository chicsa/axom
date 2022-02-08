// Copyright (c) 2017-2022, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level LICENSE file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)


//-----------------------------------------------------------------------------
///
/// file: example.cpp
///
//-----------------------------------------------------------------------------

#include "axom/core.hpp"
#include "axom/fmt.hpp"

#include <iostream>

int main()
{
   // Using fmt library exported by axom
   std::cout << axom::fmt::format(
        "Example of using and installed version of Axom {}",
        axom::getVersion()) << std::endl << std::endl;

   // Uses installed axom library
   axom::about();
}

