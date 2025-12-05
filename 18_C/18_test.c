/*
 * Task: 18 (BMP/PNG)
 * Test Driver (C)
 * Student: [Ваше Прізвище]
 */

#include "18.h"

void process_input(FILE *in, Image *img)
{
    char cmd[16];
    int x, y, w, h, r, R, G, B;

    while (fscanf(in, "%s", cmd) != EOF)
    {
        if (strcmp(cmd, "RECT") == 0)
        {
            if (fscanf(in, "%d %d %d %d %d %d %d", &x, &y, &w, &h, &R, &G, &B) == 7)
            {
                Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
                draw_rect(img, x, y, w, h, p);
                printf("  -> Drawn RECT at %d,%d\n", x, y);
            }
        }
        else if (strcmp(cmd, "CIRCLE") == 0)
        {
            if (fscanf(in, "%d %d %d %d %d %d", &x, &y, &r, &R, &G, &B) == 6)
            {
                Pixel p = {(uint8_t)B, (uint8_t)G, (uint8_t)R};
                draw_circle(img, x, y, r, p);
                printf("  -> Drawn CIRCLE at %d,%d\n", x, y);
            }
        }
    }
}

int main()
{
    int mode;
    printf("\n=== BMP Toolkit Test (C) ===\n");
    printf("1. Generate New Image (Console/File)\n");
    printf("2. Modify Existing BMP\n");
    printf("3. Test ASCII View\n");
    printf("> ");
    if (scanf("%d", &mode) != 1)
        return 1;

    Image *img = NULL;

    if (mode == 1)
    {
        img = create_image(800, 600);
        clear_image(img, (Pixel){255, 255, 255});

        printf("Use file input? (0-No, 1-Yes): ");
        int use_file;
        scanf("%d", &use_file);

        if (use_file)
        {
            FILE *f = fopen("18_test.dat", "r");
            if (f)
            {
                process_input(f, img);
                fclose(f);
            }
            else
                printf("Error: 18_test.dat missing.\n");
        }
        else
        {
            printf("Enter commands (e.g. CIRCLE 400 300 100 0 0 255). Ctrl+D to stop.\n");
            process_input(stdin, img);
        }

        save_bmp(img, "output_c.bmp");
        printf("Saved to output_c.bmp\n");
    }
    else if (mode == 2)
    {
        printf("Enter filename to load: ");
        char fname[100];
        scanf("%s", fname);
        img = read_bmp(fname);
        if (img)
        {
            printf("Loaded successfully. Drawing a black circle at 50,50.\n");
            draw_circle(img, 50, 50, 30, (Pixel){0, 0, 0});
            save_bmp(img, "modified_c.bmp");
            printf("Saved to modified_c.bmp\n");
        }
        else
        {
            printf("Failed to load.\n");
        }
    }
    else if (mode == 3)
    {
        // Create small image for ASCII test
        img = create_image(40, 20);
        clear_image(img, (Pixel){0, 0, 0});                   // Black background
        draw_rect(img, 5, 5, 30, 10, (Pixel){255, 255, 255}); // White rect
        print_ascii_art(img);
    }

    if (img)
        free_image(img);
    return 0;
}