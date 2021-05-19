// See LICENSE for license details.

//**************************************************************************
// Multi-threaded Matrix Multiply benchmark
//--------------------------------------------------------------------------
// TA     : Christopher Celio
// Student: 
//
//
// This benchmark multiplies two 2-D arrays together and writes the results to
// a third vector. The input data (and reference data) should be generated
// using the matmul_gendata.pl perl script and dumped to a file named
// dataset.h. 

//--------------------------------------------------------------------------
// Includes 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset.h"
 

//--------------------------------------------------------------------------
// Basic Utilities and Multi-thread Support

#include "util.h"

   
//--------------------------------------------------------------------------
// matmul function
 
extern void matmul(const size_t coreid, const size_t ncores, const size_t lda,  const data_t A[], const data_t B[], data_t C[] );


void main(int cid, int nc)
{
   static data_t results_data[ARRAY_SIZE];

   stats(matmul(0, 1, DIM_SIZE, input1_data, input2_data, results_data), DIM_SIZE/DIM_SIZE/DIM_SIZE);
 
   int res = verify(ARRAY_SIZE, results_data, verify_data);

   printf("res : %d\n",res);
   return 0;
}
