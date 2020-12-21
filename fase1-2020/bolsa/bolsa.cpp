#include <cstdio>
#include <vector>

int main(void) {
    int n, x;
    scanf("%i%i", &n, &x);

    std::vector<int> products;
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%i", &value);
        // ignore if bigger than our x
        if (value > x) {
            continue;
        }

        // check if this one product is enough
        if (value <= x && value >= x/2.0) {
            printf("1\n");
            return 0;
        }
        // because of the earlier check every value in the array is < x/2 this is really helpful
        products.push_back(value);
    }

    int sum = 0;
    for (int i = 0; i < products.size(); i++) {
        sum += products[i];

        // sum & product < x/2 then sum+product < x
        if (sum >= x/2.0) {
            printf("1\n");
            return 0;
        }
    }

    printf("0\n");
    return 0;
}
