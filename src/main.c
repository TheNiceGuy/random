#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "random.h"
#include "config.h"

void printn(char* num, int b, int a) {
    int i;

    for(i = 0; num[i] != '.'; i++);
    for(b -= i; b > 0; b--)
        printf(" ");
    printf("%s", num);
}

int get_int(char* string, int min, int max) {
    int input;

    do {
        printf("%s [%d, %d] : ", string, min, max);
        scanf("%d", &input);
    } while(input < min || input > max);

    return input;
}

char* get_Str(char* string, char* buff) {
    while(getchar() != '\n');
    printf("%s", string);

    if (fgets(buff, BUFF, stdin) == NULL)
        return NULL;

    if(buff[strlen(buff)-1] != '\n')
        while(getchar() != '\n');

    buff[strlen(buff)-1] = '\0';
    return buff;
}

void get_enter() {
    char key;

    printf("\nAppuyer sur <entré> pour continuer...");

    while ((key = getchar()) != '\n' && key != EOF);
    getchar();
}

void menu_rand() {
    int a, c, m, x, i;
    suite_t* suite;

    clear();
    a = get_int("Valeur a", 0, 9999);
    c = get_int("Valeur c", 0, 9999);
    m = get_int("Valeur m", 0, 9999);
    x = get_int("Valeur x", 0, 9999);

    printf("\n");

    suite = pseudo(a, c, m, x);
    if(suite == NULL) {
        get_enter();
        return;
    }

    printf("Voici la suite généré avec a=%d, c=%d, m=%d, x=%d :\n", a, c, m, x);

    printf("[");
    for(i = 0; i < suite->taille; i++)
        printf("%d, ", suite->suite[i]);
    printf("\b\b]\n");
    get_enter();

    free(suite);
}

int main() {
    int exit = FALSE;

    do {
        clear();
        printf("Que voulez-vous effectuer?\n\n");
        printf("[0] Généré une suite de nombres pseudo-aléatoires\n");
        printf("[1] Quitter\n");

        switch(get_int("Veuillez faire votre choix", 0, 1)) {
            case 0:
                menu_rand();
                break;
            case 1:
                exit = TRUE;
                break;
        }
    } while(!exit);

    return 0;
}
