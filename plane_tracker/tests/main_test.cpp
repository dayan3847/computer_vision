#include "../tools.h"

int main() {
    double coords[8];
    // get length
    int count = sizeof(coords) / sizeof(coords[0]);
    my_tools::getCenteredCoordinates(8, 0.1, coords);

    return 0;
}
