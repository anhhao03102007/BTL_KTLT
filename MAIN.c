#include <stdio.h>
#include <stdlib.h>
#include "Function.h"
#include "Menu.h"
#include "Admin.h"
#include "User.h"

int main() {
    int choice;
    do {
        hienThiMenuChinh();
        printf("\nVui long nhap lua chon cua ban (0-2): ");
        scanf("%d", &choice);
        xoaBoDemDauVao();

        switch (choice) {
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
                break;
            default:
                printf("\n[LOI] Lua chon khong ton tai. Vui long chon tu 0 den 2!\n");
        }
    } while (choice != 0);
    return 0;
}