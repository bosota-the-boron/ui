#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ui.h"         // Interface utilisateur avec ncurses
#include "processor.h"  // Fonctions pour lire /proc/stat et calculer l'usage CPU

#define MAX_CORES 128   // Nombre max de cœurs supportés

int main() {
    cpu_stats_t prev_stats[MAX_CORES + 1], curr_stats[MAX_CORES + 1];
    int core_count;

    // Lecture initiale des stats CPU
    if (read_all_cpu_stats(prev_stats, &core_count) != 0) {
        fprintf(stderr, "Erreur : impossible de lire /proc/stat\n");
        return 1;
    }

    ui_init();  // Initialisation de l'interface ncurses

    while (1) {
        usleep(500 * 1000);  // Pause de 500 ms

        // Lire les stats actuelles
        if (read_all_cpu_stats(curr_stats, &core_count) != 0) {
            break;
        }

        ui_clear();  // Efface l'écran

        int start_row = 2;

        // Affiche l'utilisation totale du CPU
        float usage_total = 0.0f;
        for (int i = 1; i <= core_count; ++i) {
            usage_total += calculate_cpu_usage(&prev_stats[i], &curr_stats[i]);
        }
        usage_total /= core_count;
        ui_draw_bar(start_row, 2, 50, usage_total, "Total CPU");

        // Affiche l'utilisation par cœur
        for (int i = 1; i <= core_count; ++i) {
            float usage_core = calculate_cpu_usage(&prev_stats[i], &curr_stats[i]);

            char label[16];
            snprintf(label, sizeof(label), "Core %-2d", i - 1);  // Ex: "Core 11"

            ui_draw_bar(start_row + i, 2, 50, usage_core, label);
        }

        ui_refresh();  // Met à jour l'affichage

        // Mise à jour pour le prochain tour
        memcpy(prev_stats, curr_stats, sizeof(cpu_stats_t) * (core_count + 1));
    }

    ui_deinit();  // Quitte proprement ncurses
    return 0;
}
