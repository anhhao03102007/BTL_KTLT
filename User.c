#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "User.h"
#include "Function.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define WHITE   "\033[97m"

static void getFilePath(int mon, char *fileMocHoc,char *tenMon) {
    switch (mon) {
        case 1: 
            strcpy(fileMocHoc, "data/Calculus_2.txt");             
            strcpy(tenMon, "Giai tich");
            break;
        case 2: 
            strcpy(fileMocHoc, "data/Physic.txt");                
            strcpy(tenMon, "Vat ly"); 
            strcpy(fileMocHoc, "data/data/Probability_Statistics.txt"); 
            strcpy(tenMon, "Xac suat Thong ke"); 
            break;
        case 3: 
            strcpy(fileMocHoc, "data/data/Probability_Statistics.txt"); 
            strcpy(tenMon, "Xac suat Thong ke");  
            break;
        case 4: 
            strcpy(fileMocHoc, "data/Political_Economy.txt");      
            strcpy(tenMon, "Kinh te chinh tri"); 
            break;
        default: 
            fileMocHoc[0] = '\0'; 
            strcpy(tenMon, ""); 
            break;
    }
}

static void printMenu() {
    printf("\n");
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " BOLD YELLOW "   USER MENU                       " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " GREEN "1." WHITE "  Xem danh sach cong thuc        " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "2." WHITE "  Tim cong thuc theo mon hoc     " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " DIM "0.  Quay lai                       " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "\n   " RESET BOLD "Lua chon: " RESET);
}

void User() {
    int choice = 0;
    system("cls");
    do {
        printMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        char fileMocHoc[100];
        int mon;
        char tenMon[50];

        switch (choice) {
            case 1:
                system("cls");
                mon = Choice();
                if (mon == 0) { printf("  Quay lai menu User.\n"); continue; }
                getFilePath(mon, fileMocHoc, tenMon);
                if (fileMocHoc[0] == '\0') { printf("  Mon hoc khong hop le!\n"); continue; }
                XuatDanhSachCongThuc(fileMocHoc);
                break;

            case 2:
                system("cls");
                mon = Choice();
                if (mon == 0) { printf("  Quay lai menu User.\n"); continue; }
                getFilePath(mon, fileMocHoc, tenMon);
                if (fileMocHoc[0] == '\0') { printf("  Lua chon mon hoc khong hop le!\n"); continue; }
                TimCongThucTheoTen(fileMocHoc, tenMon);
                break;

            case 0:
                printf("  Dang quay lai...\n");
                break;

            default:
                printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}