#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "Function.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define WHITE   "\033[97m"

// Dùng chung cho cả User và Admin để tránh lặp code
static void getFilePath(int mon, char *fileMocHoc) {
    switch (mon) {
        case 1: strcpy(fileMocHoc, "data/Calculus_2.txt");             break;
        case 2: strcpy(fileMocHoc, "data/Probability_Statistics.txt"); break;
        case 3: strcpy(fileMocHoc, "data/Political_Science.txt");      break;
        case 4: strcpy(fileMocHoc, "data/Physics.txt");                break;
        default: fileMocHoc[0] = '\0'; break;
    }
}

static void printMenu() {
    printf("\n");
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " BOLD YELLOW "⚗   USER MENU                      " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " GREEN "1." WHITE "  Xem danh sach cong thuc       " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "2." WHITE "  Tim cong thuc theo mon hoc    " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " DIM "0.  Quay lai                      " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "\n➤  " RESET BOLD "Lua chon: " RESET);
}

void User() {
    int choice = 0;

    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        char fileMocHoc[100];
        int mon;

        switch (choice) {
            case 1:
                mon = Choice();
                if (mon == 0) { printf("  Quay lai menu User.\n"); continue; }
                getFilePath(mon, fileMocHoc);
                if (fileMocHoc[0] == '\0') { printf("  Mon hoc khong hop le!\n"); continue; }
                XuatDanhSachCongThuc(fileMocHoc);
                break;

            case 2:
                mon = Choice();
                if (mon == 0) { printf("  Quay lai menu User.\n"); continue; }
                getFilePath(mon, fileMocHoc);
                if (fileMocHoc[0] == '\0') { printf("  Lua chon mon hoc khong hop le!\n"); continue; }
                TimCongThucTheoTen(fileMocHoc);
                break;

            case 0:
                printf("  Dang quay lai...\n");
                break;

            default:
                printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}