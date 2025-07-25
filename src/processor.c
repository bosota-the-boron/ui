#include <stdio.h>      // Pour printf, fprintf, FILE*, fopen, fgets, sscanf, fclose
#include <stdlib.h>     // Pour exit, malloc (non utilisé ici, mais souvent utile)
#include <unistd.h>     // Pour usleep (pause en microsecondes)
#include <string.h> 



#define MAX_CORES 128

// Structure pour stocker les compteurs cumulés CPU lus depuis /proc/stat
typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} cpu_stats_t;

// Fonction qui lit les statistiques CPU depuis /proc/stat et remplit la structure cpu_stats_t
int read_cpu_stats(cpu_stats_t *stats) {
    FILE *fp = fopen("/proc/stat", "r");      // Ouvre le fichier /proc/stat en lecture
    if (!fp) return -1;                       // Si échec ouverture, retourne erreur

    char line[256];
    if (fgets(line, sizeof(line), fp) == NULL) {  // Lit la première ligne (celle qui commence par "cpu")
        fclose(fp);
        return -1;                           // Si erreur lecture, retourne erreur
    }

    // Extrait à partir de la ligne "cpu ..." les 8 compteurs dans stats
    sscanf(line, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu",
           &stats->user, &stats->nice, &stats->system, &stats->idle,
           &stats->iowait, &stats->irq, &stats->softirq, &stats->steal);

    fclose(fp);  // Ferme le fichier
    return 0;    // Retourne succès
}

// Calcule le pourcentage d'utilisation CPU entre deux mesures successives
float calculate_cpu_usage(const cpu_stats_t *prev, const cpu_stats_t *curr) {
    // Calcul des temps d'inactivité cumulés (idle + iowait) précédents et courants
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;

    // Calcul des temps d'activité cumulés précédents et courants (user, nice, system, irq, softirq, steal)
    unsigned long long prev_non_idle = prev->user + prev->nice + prev->system + prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_non_idle = curr->user + curr->nice + curr->system + curr->irq + curr->softirq + curr->steal;

    // Somme totale des temps CPU cumulés précédents et courants
    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long curr_total = curr_idle + curr_non_idle;

    // Calcul des différences entre les mesures successives
    unsigned long long totald = curr_total - prev_total;    // Différence du total
    unsigned long long idled = curr_idle - prev_idle;       // Différence du temps idle

    // Pour éviter la division par zéro
    if (totald == 0)
        return 0.0f;

    // Calcul du ratio d'utilisation CPU sur la période mesurée
    return (float)(totald - idled) / (float)totald;
}

// Lire les stats pour tous les CPU (cpu total + cpu0, cpu1, ...)
int read_all_cpu_stats(cpu_stats_t *stats_array, int *core_count) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    char line[512];
    int index = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "cpu", 3) != 0)
            break;  // On arrête dès qu'on ne lit plus une ligne commençant par "cpu"

        if (index >= MAX_CORES + 1)
            break;  // Évite dépassement

        sscanf(line, "cpu%*s %llu %llu %llu %llu %llu %llu %llu %llu",
               &stats_array[index].user,
               &stats_array[index].nice,
               &stats_array[index].system,
               &stats_array[index].idle,
               &stats_array[index].iowait,
               &stats_array[index].irq,
               &stats_array[index].softirq,
               &stats_array[index].steal);

        index++;
    }

    fclose(fp);
    *core_count = index - 1;  // Le premier (index 0) est "cpu" global
    return 0;
}
