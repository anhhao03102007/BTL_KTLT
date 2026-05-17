#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "Function.h"
#include "Menu.h"
#include "Admin.h"
#include "User.h"

#define RED     "\033[31m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
// Hàm phụ trợ xóa bộ đệm bàn phím

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
        
        printf("\n" CYAN "========================================" RESET "\n");
        printf("       HE THONG QUAN LY CONG THUC       ");
        printf("\n" CYAN "========================================" RESET "\n");
        printf(GREEN "1." RESET " Dang nhap tu cach Quan tri vien (Admin)\n");
        printf(GREEN "2." RESET " Dang nhap tu cach Nguoi dung (User)\n");
        printf(GREEN "0." RESET " Thoat chuong trinh");
        printf("\n" CYAN "========================================" RESET "\n");
        printf("Vui long nhap lua chon cua ban (0-2): ");

        trangThai = scanf("%d", &luaChon);

        if (trangThai != 1) {
            printf("\n" RED "[LOI] Dau vao khong hop le. Vui long nhap ky tu so!" RESET "\n");
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
                    break; 
                }
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
    
    printf("\n" YELLOW "--- XAC THUC QUAN TRI VIEN ---" RESET "\n");
    printf("Nhap mat khau: ");
    
    xoaBoDemDauVao();
    scanf("%49s", matKhau); 

    if (strcmp(matKhau, matKhauDung) == 0) {
        printf("\n" GREEN "[THANH CONG] Dang nhap Admin thanh cong!" RESET "\n");
        Sleep(1000);        
        return 1; 
    } else {
        printf("\n" RED "[THAT BAI] Mat khau khong chinh xac!" RESET "\n");
        printf(YELLOW "Nhan Enter de thu lai..." RESET);
        _getch();
        return 0; 
    }
}


