#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Admin.h"
#include "Function.h"

    void Admin(){
        printf("Admin Menu\n");
        int choice = 0;
        int result;
        printf("1. Them cong thuc\n");
        printf("2. Xoa cong thuc\n");
        printf("0. Quay lai\n");
        printf("Selection > ");
        result = scanf("%d", &choice);
        if (result != 1) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le!\n");
            return;
        }
        
        if (choice == 1) {
            int Chon;
            do {
                Chon = Choice(); 
                if (Chon < 1 || Chon > 4) {
                    printf("Lua chon mon hoc khong hop le!\n");
                    continue;
                }
                switch(Chon) {
                    case 1: ThemCongThuc("data/Calculus_2.txt"); break;
                    case 2: ThemCongThuc("data/Probability_Statistics.txt"); break;
                    case 3: ThemCongThuc("data/Political_Science.txt"); break;
                    case 4: ThemCongThuc("data/Physics.txt"); break;
                }
                break;
            } while (1);
        } else if (choice == 2) {
            char ten[100] = {0};
            int Chon;
            printf("Nhap ten cong thuc can xoa: ");
            fflush(stdin);
            fgets(ten, sizeof(ten), stdin);
            ten[strcspn(ten, "\n")] = 0;
            if (strlen(ten) == 0) {
                printf("Ten cong thuc khong the trong!\n");
                return;
            }
            do {
                Chon = Choice(); 
                if (Chon < 1 || Chon > 4) {
                    printf("Lua chon mon hoc khong hop le!\n");
                    continue;
                }
                switch(Chon) {
                    case 1: XoaCongThuc(ten, "data/Calculus_2.txt"); break;
                    case 2: XoaCongThuc(ten, "data/Probability_Statistics.txt"); break;
                    case 3: XoaCongThuc(ten, "data/Political_Science.txt"); break;
                    case 4: XoaCongThuc(ten, "data/Physics.txt"); break;
                }
                break;
            } while (1);
        } else if (choice != 0) {
            printf("Lua chon khong hop le! Vui long thu lai.\n");
        }
    } while (choice != 0);
}