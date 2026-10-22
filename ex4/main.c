#include <stdio.h>

int main(void) {
    FILE *fp;
    
    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1f, 1.2f, 1.3f};

    int ra[3];
    char rb[3];
    float rc[3];

    fp = fopen("a.bin", "wb+");

    fwrite(a, sizeof(int), 3, fp);
    fwrite(b, sizeof(char), 3, fp);
    fwrite(c, sizeof(float), 3, fp);

    fseek(fp, 0, SEEK_SET);

    fread(ra, sizeof(int), 3, fp);
    fread(rb, sizeof(char), 3, fp);
    fread(rc, sizeof(float), 3, fp);

    for (int i = 0; i < 3; i++)
        printf("%d%c", ra[i], i == 2 ? '\n' : ' ');

    for (int i = 0; i < 3; i++)
        printf("%c%c", rb[i], i == 2 ? '\n' : ' ');

    for (int i = 0; i < 3; i++)
        printf("%f%c", rc[i], i == 2 ? '\n' : ' ');

    fclose(fp);

    return 0;
}
