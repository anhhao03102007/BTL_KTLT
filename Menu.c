#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Hàm phụ trợ xóa bộ đệm bàn phím
void xoaBoDemDauVao(void) {
    int kyTu;
    while ((kyTu = getchar()) != '\n' && kyTu != EOF) {}
}

// Hàm hiển thị Menu chính
int hienThiMenuChinh(void) {
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

    return luaChon;
}

// Hàm xử lý logic đăng nhập cho Admin
int dangNhapQuanTriVien(void) {
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

// Hàm hiển thị Menu môn học cho User
int hienThiMenuNguoiDung(void) {
    int luaChon;
    int trangThai;

    do {
        printf("\n========================================\n");
        printf("          DANH SACH MON HOC           \n");
        printf("========================================\n");
        printf("1. Cong thuc Giai tich\n");
        printf("2. Cong thuc Vat ly (Dong luc hoc, Nhiet dong luc hoc...)\n");
        printf("3. Cong thuc Xac suat thong ke\n");
        printf("4. Cong thuc Kinh te chinh tri\n");
        printf("0. Quay lai menu chinh\n");
        printf("========================================\n");
        printf("Vui long chon mon hoc (0-4): ");

        trangThai = scanf("%d", &luaChon);

        if (trangThai != 1) {
            printf("\n[LOI] Dau vao khong hop le. Vui long nhap ky tu so!\n");
            xoaBoDemDauVao();
            luaChon = -1;
        } else if (luaChon < 0 || luaChon > 4) {
            printf("\n[LOI] Lua chon khong ton tai. Vui long chon tu 0 den 4!\n");
        }
    } while (luaChon < 0 || luaChon > 4);

    return luaChon;
}

int main() {
    int luaChonNguoiDung;
    int luaChonMonHoc;

    do {
        luaChonNguoiDung = hienThiMenuChinh();

        switch (luaChonNguoiDung) {
            case 1:
                if (dangNhapQuanTriVien()) {
                    printf("\n=> Dang truy cap giao dien quan ly cong thuc (Them/Sua/Xoa)...\n");
                    // TODO: Gọi hàm hiển thị giao diện quản lý của Admin
                }
                break;
                
            case 2:
                // Vòng lặp con xử lý Menu Môn học
                do {
                    luaChonMonHoc = hienThiMenuNguoiDung();
                    
                    switch(luaChonMonHoc) {
                        case 1:
                            printf("\n=> Hien thi danh sach cong thuc Giai tich...\n");
                            break;
                        case 2:
                            printf("\n=> Hien thi danh sach cong thuc Vat ly...\n");
                            // TODO: In danh sách liên kết các công thức Vật lý
                            break;
                        case 3:
                            printf("\n=> Hien thi danh sach cong thuc Xac suat thong ke...\n");
                            break;
                        case 4:
                            printf("\n=> Hien thi danh sach cong thuc Kinh te chinh tri...\n");
                            break;
                        case 0:
                            printf("\n=> Dang quay lai Menu chinh...\n");
                            break;
                    }
                } while (luaChonMonHoc != 0); // Thoát khi chọn 0
                break;
                
            case 0:
                printf("\n=> Dang thoat he thong. Hen gap lai!\n");
                break;
        }
    } while (luaChonNguoiDung != 0); 

    return 0;
}