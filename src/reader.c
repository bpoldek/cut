#include "../inc/reader.h"
unsigned sleep(unsigned sec);

void *get_raw_data(void *c)
{
    while(1)
    {
        
        char *byte = (char*)c;
        FILE *fp= fopen("/proc/stat", "r");
        char line[80];
        uint8_t linesum=0;
        char *pline;
        pthread_mutex_lock(&mux_reader);
        while(fgets(line,sizeof(line),fp))
        {
                pline = line;
                if(*pline!='c')
                    break;
                strcpy(byte,line);
                byte = byte + strlen(line);
                linesum++;           
        }
        fclose(fp);
        pthread_mutex_unlock(&mux_reader);
    }
    return 0;
}
