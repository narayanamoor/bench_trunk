/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "disparity.h"

void computeSAD(I2D *Ileft, I2D* Iright_moved, F2D* SAD)
{
    int rows, cols, i, j, diff;
    
    rows = Ileft->height;
    cols = Ileft->width;
    int togo, size;
    //m5rh_start(kernel_number,1);
    
    //for(i=0; i<rows; i++)
    for (i=0; i < rows *cols;i+=8) 
    {
        togo = rows*cols - i;
        size = (togo > 8) ? 8 : togo;
        for(j=0; j<size ; j++)
        //for(j=0; j<cols; j++)
        {
              //m5_rh_load_data(0, 2, 2, 0); //2 cycles for address generation (???)  //how many cycles for address generation???
              //m5_rh_load_data(Ileft->data+i, size*4, 4, 1); //load data as many data elements as the number of size
            //  m5_rh_load_data(Iright_moved->data+i, size*4, 4, 1); //load data as many data elements as the number of size
          //    m5_rh_load_data(0, 1, 5 , 0); //Exec time  --subtraction takes only five cycles and they are all done in parallel
            //diff = subsref(Ileft,i,j) - subsref(Iright_moved,i,j);
             //** diff = asubsref(Ileft,i*1088+j) - asubsref(Iright_moved,i*1088+j);
              diff = asubsref(Ileft,i+j) - asubsref(Iright_moved,i+j);
              //printf("Ileft->width is %d \n",Ileft->width);
              //printf("Iright_moved->width is %d \n", Iright_moved->width);
              //**asubsref(SAD,i*1088+j) = diff * diff;
              asubsref(SAD,i+j) = diff * diff;
              //printf("SAD->width is %d \n",SAD->width);

        //      m5_rh_load_data(SAD->data+i, size, 4, 1); //store results
      //        m5_rh_load_data(0, 0, 0, 0); 
        }
    }
    //m5rh_start(kernel_number,0);

    
    return;
}

