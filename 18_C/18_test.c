#include "18.h"

void process_input(FILE *in, Image *img) {
    char cmd[16];
    int x, y, w, h, r;
    int R, G, B;
    
    while (fscanf(in, "%s", cmd) != EOF) {
        if (strcmp(cmd, "RECT") == 0) {
            fscanf(in, "%d %d %d %d %d %d %d", &x, &y, &w, &h, &R, &G, &B);
            Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
            draw_rect(img, x, y, w, h, p);
            printf("Processing: RECT at %d,%d\n", x, y);
        } else if (strcmp(cmd, "CIRCLE") == 0) {
            fscanf(in, "%d %d %d %d %d %d", &x, &y, &r, &R, &G, &B);
            Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
            draw_circle(img, x, y, r, p);
            printf("Processing: CIRCLE at %d,%d\n", x, y);
        }
    }
}

int main() {
    int mode;
    printf("1. Console Input\n2. File Input (18_test.dat)\nChoose: ");
    if (scanf("%d", &mode) != 1) return 1;

    Image *img = create_image(800, 600);
    Pixel white = {255, 255, 255};
    draw_rect(img, 0, 0, 799, 599, white);

    if (mode == 1) {
        printf("Enter commands (e.g., RECT x y w h r g b). Ctrl+D to stop.\n");
        process_input(stdin, img);
    } else {
        FILE *f = fopen("18_test.dat", "r");
        if (f) {
            process_input(f, img);
            fclose(f);
        } else {
            printf("File not found!\n");
        }
    }

    save_bmp(img, "output_c.bmp");
    printf("Saved to output_c.bmp\n");
    free_image(img);
    return 0;
}