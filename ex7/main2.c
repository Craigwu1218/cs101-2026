#include <stdio.h>
#include <string.h>

#define BOOK_COUNT 6
#define TITLE_LEN 64

typedef struct Books {
    int id;
    int price;
    char title[TITLE_LEN];
} book_t;

void total_price(book_t books[], int n)
{
    int i, total = 0;

    for (i = 0; i < n; i++) {
        total += books[i].price;
    }
    printf("Total price: %d\n", total);
}

void list_books(book_t books[], int n)
{
    int i;

    printf("%-4s %-6s %s\n", "Id", "Price", "Title");
    for (i = 0; i < n; i++) {
        printf("%-4d %-6d %s\n", books[i].id, books[i].price, books[i].title);
    }
}

int main()
{
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };
    book_t loaded[BOOK_COUNT];
    FILE *fp;

    fp = fopen("Book.bin", "wb");
    if (fp == NULL) {
        printf("無法開啟 Book.bin\n");
        return 1;
    }
    fwrite(books, sizeof(book_t), BOOK_COUNT, fp);
    fclose(fp);

    fp = fopen("Book.bin", "rb");
    if (fp == NULL) {
        printf("無法讀取 Book.bin\n");
        return 1;
    }
    if (fread(loaded, sizeof(book_t), BOOK_COUNT, fp) != BOOK_COUNT) {
        printf("讀取 Book.bin 失敗\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    list_books(loaded, BOOK_COUNT);
    total_price(loaded, BOOK_COUNT);

    return 0;
}
