// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;

    printf("%5c %4c\n", (char)'F', (char)'C' );
    
    while (fahr <= upper) {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    
    printf("\n");
    
    printf("%6c %5c\n", (char)'K', (char)'F' );
    
    float kelvin=lower;
    
    while(kelvin<=upper){
        fahr=(9.0/5.0)*(kelvin-273.0) + 32.0;
        printf("%03.3f %5f\n",(double)kelvin,(double)fahr);
        kelvin=kelvin+step;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    BOARD_End();
    while (1);
}
