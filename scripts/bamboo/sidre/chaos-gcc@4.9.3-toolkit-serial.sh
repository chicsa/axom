#!/bin/sh
echo "Configuring..."
echo "-----------------------------------------------------------------------"
./scripts/config-build.py -c gcc@4.9.3 --buildtype RelWithDebInfo -DENABLE_MPI=OFF
cd build-chaos-gcc@4.9.3-relwithdebinfo
echo "-----------------------------------------------------------------------"

echo "-----------------------------------------------------------------------"
echo "Generating C/Fortran binding..."
make generate
echo "-----------------------------------------------------------------------"

echo "Building..."
echo "-----------------------------------------------------------------------"
make -j16
echo "-----------------------------------------------------------------------"

echo "Run tests"
echo "-----------------------------------------------------------------------"
make test ARGS="-T Test -E 'mpi|parallel'"
echo "-----------------------------------------------------------------------"
