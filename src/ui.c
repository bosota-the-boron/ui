#include <ncurses.h>    // Bibliothèque pour gestion d'interface texte (fenêtres, couleurs, etc.)
#include <string.h>    // Pour strlen, utilisé dans l'affichage de la barre

#include "../include/ui.h"         // Déclarations des fonctions d'interface (prototype, etc.)

// Initialise l'interface utilisateur ncurses
void ui_init() {
    initscr();          // Initialise l'écran ncurses, remplace le terminal par une fenêtre
    cbreak();           // Mode cbreak : l'entrée clavier est disponible immédiatement, sans attendre la touche Entrée
    noecho();           // Désactive l'écho des caractères tapés (pas affichés automatiquement)
    curs_set(FALSE);    // Cache le curseur
    start_color();      // Active la gestion des couleurs
    use_default_colors(); // Permet d'utiliser la couleur par défaut du terminal comme arrière-plan (-1)

    // Initialise deux paires de couleurs :
    // 1 : texte vert sur fond par défaut
    init_pair(1, COLOR_GREEN, -1);
    // 2 : texte rouge sur fond par défaut (non utilisé ici mais prêt à servir)
    init_pair(2, COLOR_RED, -1);
}

// Termine proprement l'interface ncurses et restaure le terminal
void ui_deinit() {
    endwin();  // Termine ncurses, remet le terminal dans son état normal
}

// Efface tout l'écran pour préparer un nouvel affichage
void ui_clear() {
    clear();   // Efface le contenu de la fenêtre standard
}

void ui_draw_bar(int y, int x, int width, float percent, const char *label) {
    int filled = (int)(percent * width);

    mvprintw(y, x, "%-10s [", label);  // Aligne le label à gauche sur 10 caractères

    attron(COLOR_PAIR(1));
    for (int i = 0; i < filled; i++) {
        addch('#');
    }
    attroff(COLOR_PAIR(1));

    for (int i = filled; i < width; i++) {
        addch(' ');
    }

    addch(']');

    // Affiche le pourcentage juste après la barre
    mvprintw(y, x + 12 + width, " %.1f%%", percent * 100);
}

// Rafraîchit l'écran pour appliquer toutes les modifications affichées
void ui_refresh() {
    refresh();
}
