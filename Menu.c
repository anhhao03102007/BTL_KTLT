#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "Function.h"
#include "Menu.h"
#include "Admin.h"
#include "User.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define WHITE   "\033[97m"

void xoaBoDemDauVao(void) {
    int kyTu;
    while ((kyTu = getchar()) != '\n' && kyTu != EOF) {}
}

void hienThiMenuChinh() {
    int luaChon;
    int trangThai;

    while (1) {
        system("cls");

        printf("\n");
        printf(CYAN "+--------------------------------------+\n" RESET);
        printf(CYAN "|   " BOLD YELLOW "  HE THONG QUAN LY CONG THUC      " RESET CYAN "|\n" RESET);
        printf(CYAN "+--------------------------------------+\n" RESET);
        printf(CYAN "|   " GREEN "1." WHITE "  Dang nhap Admin                " RESET CYAN "|\n" RESET);
        printf(CYAN "|   " GREEN "2." WHITE "  Dang nhap User                 " RESET CYAN "|\n" RESET);
        printf(CYAN "+--------------------------------------+\n" RESET);
        printf(CYAN "|   " DIM "0.  Thoat chuong trinh             " RESET CYAN "|\n" RESET);
        printf(CYAN "+--------------------------------------+\n" RESET);
        printf(CYAN "\n   " RESET BOLD "Vui long nhap lua chon cua ban (0-2): " RESET);

        trangThai = scanf("%d", &luaChon);

        if (trangThai != 1) {
            printf(RED "\n[LOI] Dau vao khong hop le. Vui long nhap ky tu so!\n" RESET);
            xoaBoDemDauVao();
            printf(DIM "Nhan enter de thu lai..." RESET);
            _getch();
            continue;
        }

        if (luaChon < 0 || luaChon > 2) {
            printf(RED "\n[LOI] Lua chon khong ton tai. Vui long chon tu 0 den 2!\n" RESET);
            printf(DIM "Nhan enter de thu lai..." RESET);
            _getch();
            continue;
        }

        switch (luaChon) {
            case 1:
                if (dangNhapQuanTriVien()) {
                    Admin();
                } else {
                    printf(RED "\n[THAT BAI] Dang nhap Admin that bai!\n" RESET);
                    _getch();
                }
                break;
            case 2:
                User();
                break;
            case 0:
                printf(GREEN "\nCam on ban da su dung chuong trinh. Tam biet!\n" RESET);
                exit(0);
        }
    }
}

int dangNhapQuanTriVien() {
    char matKhau[50];
    const char matKhauDung[] = "admin123"; 
    
    printf("\n--- XAC THUC QUAN TRI VIEN ---\n");
    printf("Nhap mat khau: ");
    
    xoaBoDemDauVao();
    scanf("%49s", matKhau); 

    if (strcmp(matKhau, matKhauDung) == 0) {
        printf("\n[THANH CONG] Dang nhap Admin thanh cong!\n");
        Sleep(1000);        
        return 1; 
    } else {
        printf("\n[THAT BAI] Mat khau khong chinh xac!\n");
        printf("Nhan Enter de thu lai...");
        _getch();
        return 0; 
    }
}


