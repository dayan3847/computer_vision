#include "src/Main.h"

int main(int argc, char **argv) {
    char imagePath[256] = "";
    if (argc > 1)
        strncpy(imagePath, argv[1], 255);
    string imagePathStr(imagePath);
    Main main = Main(imagePathStr);
    main.run();

    return 0;
}
