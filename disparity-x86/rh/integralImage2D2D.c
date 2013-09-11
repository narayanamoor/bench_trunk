/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"
#include "m5op.h"
void integralImage2D2D(F2D* SAD, F2D* integralImg)
{
    int nr, nc, i, j;
    
    nr = SAD->height;
    nc = SAD->width;
    int togo,size;
    for(i=0; i<nc; i++)
        subsref(integralImg,0,i) = subsref(SAD,0,i);
   /* 
    for(i=1; i<nr; i++)
        for(j=0; j<nc; j++)
        {
            asubsref(integralImg,i+j) = asubsref(integralImg, i-1+ j) + asubsref(SAD,i+j);
        }

    for(i=0; i<nr; i++)
        for(j=1; j<nc; j++)
            asubsref(integralImg,i,j) = asubsref(integralImg, i+j-1) + asubsref(integralImg,i+j);
*/

      //@Amin: Does it sound about right to put both of the lines in just one nested loop?
      m5rh_start(101,1); //Begining of ROI
      for(i=1; i<nr*nc; i+=8)
      {
      	togo = nr*nc - i;
        size = (togo > 8) ? 8 : togo;
        m5_rh_load_data(0, 2, 1, 0); // 1 cycle for address generation as in SAD->data+i there's only one + operation (tree depth)
        //@Amin: Is address generation for line 38 and 39 done in parallel? My guess is "yes".
      	m5_rh_load_data(integralImg->data+i, size*4, 4, 1); //load data as many data elements as the number of size (each int/float size is 4 byte)
        m5_rh_load_data(SAD->data+i, size*4, 4, 1); //load data as many data elements as the number of size (each int/float size is 4 byte)
        m5_rh_load_data(0, 1, 10 , 0); //two dependent addition
        for(j=0; j<size; j++)
        {
            asubsref(integralImg,i+j) = asubsref(integralImg, i-1+ j) + asubsref(SAD,i+j);
            asubsref(integralImg,i,j) = asubsref(integralImg, i+j-1) + asubsref(integralImg,i+j);
        }
        m5_rh_load_data(integramImg->data+i, size*4, 4, 1); //store results
        m5_rh_load_data(0, 0, 0, 0); 
      }
    m5rh_start(101,0);
    return;
    
}
