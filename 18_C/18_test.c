/* File: 18_test.c
   Task: 18 (BMP/PNG)
   Test driver for C implementation
   Done by: [ВАШЕ ПРІЗВИЩЕ] (Group [ВАША ГРУПА])
   Date: 05.12.2025
*/

#include "18.h"

void process_input(FILE *in, Image *img)
{
    char cmd[16];
    int x, y, w, h, r;
    int R, G, B;

    while (fscanf(in, "%s", cmd) != EOF)
    {
        if (strcmp(cmd, "RECT") == 0)
        {
            if (fscanf(in, "%d %d %d %d %d %d %d", &x, &y, &w, &h, &R, &G, &B) == 7)
            {
                Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
                draw_rect(img, x, y, w, h, p);
                printf("Processed: RECT %d %d %d %d\n", x, y, w, h);
            }
        }
        else if (strcmp(cmd, "CIRCLE") == 0)
        {
            if (fscanf(in, "%d %d %d %d %d %d", &x, &y, &r, &R, &G, &B) == 6)
            {
                Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
                draw_circle(img, x, y, r, p);
                printf("Processed: CIRCLE %d %d r=%d\n", x, y, r);
            }
        }
    }
}

int main()
{
    int mode;
    printf("Task 18 Test Driver (C Version)\n");
    printf("1. Console Input\n2. File Input (18_test.dat)\nChoose: ");
    if (scanf("%d", &mode) != 1)
        return 1;

    Image *img = create_image(800, 600);
    if (!img)
    {
        printf("Memory error\n");
        return 1;
    }

    /* FIX: Fill background with WHITE color instead of black */
    Pixel white = {255, 255, 255};
    clear_image(img, white);

    if (mode == 1)
    {
        printf("Enter commands (e.g., RECT x y w h r g b). Ctrl+D to stop.\n");
        process_input(stdin, img);
    }
    else
    {
        FILE *f = fopen("18_test.dat", "r");
        if (f)
        {
            process_input(f, img);
            fclose(f);
        }
        else
        {
            printf("Error: 18_test.dat not found!\n");
        }
    }

    if (save_bmp(img, "output_c.bmp"))
    {
        printf("Saved to output_c.bmp\n");
        print_file_info("output_c.bmp");
    }
    else
    {
        printf("Error saving file\n");
    }

    free_image(img);
    return 0;
}