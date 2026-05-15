#include <stdio.h>
#include <string.h>
#include "Menu.h"
#include "Function.h"
#include "User.h"
#include "Admin.h"

void Account(void) {
    int choice = 0;
    char password[100];

    drawBox(5, 30, "SYSTEM ACCESS");
    printf("  1. User\n");
    printf("  2. Admin\n");
    printf("------------------------------\n");
    printf("  Selection > ");

    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("  Lua chon khong hop le!\n");
        return;
    }
    while (getchar() != '\n');

    if (choice == 1) {
        printf("\n  Dang dang nhap voi quyen User...\n");
        User();
    } else if (choice == 2) {
        printf("\n");
        drawBox(3, 32, "ADMIN PASSWORD REQUIRED");
        printf("  Password: ");
        if (scanf("%99s", password) != 1) {
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');

        if (strcmp(password, "admin123") == 0) {
            printf("\n  [SUCCESS] Dang nhap Admin thanh cong!\n");
            Admin();
        } else {
            printf("\n  [ERROR] Sai mat khau!\n");
        }
    } else {
        printf("  Lua chon khong hop le!\n");
    }
}

void Menu(void) {
    drawBox(3, 42, "FORMULA MANAGEMENT SYSTEM");
    Account();
}