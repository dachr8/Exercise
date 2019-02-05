//flexmemb.c -- Telescopic array member
#include <stdio.h>
#include <malloc.h>

struct flex {
    size_t count;
    double average, scores[];
};

void showFlex(const struct flex *p) {
    puts("Scores :");
    for (int i = 0; i < p->count; ++i)
        printf("%g ", p->scores[i]);
    printf("\nAverage %g\n", p->average);
}

int main(void) {
    size_t n = 5;
    double tot = 0;

    struct flex *pf1 = malloc(sizeof(struct flex) + n * sizeof(double));
    pf1->count = n;
    for (int i = 0; i < n; ++i) {
        pf1->scores[i] = 20.0 - i;
        tot += pf1->scores[i];
    }
    pf1->average = tot / n;
    showFlex(pf1);

    n = 9;
    tot = 0;
    struct flex *pf2 = malloc(sizeof(struct flex) + n * sizeof(double));
    pf2->count = n;
    for (int i = 0; i < n; ++i) {
        pf2->scores[i] = 20.0 - i / 2.0;
        tot += pf2->scores[i];
    }
    pf2->average = tot / n;
    showFlex(pf2);
    free(pf1);
    free(pf2);

    return 0;
}
