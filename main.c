#include <stdio.h>
#include <stdlib.h>

int dim = 8;

FILE *rndfile;

static int rnd(void) {
    int n;
    if (fread(&n, sizeof(int), 1, rndfile) != 1)
        printf("couldn't read /dev/urandom\n");
    return n;
}

int main(int argc, char **argv) {
    rndfile = fopen("/dev/urandom", "r");
    if (rndfile == NULL) {
        printf("couldn't open /dev/urandom\n");
        return 1;
    }
    
    if (argc == 2)
        dim = atoi(argv[1]);

    int colour = rnd()%8 + 40;
    char colourstr[8];
    sprintf(colourstr, "\e[0;%dm", colour);
    char resetstr[] = "\e[0;107m";

    int *arr = malloc((dim/2)*sizeof(int));


    for (int i = 0; i < dim+2 - dim%2; ++i)
        printf("%s  ", resetstr);
    printf("\e[0m\n");

    for (int row = 0; row < dim; ++row) {

        printf("%s  ", resetstr);
        for (int i = 0; i < dim/2; ++i) {
            arr[i] = rnd()%2;
            printf("%s  ", arr[i] ? colourstr : resetstr);
        }

        for (int i = 0; i < dim/2; ++i)
            printf("%s  ", arr[dim/2 - i - 1] ? colourstr : resetstr);

        printf("%s  ", resetstr);
        printf("\e[0m\n");
    }

    for (int i = 0; i < dim+2 - dim%2; ++i)
        printf("%s  ", resetstr);
    printf("\e[0m\n");

    free(arr);
    fclose(rndfile);

    return 0;
}
