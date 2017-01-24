#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
        int32_t signed_int;

        signed_int = (10) >> 31;
        printf("signed_int = 10>>31: %d\n", signed_int);

        signed_int = (100) >> 31;
        printf("signed_int = 100>>31: %d\n", signed_int);

        signed_int = (-100) >> 31;
        printf("signed_int = -100>>31: %d\n", signed_int);

        signed_int = (-10) >> 31;
        printf("signed_int = -10>>31: %d\n", signed_int);

        signed_int = (0) >> 31;
        printf("signed_int = 0>>31: %d\n", signed_int);

}
