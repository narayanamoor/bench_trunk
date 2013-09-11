#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include "m5op.h"

void finalSAD(F2D* integralImg, int win_sz, F2D* retSAD)
{
int endR, endC;
int i, j, k;
endR = integralImg->height;
endC = integralImg->width;
k = 0;
sizeM=endC-win_sz;
sizeN=endR-win_sz;

asm volatile (
              "vmov d0, %[sizeN], %[sizeM]\n\t"
                                : 
              [sizeN] "r" (sizeN), [sizeM] "r" (sizeM)
                                :
             );
m5rh_start(kernel_number,1); 
int togo, size;
//togo = sizeM*sizeN - i;
//togo=(endC-win_sz)*(endR-win_sz) -i ;

//for(j=0; j<(endC-win_sz)*(endR-win_sz); j=j+8)
for(j=0; j< sizeM * sizeN; j=j+8)   
{    
    togo = sizeM*sizeN - j;                                                                                                                                    
    size = (togo > 8) ? 8 : togo;
     
     m5_rh_load_data(0, 1, 5 , 0); //Exec time  --subtraction takes only five cycles and they are all done in parallel
    for(i=0; size ; i++)
         {
              m5_rh_load_data(0, 2, 2, 0); //2 cycles for address generation (???)  //how many cycles for address generation???
              m5_rh_load_data(integralImg->data+j, size, 4, 1); //sizeof(int)=4  (should it be i or j ? ) (This line is the most confusing line for me !!!) --loading the data
              m5_rh_load_data(0, 1, 5 , 0); //Exec time  --subtraction takes only five cycles and they are all done in parallel
              //subsref(retSAD,i,j) = subsref(integralImg,(win_sz+i),(j+win_sz)) + subsref(integralImg,(i+1) ,(j+1)) - subsref(integralImg,(i+1),(j+win_sz)) - subsref(integralImg,(win_sz+i),(j+1));
              //asubsref(current,i+j) = asubsref(in1,i+j) - asubsref(in2,i+j); @Amin's code in diffs.c in sift_rh
              asubsref(retSAD,i+j) = asubsref(integralImg,(win_sz+i)+(j+win_sz)) + asubsref(integralImg,(i+1)+ (j+1)) - asubsref(integralImg,(i+1)+(j+win_sz)) - asubsref(integralImg,(win_sz+i)+(j+1)); 
              m5_rh_load_data(0, 0, 0, 0); //done 
            
          }
     }   
    m5rh_start(kernel_number,0);
      return;
  }
