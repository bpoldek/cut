#include <stdio.h>

int main()
{
    FILE *fp = fopen("/proc/stat", "r");
    return 0; 
}