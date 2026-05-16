#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Function.h"
#include "Menu.h"
#include "Admin.h"
#include "User.h"


// Hàm phụ trợ xóa bộ đệm bàn phím
void xoaBoDemDauVao(void) {
    int kyTu;
    while ((kyTu = getchar()) != '\n' && kyTu != EOF) {}
}

// Hàm hiển thị Menu chính
void hienThiMenuChinh() {
    int luaChon;
    int trangThai;
    do {
        printf("\n========================================\n");
        printf("      HE THONG QUAN LY CONG THUC      \n");
        printf("========================================\n");
        printf("1. Dang nhap tu cach Quan tri vien (Admin)\n");
        printf("2. Dang nhap tu cach Nguoi dung (User)\n");
        printf("0. Thoat chuong trinh\n");
        printf("========================================\n");
        printf("Vui long nhap lua chon cua ban (0-2): ");

        trangThai = scanf("%d", &luaChon);

        if (trangThai != 1) {
            printf("\n[LOI] Dau vao khong hop le. Vui long nhap ky tu so!\n");
            xoaBoDemDauVao();
            luaChon = -1; 
        } else if (luaChon < 0 || luaChon > 2) {
            printf("\n[LOI] Lua chon khong ton tai. Vui long chon tu 0 den 2!\n");
        }
    } while (luaChon < 0 || luaChon > 2);

    switch (luaChon) {
        case 1:
            if (dangNhapQuanTriVien()) {
                Admin();
            } else {
                printf("\n[THAT BAI] Dang nhap Admin that bai. Vui long thu lai!\n");
            }
            break;
        case 2:
            User();
            break;
        case 0:
            printf("\nCam on ban da su dung chuong trinh. Tam biet!\n");
            exit(0);
    }
}

// Hàm xử lý logic đăng nhập cho Admin
int dangNhapQuanTriVien() {
    char matKhau[50];
    const char matKhauDung[] = "admin123"; 
    
    printf("\n--- XAC THUC QUAN TRI VIEN ---\n");
    printf("Nhap mat khau: ");
    
    xoaBoDemDauVao();
    scanf("%49s", matKhau); 

    if (strcmp(matKhau, matKhauDung) == 0) {
        printf("\n[THANH CONG] Dang nhap Admin thanh cong!\n");
        return 1; // Đúng
    } else {
        printf("\n[THAT BAI] Mat khau khong chinh xac!\n");
        return 0; // Sai
    }
}




