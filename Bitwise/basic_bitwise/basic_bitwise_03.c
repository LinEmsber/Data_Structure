/* An example of bitwise operation */

// The following two case is equivalent:
//
// case 1:
//         if (b < 0){
//                 a++;
//         }
// 
// case 2:
//         a -= b >> 31;

#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv[])
{
        int32_t sint;

        sint = (10) >> 31;
        printf("sint = 10>>31: %d\n", sint);

        sint = (100) >> 31;
        printf("sint = 100>>31: %d\n", sint);

        sint = (-100) >> 31;
        printf("sint = -100>>31: %d\n", sint);

        sint = (-10) >> 31;
        printf("sint = -10>>31: %d\n", sint);

        sint = (0) >> 31;
        printf("sint = 0>>31: %d\n", sint);

}
