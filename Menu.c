#include<stdio.h>
#include"Menu.h"
#include"Function.h"
#include"User.h"
#include"Admin.h"
#include <string.h>

// Hàm vẽ khung có chứa nội dung văn bản bên trong

void Account() {
    int choice;
    char password[100];

    drawBox(5, 30, "SYSTEM ACCESS");
    printf("  1. User \n");
    printf("  2. Admin \n");
    printf("------------------------------\n");
    printf("Selection > ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nLogging in as User...\n");
        User();
    } 
    else if (choice == 2) {
        printf("\n");
        drawBox(3, 30, "ADMIN PASSWORD REQUIRED"); 
        printf("Password: ");
        scanf("%99s", password);

        if (strcmp(password, "admin123") == 0) {
            printf("\n[SUCCESS] Access Granted!\n");
            Admin();     
        } else {
            printf("\n[ERROR] Incorrect Password!\n");
        }
    }
}

    
    void Menu(){
        printf("Welcome to the Formula Management System\n");
        Account();
    }

