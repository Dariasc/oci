#include <cstdio>

int main(void) {
    int n, m;
    scanf("%i%i", &n, &m);

    int fake[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &fake[i]);
    }

    int target[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &target[i]);
    }


    int cost = 0;
    for (int i = 0; i < n; i++) {
        if (target[i] == fake[i]) {
            continue;
        }
        if (target[i] > fake[i]) {
            printf("no\n");
            return 0;
        }
        if (target[i] < fake[i]) {
            cost++;
            if (cost > m) {
                printf("no\n");
                return 0;
            }
        }
    }

    printf("si\n");
    return 0;
}
