#include <stdio.h>      // Pour printf, fprintf, FILE*, fopen, fgets, sscanf, fclose
#include <stdlib.h>     // Pour exit, malloc (non utilisé ici, mais souvent utile)
#include <unistd.h>     // Pour usleep (pause en microsecondes)
#include <string.h> 


//Structure de la ram pour stocker /proc/meminfo
typedef struct 
{
    unsigned long long MemTotal, MemFree, Buffers, Cached, SwapTotal, SwapFree;
} ram_stats_t;

int read_ram_stat(ram_stats_t *meminfo){
    FILE *fp = fopen("/proc/meminfo", "r"); //Ouvre le fichier meminfo
    if (!fp) return -1;

    char line[256];
    if (fgets(line, sizeof(line), fp) == NULL){
        fclose(fp);
        return -1;
    }

    sscanf(line, "ram  %llu %llu %llu %llu %llu %llu %llu %llu",
           &meminfo->MemTotal, &meminfo->MemFree, &meminfo->Buffers,
           &meminfo->Cached, &meminfo->SwapTotal, &meminfo->SwapFree);
    
    fclose(fp);
    return 0;
