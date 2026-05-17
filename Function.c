#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Function.h"

#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define WHITE   "\033[97m"

/* ============================================================
 *  HAM TIEN ICH - LINKED LIST
 * ============================================================ */

Formula *CreateNode(char *ten, char *congthuc) {
    Formula *newNode = (Formula *)malloc(sizeof(Formula));
    if (newNode == NULL) {
        printf("  Loi: Khong du bo nho!\n");
        return NULL;
    }
    strcpy(newNode->ten, ten);
    strcpy(newNode->congthuc, congthuc);
    newNode->next = NULL;
    return newNode;
}

void ThemNode(Formula **head, char *ten, char *congthuc) {
    Formula *newNode = CreateNode(ten, congthuc);
    if (newNode == NULL) return;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Formula *temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

int XoaNode(Formula **head, char *ten) {
    Formula *current = *head;
    Formula *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->ten, ten) == 0) {
            if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;
            free(current);
            return 1; 
        }
        prev = current;
        current = current->next;
    }
    printf("  Khong tim thay cong thuc '%s' de xoa.\n", ten);
    return 0; 
}


void FreeList(Formula *head) {
    Formula *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ============================================================
 *  HAM TIEN ICH - CHUAN HOA CHUOI
 * ============================================================ */

void ChuanHoaTen(char *name) {
    if (name == NULL || name[0] == '\0') return;

    char copy[100];
    strncpy(copy, name, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';

    char temp[200] = "";
    char *token = strtok(copy, " ");
    int isFirstToken = 1;

    while (token != NULL) {
        char word[50];
        strncpy(word, token, sizeof(word) - 1);
        word[sizeof(word) - 1] = '\0';

        // Duyệt từng ký tự trong từ
        for (int i = 0; word[i]; i++) {
            if (isFirstToken && i == 0) {
                word[i] = toupper((unsigned char)word[i]); 
            } else {
                word[i] = tolower((unsigned char)word[i]); 
            }
        }

        
        if (!isFirstToken) strcat(temp, " "); 
        strcat(temp, word);

        isFirstToken = 0;
        token = strtok(NULL, " ");
    }

    strncpy(name, temp, 99);
    name[99] = '\0';
}

void FlushStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
 *  MENU CHON MON HOC
 * ============================================================ */

static void printChoiceMenu() {
    printf("\n");
    
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " BOLD YELLOW "📚  DANH SACH MON HOC            " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " GREEN "1." WHITE "  Giai tich                     " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "2." WHITE "  Vat ly                        " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "3." WHITE "  Xac suat thong ke             " RESET CYAN "|\n" RESET);
    printf(CYAN "|   " GREEN "4." WHITE "  Kinh te chinh tri             " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "|   " DIM "0.  Quay lai                      " RESET CYAN "|\n" RESET);
    printf(CYAN "+--------------------------------------+\n" RESET);
    printf(CYAN "\n➤  " RESET BOLD "Chon mon hoc (0-4): " RESET);
}

int Choice() {
    int luaChon, trangThai;
    do {
        printChoiceMenu();
        trangThai = scanf("%d", &luaChon);
        if (trangThai != 1) {
            printf(YELLOW "  [LOI] Dau vao khong hop le!\n" RESET);
            FlushStdin();
            luaChon = -1;
        } else if (luaChon < 0 || luaChon > 4) {
            printf(YELLOW "  [LOI] Vui long chon tu 0 den 4!\n" RESET);
        }
    } while (luaChon < 0 || luaChon > 4);
    return luaChon;
}

/* ============================================================
 *  HAM FILE I/O
 * ============================================================ */

void LoadFile(Formula **head, char *nameFile) {
    FILE *fin = fopen(nameFile, "r");
    if (fin == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fin)) {
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, "|");
        if (token == NULL) continue;
        char ten[100];
        strncpy(ten, token, sizeof(ten) - 1);
        ten[sizeof(ten) - 1] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL) continue;

        while (*token == ' ') token++;
        char congthuc[100];
        strncpy(congthuc, token, sizeof(congthuc) - 1);
        congthuc[sizeof(congthuc) - 1] = '\0';

        int tlen = (int)strlen(ten);
        while (tlen > 0 && ten[tlen - 1] == ' ') ten[--tlen] = '\0';

        ThemNode(head, ten, congthuc);
    }
    fclose(fin);
}

/* ============================================================
 *  GHI 1 CONG THUC RA FILE TXT
 * ============================================================ */
void DisplayOutput(Formula CongThuc, char *nameFile) {
    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
        return;
    }

    char content[210];
    snprintf(content, sizeof(content), "%s | %s", CongThuc.ten, CongThuc.congthuc);
    int len  = (int)strlen(content);
    int cols = (len + 4 > 38) ? len + 4 : 38;

    fprintf(fout, "  +");
    for (int j = 0; j < cols; j++) fprintf(fout, "-");
    fprintf(fout, "+\n");

    fprintf(fout, "  | %-*s |\n", cols - 2, content);

    fprintf(fout, "  +");
    for (int j = 0; j < cols; j++) fprintf(fout, "-");
    fprintf(fout, "+\n\n");

    fclose(fout);
}

/* ============================================================
 *  GHI TOAN BO DANH SACH CONG THUC RA FILE TXT
 * ============================================================ */
 void DisplayOutputList(Formula *List, char *nameFile) {
    FILE *fout = fopen(nameFile, "w");
    if (fout == NULL) {
        printf("  Loi: Khong the ghi file: %s\n", nameFile);
        return;
    }

    fprintf(fout, "  +-----+--------------------------------+-------------------------------------------------------------+\n");
    fprintf(fout, "  | %-3s | %-30s | %-19s |\n", "STT", "Ten cong thuc", "Cong thuc");
    fprintf(fout, "  +-----+--------------------------------+-------------------------------------------------------------+\n");

    Formula *current = List;
    int total = 0;
    while (current != NULL) {
        fprintf(fout, "  | %-3d | %-30s | %-19s |\n",
                total++, current->ten, current->congthuc);
        current = current->next;
    }

    fprintf(fout, "  +-----+--------------------------------+--------------------------------------------------------------+\n");
    fprintf(fout, "  | Tong so: %-3d cong thuc                                                                             |\n", total);
    fprintf(fout, "  +-----+--------------------------------+--------------------------------------------------------------+\n");

    fclose(fout);
    printf("  Da xuat %d cong thuc ra file '%s'.\n", total, nameFile);
}

/* ============================================================
 *  XUAT DANH SACH CONG THUC RA MAN HINH + FILE TXT
 * ============================================================ */
void XuatDanhSachCongThuc(char *nameFile) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu trong file: %s\n", nameFile);
        return;
    }
    DisplayOutputList(List, "DisplayData.txt");
    printf("\n  [OK] Da luu ban in vao 'DisplayData.txt'\n");
    
    FreeList(List);
}
/* ============================================================
 *  TIM KIEM CONG THUC THEO TEN
 * ============================================================ */

void TimCongThucTheoTen(char *nameFile,char *tenMon) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu de tim kiem!\n");
        return;
    }
    FlushStdin();
    char tenTim[100];
    system("cls");
    printf("\nBan da chon: " GREEN "TIM KIEM CONG THUC THEO TEN" RESET " - Mon: " YELLOW "%s\n" RESET, tenMon);
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
        printf( RED " [LOI] Khong tim thay cong thuc nao voi tu khoa: '%s'\n", tenTim);
    else
        printf( GREEN " [THANH CONG] Tim thay %d ket qua. Da luu vao 'DisplayData.txt'.\n", found);
        printf("\n  Nhan enter de tiep tuc ..."); 
        _getch();
}