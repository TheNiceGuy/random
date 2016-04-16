#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.h"
#include "error.h"
#include "config.h"

suite_t* suite_new(uint taille) {
    suite_t* suite;

    /* On alloue la mémoire pour la structure. */
    suite = malloc(sizeof(suite_t));
    if(suite == NULL)
        RET("La mémoire est insuffisante.", NULL)

    /* On initialise la structure. */
    suite->taille = taille;

    /* On alloue la mémoire pour la suite. */
    suite->suite = malloc(taille*sizeof(int));
    if(suite->suite == NULL) {
        free(suite);
        RET("La mémoire est insuffisante.", NULL)
    }

    return suite;
}

void suite_delete(suite_t* suite) {
    /* On libère la mémoire. */
    free(suite->suite);
    free(suite);
}

int is_prime(uint a) {
    int i;

    /* On regarde s'il existe un diviseur au nombre. */
    for(i = 2; i <= sqrt(a); i++)
        if(a%i == 0)
            return FALSE;

    return TRUE;
}

int is_knuth(uint a, uint c, uint m) {
    int p;
    int r = TRUE;

    /* On s'assure que c et m sont copremier. */
    if(pgcd(c,m) != 1)
        ERROR("Le premier critère de Knuth n'est pas respecté : "
              "pgcd(c, m) = 1", r, FALSE)

    /* On s'assure que p|(a-1), ∀ p|m où p est premier. */
    for(p = 2; p < m; p++) {
        /* On vérifie que p est premier. */
        if(is_prime(p) == FALSE)
            continue;

        /* On vérifie que p|m. */
        if(m%p != 0)
            continue;
        
        /* On s'assure que p|(a-1). */
        if((a-1)%p != 0) {
            ERROR("Le deuxième critère de Knuth n'est pas respecté : "
                  "p|(a-1), ∀ p|m où p est premier", r, FALSE)
            break;
        }
    }

    /* On s'assure que 4|m => 4|(a-1). */
    if(m%4 == 0 && (a-1)%4 != 0)
        ERROR("Le troisième critère de Knuth n'est pas respecté : "
              "4|m => 4|(a-1)", r, FALSE)

    /* On s'assure que c∈N* tel que c<m. */
    if(c <= 0 || c >= m)
        ERROR("Le quatrième critère de Knuth n'est pas respecté : "
              "c∈N* tel que c<m", r, FALSE)

    return r;
}

suite_t* pseudo(uint a, uint c, uint m, uint x) {
    int i;
    suite_t* suite;

    /* On s'assure que m n'est pas nulle. */
    if(m <= 0)
        RET("La valeur m ne peut pas être nulle.", NULL)

    /* On s'assure que 2<=a<m. */
    if((a < 2) || (m <= a))
        RET("La valeur a doit respecter la condition suivante : 2 <= a < m.", NULL)

    /* On s'assure que 0<=x<m. */
    if((x < 0) || (m <= x))
        RET("La valeur x doit respecter la condition suivante : 0 <= x < m.", NULL)

    /* On s'assure de respecter le critère de Knuth. */
    if(!is_knuth(a, c, m))
        return NULL;

    /* On crée la structure de la suite de nombres. */
    suite = suite_new(m-1);
    if(suite == NULL)
        return NULL;

    /* On génère les nombres aléatoires. */
    suite->suite[0] = x;
    for(i = 1; i < suite->taille; i++) {
        suite->suite[i] = (a*x+c)%m;
        x = suite->suite[i];
    }

    return suite;
}

int pgcd(int a, int b) {
    /* On s'assure que les deux nombres ne sont pas nulle. */
    if(a == 0 && b == 0)
        return ERR;

    /* On retourne l'autre valeur si une seule d'entre elles est nulle. */
    if(a == 0) return b;
    if(b == 0) return a;

    /* Le pgcd de 1 ou 2 nombres négatifs est équivalent à leur valeur absolue. */
    a = abs(a);
    b = abs(b);

    /* On calcule le pgcd. */
    while(a != 0 && b != 0)
        if(a < b)
            b %= a;
        else
            a %= b;

    return (a==0?b:a);
}
