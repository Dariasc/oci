#include <cstdio>

int n;

int main(void) {
    scanf("%i", &n);

    // where we at
    int height = 0, location = 0;

    // here we generate a mountain array from the provided indices
    int index_map[n];
    int mountains[n];
    for (int i = 0; i < n; i++) {
        int index;
        scanf("%i", &index);

        index_map[i] = index;

        if (i == 0) {
            location = index;
        }

        // the lower the number the taller bc why not
        mountains[index] = i;
    }


    int left_limit = 0;
    int right_limit = n - 1;

    bool changed = true;
    while (changed) {
        changed = false;

        // loop until we find the next valid mountain
        for (int h = height + 1; h < n; h++) {
            int new_mountain = index_map[h];

            // if the mountain is within limits
            if (new_mountain >= left_limit && new_mountain <= right_limit) {
                if (new_mountain > location) {
                    left_limit = location;
                } else {
                    right_limit = location;
                }
                location = new_mountain;
                height = h;
                changed = true;
                break;
            }
        }
    }

    // we couldn't find a valid mountain to glide to
    printf("%i\n", location);
    return 0;
}
