#include <stdio.h>      // Pour printf, fprintf, FILE*, fopen, fgets, sscanf, fclose
#include <stdlib.h>     // Pour exit, malloc (non utilisé ici, mais souvent utile)
#include <unistd.h>     // Pour usleep (pause en microsecondes)
#include <string.h>     // Pour manipuler les chaînes (pas utilisé directement ici)

#include "ui.h"         // Notre module personnalisé d'interface UI basé sur ncurses
#include "processor.h"




// Fonction principale (point d'entrée du programme)
int main() {
    cpu_stats_t prev_stats, curr_stats;  // Variables pour stocker deux lectures consécutives des stats CPU

    // Lecture initiale des stats CPU pour avoir une base de départ
    if (read_cpu_stats(&prev_stats) != 0) {
        fprintf(stderr, "Erreur lecture /proc/stat\n");   // Affiche un message d'erreur sur la sortie d'erreur standard
        return 1;     // Quitte le programme avec code d'erreur 1
    }

    ui_init();  // Initialise l'interface utilisateur (ncurses, couleurs, etc.)

    // Boucle infinie pour mettre à jour l'affichage toutes les 0,5 secondes
    while (1) {
        usleep(500 * 1000);  // Pause de 500 millisecondes (usleep prend des microsecondes)

        // Lecture actuelle des stats CPU
        if (read_cpu_stats(&curr_stats) != 0) {
            break;  // En cas d'erreur lecture, quitte la boucle proprement
        }

        // Calcul du pourcentage d'utilisation CPU entre les deux lectures
        float usage = calculate_cpu_usage(&prev_stats, &curr_stats);

        ui_clear();  // Efface l'interface pour un nouvel affichage propre
        ui_draw_bar(2, 2, 50, usage, "CPU Usage");  // Affiche une barre représentant l'utilisation CPU
        ui_refresh(); // Rafraîchit l'écran pour appliquer les changements

        prev_stats = curr_stats;  // Met à jour prev_stats pour la prochaine mesure (mémorisation)
    }

    ui_deinit();  // Quitte proprement ncurses, restaurer terminal

    return 0;     // Fin normale du programme
}
