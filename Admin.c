#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Admin.h"
#include "Function.h"

/* ============================================================
 *  THEM CONG THUC
 *  - Nhan ten va cong thuc tu ban phim
 *  - Ghi them vao cuoi file (append)
 *  BUG FIX: bo tham so Formula** thua, chi can char *nameFile
 * ============================================================ */
void ThemCongThuc(char *nameFile) {
    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf("  Loi: Khong the mo file: %s\n", nameFile);
        return;
    }

    char ten[100], congthuc[100];

    printf("  Nhap ten cong thuc : ");
    if (fgets(ten, sizeof(ten), stdin) == NULL) { fclose(fout); return; }
    ten[strcspn(ten, "\n")] = '\0';

    if (ten[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        fclose(fout);
        return;
    }
    ChuanHoaTen(ten);

    printf("  Nhap cong thuc     : ");
    if (fgets(congthuc, sizeof(congthuc), stdin) == NULL) { fclose(fout); return; }
    congthuc[strcspn(congthuc, "\n")] = '\0';

    if (congthuc[0] == '\0') {
        printf("  Cong thuc khong duoc de trong!\n");
        fclose(fout);
        return;
    }

    fprintf(fout, "%s | %s\n", ten, congthuc);
    fclose(fout);
    printf("  Da them cong thuc '%s' vao file '%s' thanh cong!\n", ten, nameFile);
}

/* ============================================================
 *  XOA CONG THUC
 *  - Tim theo ten, xoa khoi linked list
 *  - Ghi lai toan bo list vao file
 * ============================================================ */
void XoaCongThuc(char *nameFile) {
    if (nameFile == NULL) return;

    char ten[100];
    printf("  Nhap ten cong thuc can xoa: ");
    if (fgets(ten, sizeof(ten), stdin) == NULL) return;
    ten[strcspn(ten, "\n")] = '\0';

    if (ten[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        return;
    }
    ChuanHoaTen(ten);

    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu de xoa!\n");
        return;
    }

    /* Kiem tra ton tai truoc khi xoa */
    Formula *cur = List;
    int found = 0;
    while (cur) {
        if (strcmp(cur->ten, ten) == 0) { found = 1; break; }
        cur = cur->next;
    }
    if (!found) {
        printf("  Khong tim thay cong thuc '%s'!\n", ten);
        FreeList(List);
        return;
    }

    XoaNode(&List, ten);

    FILE *fout = fopen(nameFile, "w");
    if (fout == NULL) {
        printf("  Loi: Khong the ghi file: %s\n", nameFile);
        FreeList(List);
        return;
    }

    Formula *current = List;
    while (current != NULL) {
        fprintf(fout, "%s | %s\n", current->ten, current->congthuc);
        current = current->next;
    }
    fclose(fout);
    FreeList(List);

    printf("  Da xoa cong thuc '%s' va cap nhat file '%s' thanh cong!\n", ten, nameFile);
}

/* ============================================================
 *  SUA CONG THUC
 *  - Tim theo ten, cap nhat cong thuc moi trong linked list
 *  - Ghi lai toan bo list vao file
 *  BUG FIX #1: xoa khai bao current thu hai (compiler error)
 *  BUG FIX #2: them current = current->next vao vong while
 * ============================================================ */
void SuaCongThuc(char *nameFile) {
    if (nameFile == NULL) return;

    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu trong file: %s\n", nameFile);
        return;
    }

    char tenTimKiem[100];
    printf("  Nhap ten cong thuc can sua: ");
    if (fgets(tenTimKiem, sizeof(tenTimKiem), stdin) == NULL) {
        FreeList(List);
        return;
    }
    tenTimKiem[strcspn(tenTimKiem, "\n")] = '\0';

    if (tenTimKiem[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        FreeList(List);
        return;
    }
    ChuanHoaTen(tenTimKiem);

    int found = 0;
    Formula *current = List;                 /* FIX: chi khai bao 1 lan */
    while (current != NULL) {
        if (strcmp(current->ten, tenTimKiem) == 0) {
            printf("  Tim thay: %-30s | %s\n", current->ten, current->congthuc);
            printf("  Nhap cong thuc moi (Enter de giu nguyen): ");

            char congThucMoi[100];
            if (fgets(congThucMoi, sizeof(congThucMoi), stdin) == NULL) break;
            congThucMoi[strcspn(congThucMoi, "\n")] = '\0';

            if (strlen(congThucMoi) > 0) {
                strncpy(current->congthuc, congThucMoi, sizeof(current->congthuc) - 1);
                current->congthuc[sizeof(current->congthuc) - 1] = '\0';
                printf("  Da cap nhat: %-30s | %s\n", current->ten, current->congthuc);
            } else {
                printf("  Giu nguyen cong thuc cu.\n");
            }
            found = 1;
            break;
        }
        current = current->next;             /* FIX: them dong nay, tranh lap vo han */
    }

    if (!found)
        printf("  Khong tim thay cong thuc '%s'!\n", tenTimKiem);

    /* Ghi lai file sau khi sua */
    FILE *fout = fopen(nameFile, "w");
    if (fout == NULL) {
        printf("  Loi: Khong the ghi file: %s\n", nameFile);
        FreeList(List);
        return;
    }

    current = List;                          /* FIX: dung lai bien current cu */
    while (current != NULL) {
        fprintf(fout, "%s | %s\n", current->ten, current->congthuc);
        current = current->next;
    }
    fclose(fout);
    FreeList(List);
}

/* ============================================================
 *  TIM CONG THUC THEO TEN
 *  - Ho tro tim kiem khop chinh xac theo ten
 *  - Ket qua hien thi tren man hinh va luu vao DisplayData.txt
 * ============================================================ */
void TimCongThucTheoTen(char *nameFile) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu de tim kiem!\n");
        return;
    }

    char tenTim[100];
    printf("  Nhap ten cong thuc can tim: ");
    if (fgets(tenTim, sizeof(tenTim), stdin) == NULL) {
        FreeList(List);
        return;
    }
    tenTim[strcspn(tenTim, "\n")] = '\0';

    if (tenTim[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        FreeList(List);
        return;
    }
    ChuanHoaTen(tenTim);

    /* Xoa file output cu truoc khi ghi ket qua moi */
    FILE *fout = fopen("DisplayData.txt", "w");
    if (fout) fclose(fout);

    int found = 0;
    Formula *current = List;
    while (current != NULL) {
        if (strcmp(current->ten, tenTim) == 0) {
            /* In ra man hinh */
            printf("  %-30s | %s\n", current->ten, current->congthuc);
            /* Luu vao file */
            DisplayOutput(*current, "DisplayData.txt");
            found++;
        }
        current = current->next;
    }

    FreeList(List);

    if (!found)
        printf("  Khong tim thay cong thuc nao voi tu khoa: '%s'\n", tenTim);
    else
        printf("  Tim thay %d ket qua. Da luu vao 'DisplayData.txt'.\n", found);
}

/* ============================================================
 *  HAM DIEU PHOI ADMIN (MENU CHINH)
 * ============================================================ */
void Admin(void) {
    int choice = 0;
    char *fileMocHoc = NULL;

    do {
        printf("\n");
        drawBox(9, 36, "QUAN LY CONG THUC - ADMIN");
        printf("  1. Them cong thuc\n");
        printf("  2. Xoa cong thuc\n");
        printf("  3. Sua cong thuc\n");
        printf("  4. Tim kiem cong thuc\n");
        printf("  5. Xem danh sach cong thuc\n");
        printf("  0. Quay lai\n");
        printf("  Lua chon > ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("  Vui long nhap so!\n");
            continue;
        }
        while (getchar() != '\n'); /* Xoa buffer */

        if (choice == 0) break;

        /* Chon mon hoc truoc khi thuc hien */
        int mon = Choice();
        switch (mon) {
            case 1: fileMocHoc = "data/Calculus_2.txt";            break;
            case 2: fileMocHoc = "data/Probability_Statistics.txt"; break;
            case 3: fileMocHoc = "data/Political_Science.txt";      break;
            case 4: fileMocHoc = "data/Physics.txt";                break;
            case 0: printf("  Quay lai menu Admin.\n"); continue;
            default: printf("  Mon hoc khong hop le!\n");          continue;
        }

        switch (choice) {
            case 1: ThemCongThuc(fileMocHoc);       break;
            case 2: XoaCongThuc(fileMocHoc);        break;
            case 3: SuaCongThuc(fileMocHoc);        break;
            case 4: TimCongThucTheoTen(fileMocHoc); break;
            case 5: XuatDanhSachCongThuc(fileMocHoc); break;
            default: printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}