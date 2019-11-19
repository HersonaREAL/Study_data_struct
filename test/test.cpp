#include <stdio.h>

int main() {
    int i, j, k, depth = 4;
    for (j = 0; j < depth; j++) {
        int w = 1 << (depth - j + 1);
        if (j == 0)
            printf("%*c\n", w, '_');
        else {
            for (i = 0; i < 1 << (j - 1); i++) {
                printf("%*c", w + 1, ' ');
                for (k = 0; k < w - 3; k++) printf("_");
                printf("/ \\");
                for (k = 0; k < w - 3; k++) printf("_");
                printf("%*c", w + 2, ' ');
            }
            printf("\n");
            for (i = 0; i < 1 << (j - 1); i++)
                printf("%*c/%*c_%*c", w, '_', w * 2 - 2, '\\', w, ' ');
            printf("\n");
        }
        for (i = 0; i < 1 << j; i++)
            printf("%*c_)%*c", w - 1, '(', w - 1, ' ');
        printf("\n");
    }
    getchar();
}