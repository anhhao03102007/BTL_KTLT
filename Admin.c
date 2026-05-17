#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "Admin.h"
#include "Function.h"

#define RED     "\033[31m"
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

static void printAdminMenu() {
    printf("\n");
    system("cls");
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " BOLD YELLOW "   ADMIN MENU                     " RESET CYAN "|\n" RESET);
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
void ThemCongThuc(char *nameFile, char *tenMon) {
    if (nameFile == NULL) return;
    
    FlushStdin();
    system("cls");
    printf("\nBan da chon chuc nang " GREEN "THEM CONG THUC" RESET " cho mon hoc: " YELLOW "%s\n" RESET, tenMon);

    char ten[100], congthuc[100];

    // 1. Nhập và chuẩn hóa tên
    printf("  Nhap ten cong thuc : ");
    if (fgets(ten, sizeof(ten), stdin) == NULL) return;
    ten[strcspn(ten, "\n")] = '\0';
    if (ten[0] == '\0') {
        printf(RED "  [LOI] Ten khong duoc de trong!\n" RESET);
        return;
    }
    ChuanHoaTen(ten);

    Formula *List = NULL;
    LoadFile(&List, nameFile); 
    Formula *temp = List;
    while (temp != NULL) {
        if (strcmp(temp->ten, ten) == 0) {
            printf(RED "  [LOI] Cong thuc '%s' da ton tai!\n" RESET, ten);
            FreeList(List);
            printf("  Nhan enter de tiep tuc...");
            _getch();
            return;
        }
        temp = temp->next;
    }
    FreeList(List); 

  
    printf("  Nhap noi dung      : ");
    if (fgets(congthuc, sizeof(congthuc), stdin) == NULL) return;
    congthuc[strcspn(congthuc, "\n")] = '\0';
    if (congthuc[0] == '\0') {
        printf(RED "  [LOI] Noi dung khong duoc de trong!\n" RESET);
        return;
    }

    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf(RED "  [LOI] Khong the mo file!\n" RESET);
        return;
    }
    fprintf(fout, "%s | %s\n", ten, congthuc);
    fclose(fout);

    printf(GREEN "\n  => Da them '%s' thanh cong!\n" RESET, ten);
    printf("  Nhan enter de tiep tuc...");
    _getch();
}

/* ============================================================
 *  XOA CONG THUC
 * ============================================================ */
void XoaCongThuc(char *nameFile, char *tenMon) {
    if (nameFile == NULL) return;
    FlushStdin();
    Formula *List = NULL;
    LoadFile(&List, nameFile); 
    
    system("cls");
    printf("\n    Ban da chon chuc nang " GREEN "XOA CONG THUC" RESET " cho mon hoc: " YELLOW "%s\n" RESET, tenMon);

    if (List == NULL) {
        printf(RED "  [LOI] Khong co du lieu de xoa!\n" RESET);
        printf("  Nhan enter de quay lai...");
        _getch();
        return;
    }

        printf(CYAN "+--------------------------------------+\n" RESET);
        printf(CYAN "|      " BOLD YELLOW "DANH SACH CONG THUC" RESET CYAN "             |\n" RESET);
        printf(CYAN "+--------------------------------------+\n" RESET);

    Formula *temp = List;
    int stt = 1;

    while (temp) {
        printf(CYAN "| " GREEN "%-3d." BOLD WHITE " %-30s" RESET CYAN " |\n" RESET, stt++, temp->ten);
        printf(CYAN "|    " YELLOW "CT: " RESET "%-32s" CYAN " |\n" RESET, temp->congthuc);

    if (temp->next)
        printf(CYAN "+--------------------------------------+\n" RESET);

        temp = temp->next;
    }

    printf(CYAN "+--------------------------------------+\n" RESET);

    char ten[100];
    FlushStdin();
    printf("\n  Nhap ten cong thuc can xoa: ");
    if (fgets(ten, sizeof(ten), stdin) == NULL) { FreeList(List); return; }
    ten[strcspn(ten, "\n")] = '\0';
    ChuanHoaTen(ten);

    if (ten[0] == '\0') {
        printf(RED "  [LOI] Ten khong duoc de trong!\n" RESET);
        FreeList(List);
        return;
    }

    int found = XoaNode(&List, ten); 
    

    if (!found) {
        printf(RED "  [LOI] Khong tim thay cong thuc '%s'!\n" RESET, ten);
    } else {
        FILE *fout = fopen(nameFile, "w");
        if (fout == NULL) {
            printf(RED "  [LOI] Khong the ghi file!\n" RESET);
        } else {
            temp = List;
            while (temp != NULL) {
                fprintf(fout, "%s | %s\n", temp->ten, temp->congthuc);
                temp = temp->next;
            }
            fclose(fout);
            printf(GREEN "  => Da xoa va cap nhat file thanh cong!\n" RESET);
        }
    }

    FreeList(List); 
    printf("\n  Nhan enter de tiep tuc ...");
    _getch();
}

/* ============================================================
 *  SUA CONG THUC
 * ============================================================ */
void SuaCongThuc(char *nameFile, char *tenMon) {
    if (nameFile == NULL) return;

    Formula *List = NULL;
    LoadFile(&List, nameFile);
    system("cls");

    if (List == NULL) {
        printf(RED "  [LOI] Khong co du lieu trong file: %s\n" RESET, nameFile);
        return;
    }

    printf("\nBan da chon: " GREEN "SUA CONG THUC" RESET " - Mon: " YELLOW "%s\n" RESET, tenMon);

    int stt = 1;
    Formula *temp = List;
    while (temp) {
        printf(CYAN "| " GREEN "%-3d." BOLD WHITE " %-30s" RESET CYAN " |\n" RESET, stt++, temp->ten);
        printf(CYAN "|    " YELLOW "CT: " RESET "%-32s" CYAN " |\n" RESET, temp->congthuc);

    if (temp->next)
        printf(CYAN "+--------------------------------------+\n" RESET);

        temp = temp->next;
    }
  
    Formula *current = List;

    char tenTimKiem[100];
    printf("\n  Nhap ten cong thuc can sua: ");
    FlushStdin();
    if (fgets(tenTimKiem, sizeof(tenTimKiem), stdin) == NULL) {
        FreeList(List);
        return;
    }
    
    tenTimKiem[strcspn(tenTimKiem, "\n")] = '\0';

    if (strlen(tenTimKiem) == 0) {
        printf(RED "  [LOI] Ten khong duoc de trong!\n" RESET);
        FreeList(List);
        return;
    }
    ChuanHoaTen(tenTimKiem);

    int found = 0;
    current = List; 
    while (current != NULL) {
        if (strcmp(current->ten, tenTimKiem) == 0) {
            found = 1;
            printf(GREEN "  Tim thay: %s | %s\n" RESET, current->ten, current->congthuc);
            printf("  Nhap cong thuc moi (Bo trong de giu nguyen): ");

            char congThucMoi[100];
            if (fgets(congThucMoi, sizeof(congThucMoi), stdin)) {
                congThucMoi[strcspn(congThucMoi, "\n")] = '\0';
                if (strlen(congThucMoi) > 0) {
                    strcpy(current->congthuc, congThucMoi);
                    printf(YELLOW "  => Da cap nhat thanh cong!\n" RESET);
                } else {
                    printf("  => Giu nguyen cong thuc cu.\n");
                }
            }
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf(RED "  [LOI] Khong tim thay cong thuc '%s'!\n" RESET, tenTimKiem);
    } else {
        FILE *fout = fopen(nameFile, "w");
        if (fout == NULL) {
            printf(RED "  Loi: Khong the ghi file!\n" RESET);
        } else {
            current = List;
            while (current != NULL) {
                fprintf(fout, "%s | %s\n", current->ten, current->congthuc);
                current = current->next;
            }
            fclose(fout);
        }
    }

    FreeList(List);
    printf("\n  Nhan enter de tiep tuc ...");
    _getch(); 
}

/* ============================================================
 *  MENU ADMIN
 * ============================================================ */
void Admin() {
    int choice = 0;
    char fileMocHoc[100];
    system("cls");
    do {
        printAdminMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 0) break;
        system("cls");
        int mon = Choice();
        char tenMon[50];
        getFilePath(mon, fileMocHoc, tenMon);
        if (mon == 0) { printf("  Quay lai menu Admin.\n"); continue; }
        if (fileMocHoc[0] == '\0') { printf("  Mon hoc khong hop le!\n"); continue; }

        switch (choice) {
            case 1: 
                ThemCongThuc(fileMocHoc, tenMon);             break;
            case 2: XoaCongThuc(fileMocHoc, tenMon);          break;
            case 3: SuaCongThuc(fileMocHoc, tenMon);          break;
            case 4: TimCongThucTheoTen(fileMocHoc, tenMon);   break;
            case 5: XuatDanhSachCongThuc(fileMocHoc); break;
            default: printf("  Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}