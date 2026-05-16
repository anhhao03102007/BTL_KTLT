#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Admin.h"
#include "Function.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define WHITE   "\033[97m"

static void getFilePath(int mon, char *fileMocHoc) {
    switch (mon) {
        case 1: strcpy(fileMocHoc, "data/Calculus_2.txt");             break;
        case 2: strcpy(fileMocHoc, "data/Probability_Statistics.txt"); break;
        case 3: strcpy(fileMocHoc, "data/Political_Science.txt");      break;
        case 4: strcpy(fileMocHoc, "data/Physics.txt");                break;
        default: fileMocHoc[0] = '\0'; break;
    }
}

static void printAdminMenu() {
    printf("\n");
    // Sử dụng dấu + và - để tạo khung không bao giờ lỗi font
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " BOLD YELLOW "🛠   ADMIN MENU                     " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " GREEN "1." WHITE "  Them cong thuc                " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "2." WHITE "  Xoa cong thuc                 " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "3." WHITE "  Sua cong thuc                 " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "4." WHITE "  Tim kiem cong thuc            " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "5." WHITE "  Xem danh sach cong thuc       " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " DIM "0.  Quay lai                      " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "\n➤  " RESET BOLD "Lua chon: " RESET);
}


/* ============================================================
 *  THEM CONG THUC
 * ============================================================ */
void ThemCongThuc(char *nameFile) {

    FlushStdin();
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
 * ============================================================ */
void XoaCongThuc(char *nameFile) {
    if (nameFile == NULL) return;

    char ten[100];
    printf("  Nhap ten cong thuc can xoa: ");
    if (fgets(ten, sizeof(ten), stdin) == NULL) return;
    FlushStdin();
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
    if (fgets(tenTimKiem, sizeof(tenTimKiem), stdin) == NULL) { FreeList(List); return; }
    tenTimKiem[strcspn(tenTimKiem, "\n")] = '\0';

    if (tenTimKiem[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        FreeList(List);
        return;
    }
    ChuanHoaTen(tenTimKiem);

    int found = 0;
    Formula *current = List;
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
        current = current->next;
    }

    if (!found)
        printf("  Khong tim thay cong thuc '%s'!\n", tenTimKiem);

    FILE *fout = fopen(nameFile, "w");
    if (fout == NULL) {
        printf("  Loi: Khong the ghi file: %s\n", nameFile);
        FreeList(List);
        return;
    }

    current = List;
    while (current != NULL) {
        fprintf(fout, "%s | %s\n", current->ten, current->congthuc);
        current = current->next;
    }
    fclose(fout);
    FreeList(List);
}

/* ============================================================
 *  TIM CONG THUC THEO TEN
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
    if (fgets(tenTim, sizeof(tenTim), stdin) == NULL) { FreeList(List); return; }
    tenTim[strcspn(tenTim, "\n")] = '\0';

    if (tenTim[0] == '\0') {
        printf("  Ten cong thuc khong duoc de trong!\n");
        FreeList(List);
        return;
    }
    ChuanHoaTen(tenTim);

    FILE *fout = fopen("DisplayData.txt", "w");
    if (fout) fclose(fout);

    int found = 0;
    Formula *current = List;
    while (current != NULL) {
        if (strcmp(current->ten, tenTim) == 0) {
            printf("  %-30s | %s\n", current->ten, current->congthuc);
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
 *  MENU ADMIN
 * ============================================================ */
void Admin() {
    int choice = 0;
    char fileMocHoc[100];

    do {
        printAdminMenu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("  Vui long nhap so!\n");
            continue;
        }
        while (getchar() != '\n');

        if (choice == 0) break;

        int mon = Choice();
        if (mon == 0) { printf("  Quay lai menu Admin.\n"); continue; }
        getFilePath(mon, fileMocHoc);
        if (fileMocHoc[0] == '\0') { printf("  Mon hoc khong hop le!\n"); continue; }

        switch (choice) {
            case 1: ThemCongThuc(fileMocHoc);         break;
            case 2: XoaCongThuc(fileMocHoc);          break;
            case 3: SuaCongThuc(fileMocHoc);          break;
            case 4: TimCongThucTheoTen(fileMocHoc);   break;
            case 5: XuatDanhSachCongThuc(fileMocHoc); break;
            default: printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}