#include <stdio.h>
#include <stdlib.h>
#include "User.h"
#include "Function.h"

void User(void) {
    int choice = 0;

    do {
        printf("\n");
        drawBox(6, 32, "USER MENU");
        printf("  1. Xem tat ca cong thuc\n");
        printf("  2. Tim cong thuc theo mon hoc\n");
        printf("  0. Quay lai\n");
        printf("  Lua chon > ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("  Vui long nhap so!\n");
            continue;
        }
        while (getchar() != '\n'); /* Xoa buffer */

        switch (choice) {
            case 1: {
                /* Xem tat ca: hien thi tung mon mot */
                char *files[] = {
                    "data/Calculus_2.txt",
                    "data/Probability_Statistics.txt",
                    "data/Political_Science.txt",
                    "data/Physics.txt"
                };
                char *tenMon[] = {
                    "Giai tich 2",
                    "Xac suat thong ke",
                    "Chu nghia khoa hoc xa hoi",
                    "Vat li"
                };
                for (int i = 0; i < 4; i++) {
                    printf("\n  --- %s ---\n", tenMon[i]);
                    XuatDanhSachCongThuc(files[i]);
                }
                break;
            }
            case 2: {
                int chon = Choice();
                char *fileMocHoc = NULL;

                switch (chon) {
                    case 1: fileMocHoc = "data/Calculus_2.txt";             break;
                    case 2: fileMocHoc = "data/Probability_Statistics.txt"; break;
                    case 3: fileMocHoc = "data/Political_Science.txt";      break;
                    case 4: fileMocHoc = "data/Physics.txt";                break;
                    case 0: printf("  Quay lai menu User.\n");              continue;
                    default: printf("  Lua chon mon hoc khong hop le!\n");  continue;
                }
                XuatDanhSachCongThuc(fileMocHoc);
                break;
            }
            case 0:
                printf("  Dang quay lai...\n");
                break;
            default:
                printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}