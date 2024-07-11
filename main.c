#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dim = 8;

int main(int argc, char **argv) {
    srand(time(0));
    
    if (argc == 2)
        dim = atoi(argv[1]);

    int colour = rand()%8 + 40;
    char colourstr[8];
    sprintf(colourstr, "\e[0;%dm", colour);
    char resetstr[] = "\e[0;107m";

    int *arr = malloc((dim/2)*sizeof(int));

    for (int row = 0; row < dim; ++row) {
        for (int i = 0; i < dim/2; ++i) {
            arr[i] = rand()%2;
            printf("%s  ", arr[i] ? colourstr : resetstr);
        }

        for (int i = 0; i < dim/2; ++i)
            printf("%s  ", arr[dim/2 - i - 1] ? colourstr : resetstr);

        printf("\e[0m\n");
    }

    free(arr);

    return 0;
}
