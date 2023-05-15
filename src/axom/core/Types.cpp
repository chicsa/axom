// Copyright (c) 2017-2023, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level LICENSE file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)

#include "axom/core/Types.hpp"

namespace axom
{
#ifdef AXOM_USE_MPI

// Default initialization of mpi_traits
template <class AxomType>
const MPI_Datatype mpi_traits<AxomType>::type = MPI_DATATYPE_NULL;

// Initialization of mpi_traits specializations
const MPI_Datatype mpi_traits<float64>::type = MPI_DOUBLE;
const MPI_Datatype mpi_traits<float32>::type = MPI_FLOAT;
const MPI_Datatype mpi_traits<std::int8_t>::type = MPI_INT8_T;
const MPI_Datatype mpi_traits<std::uint8_t>::type = MPI_UINT8_T;
const MPI_Datatype mpi_traits<std::int16_t>::type = MPI_INT16_T;
const MPI_Datatype mpi_traits<std::uint16_t>::type = MPI_UINT16_T;
const MPI_Datatype mpi_traits<std::int32_t>::type = MPI_INT32_T;
const MPI_Datatype mpi_traits<std::uint32_t>::type = MPI_UINT32_T;

  #ifndef AXOM_NO_INT64_T
const MPI_Datatype mpi_traits<std::int64_t>::type = MPI_INT64_T;
const MPI_Datatype mpi_traits<std::uint64_t>::type = MPI_UINT64_T;
  #endif /* end AXOM_NO_INT64_T */

#endif /* end AXOM_USE_MPI */

}  // end namespace axom
