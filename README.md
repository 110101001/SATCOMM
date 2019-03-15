compile:
  mkdir build
  cd build
  cmake ..
  make

usage:
  ./SatComm initTemp endTemp k controlerNum [snap files]
  
example:(you might need to copy those files to build/)
  ./SatComm 0.1 0.0000001 0.97 6 0400.snp 0500.snp 0600.snp
