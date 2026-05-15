#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Function.h"

/****************************************************
 *  HÀM TIỆN ÍCH
 ****************************************************/

Formula *CreateNode(char *ten, char *congthuc) {
    Formula *newNode = (Formula *)malloc(sizeof(Formula));
    if (newNode) {
        strcpy(newNode->ten, ten);
        strcpy(newNode->congthuc, congthuc);
        newNode->next = NULL;
    }
    return newNode;
}


void XoaNode(Formula **head, char *ten) {
    Formula *current = *head;
    Formula *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->ten, ten) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

/* Viết hoa ký tự đầu, chữ thường phần còn lại của một từ */
void ChuanHoa(char *name) {
    if (name == NULL || name[0] == '\0') return;
    for (int i = 0; name[i]; i++) {
        name[i] = (i == 0) ? toupper((unsigned char)name[i])
                           : tolower((unsigned char)name[i]);
    }
}

/* Chuẩn hóa từng từ trong chuỗi (Title Case) */
void ChuanHoaTen(char *name) {
    if (name == NULL) return;

    char copy[100];
    strcpy(copy, name);
  
    char temp[200];

    char *token = strtok(copy, " ");
    while (token != NULL) {
        ChuanHoa(token);
        strcat(temp, token);
        strcat(temp, " ");
        token = strtok(NULL, " ");
    }

    /* Xóa khoảng trắng thừa ở cuối */
    if (strlen(temp) > 0) {
        temp[strcspn(temp, " ")] = '\0';
    }

    strcpy(name, temp);
}

void FreeList(Formula *head){
    Formula* temp;
    while ( head ){
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* Đọc stdin an toàn: xóa newline thừa sau scanf */
static void FlushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
 *  VẼ KHUNG
 * ============================================================ */

void drawBox(int rows, int cols, char *text) {
    int textLen = (int)strlen(text);
    /* Đảm bảo text luôn nằm trong khung */
    if (cols < textLen + 4) cols = textLen + 4;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if ((i == 1 || i == rows) && (j == 1 || j == cols)) {
                printf("+");
            } else if (i == 1 || i == rows) {
                printf("-");
            } else if (j == 1 || j == cols) {
                printf("|");
            } else if (i == rows / 2) {
                /* Tính vị trí bắt đầu text, clamp vào [2, cols-textLen-1] */
                int startCol = (cols / 2) - (textLen / 2);
                if (startCol < 2)           startCol = 2;
                if (startCol > cols - textLen - 1) startCol = cols - textLen - 1;

                if (j == startCol) {
                    printf("%s", text);
                    j += textLen - 1;
                } else {
                    printf(" ");
                }
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/* ============================================================
 *  MENU
 * ============================================================ */

int Choice(void) {
    int choice = 0;
    drawBox(5, 34, "Chon Mon Hoc");
    printf("  1. Giai tich 2\n");
    printf("  2. Xac suat thong ke\n");
    printf("  3. Chu nghia khoa hoc xa hoi\n");
    printf("  4. Vat li\n");
    printf("  0. Thoat\n");
    printf("  Selection > ");

    if (scanf("%d", &choice) != 1) {
        FlushStdin();
        return -1;  /* Giá trị lỗi */
    }
    FlushStdin();   /* Xóa '\n' còn trong buffer */
    return choice;
}

/* ============================================================
 *  FILE I/O
 * ============================================================ */

void LoadFile(Formula **head , char *nameFile) {
    FILE *fin = fopen(nameFile, "r");
    if (fin == NULL) {
        printf("Khong the mo file: %s\n", nameFile);
        return;
    }
    char line[200];
    char ten[100], congthuc[100];
    while (fgets(line, sizeof(line), fin)) {
        char *token = strtok(line, "|");
        if (token == NULL) continue;
        strcpy(ten, token);
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(congthuc, token);
        ten[strcspn(ten, "\n")] = '\0';
        congthuc[strcspn(congthuc, "\n")] = '\0';
        ThemNode(head, ten, congthuc);
    }
    fclose(fin);
}

/*
 * Ghi một công thức vào file output dưới dạng khung ASCII.
 * Dùng "a" để có thể ghi nhiều kết quả mà không mất dữ liệu cũ.
 */
void DisplayOutput(Formula CongThuc, char *nameFile) {
    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf("Khong the mo file: %s\n", nameFile);
        return;
    }


    char content[210];
    snprintf(content, sizeof(content), "%s | %s", CongThuc.ten, CongThuc.congthuc);
    int  len  = (int)strlen(content);
    int  rows = 5;
    int  cols = (len + 4 > 30) ? len + 4 : 30;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0 || i == rows - 1) && (j == 0 || j == cols - 1)) {
                fprintf(fout, "+");
            } else if (i == 0 || i == rows - 1) {
                fprintf(fout, "-");
            } else if (j == 0 || j == cols - 1) {
                fprintf(fout, "|");
            } else if (i == rows / 2) {
                int startCol = (cols / 2) - (len / 2);
                if (startCol < 1)              startCol = 1;
                if (startCol > cols - len - 1) startCol = cols - len - 1;

                if (j == startCol) {
                    fprintf(fout, "%s", content);
                    j += len - 1;
                } else {
                    fprintf(fout, " ");
                }
            } else {
                fprintf(fout, " ");
            }
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    fclose(fout);
    printf("  Da luu cong thuc vao file '%s' thanh cong!\n", nameFile);
}

/* ============================================================
 *  THÊM CÔNG THỨC
 * ============================================================ */

void ThemCongThuc(Formula **List , char *nameFile) {
    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf("Khong the mo file: %s\n", nameFile);
        return;
    }

    char ten[100] , congthuc[100];
    printf(" Nhap ten cong thuc : ");
    fgets(ten, sizeof(ten), stdin);
    ten[strcspn(ten, "\n")] = '\0';
    ChuanHoaTen(ten);

    printf(" Nhap cong thuc : ");
    fgets(congthuc, sizeof(congthuc), stdin);
    congthuc[strcspn(congthuc, "\n")] = '\0';

    fprintf(fout, "%s | %s\n", ten,congthuc);
    fclose(fout);

}

/* ============================================================
 *  TÌM CÔNG THỨC THEO TÊN
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
    if (fgets(tenTim, sizeof(tenTim), stdin) == NULL) return;
    tenTim[strcspn(tenTim, "\n")] = '\0';
    ChuanHoaTen(tenTim);

    if (strlen(tenTim) == 0) {
        printf("  Ten cong thuc khong the trong!\n");
        return;
    }

    /* Xóa file output trước khi ghi các kết quả mới */
    FILE *fout = fopen("DisplayData.txt", "w");
    if (fout) fclose(fout);

    int found = 0;
    Formula *current = List;
    while (current != NULL) {
        if (strcmp(current->ten, tenTim) == 0) {
            DisplayOutput(*current, "DisplayData.txt");
            found++;
        }
        current = current->next;
    }
    

    if (!found) {
        printf("  Khong tim thay cong thuc nao voi tu khoa: '%s'\n", tenTim);
    } else {
        printf("  Tim thay %d ket qua. Da luu vao 'DisplayData.txt'.\n", found);
    }
    FreeList(List);
}

void XuatCongThuc(Formula CongThuc, char *nameFile) {
    (void)nameFile;
    printf("  %-30s | %s\n", CongThuc.ten, CongThuc.congthuc);
}

void XuatDanhSachCongThuc(char *nameFile) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);
    if (List == NULL) {
        printf("  Khong the doc du lieu tu file: %s\n", nameFile);
        return;
    }

    printf("\nDanh sach cong thuc trong file '%s':\n", nameFile);
    Formula *current = List;
    while (current != NULL) {
        XuatCongThuc(*current, nameFile);
        current = current->next;
    }
    FreeList(List);
    printf("\n");
}

/* ============================================================
 *  XÓA CÔNG THỨC
 * ============================================================ */

void XoaCongThuc(char *ten, char *nameFile) {
    if (ten == NULL || nameFile == NULL) return;

    if (ten[0] == '\0') {
        printf("  Ten cong thuc khong the trong!\n");
        return;
    }

    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu de xoa!\n");
        return;
    }

    ChuanHoaTen(ten);
    XoaNode(&List, ten);

    FILE *fout = fopen(nameFile, "w");
    if (fout == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
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
 *  SỬA CÔNG THỨC
 * ============================================================ */

void SuaCongThuc(char *nameFile) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL || nameFile == NULL) return;
   
    char tenTimKiem[100];
    FlushStdin();
    printf("  Nhap ten cong thuc can sua: ");
    fgets(tenTimKiem, sizeof(tenTimKiem), stdin);
    tenTimKiem[strcspn(tenTimKiem, "\n")] = '\0';
    ChuanHoaTen(tenTimKiem);
    Formula *current = List;
    while (current != NULL) {
        if (strcmp(current->ten, tenTimKiem) == 0) {
            printf("  Tim thay cong thuc: %s | %s\n", current->ten, current->congthuc);
            printf("  Nhap cong thuc moi: ");
            char congThucMoi[100];
            fgets(congThucMoi, sizeof(congThucMoi), stdin);
            congThucMoi[strcspn(congThucMoi, "\n")] = '\0';

            if (strlen(congThucMoi) > 0) {
                strcpy(current->congthuc, congThucMoi);
                printf("  Da cap nhat cong thuc moi: %s | %s\n", current->ten, current->congthuc);
            } else {
                printf("  Cong thuc khong duoc de trong. Giữ nguyên cong thuc cu.\n");
            }
            break;
        }
    }

    FILE *fin = fopen(nameFile, "w");
    if (fin == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
        return;
    }
    Formula *temp = List;
    while (temp != NULL) {
        fprintf(fin, "%s|%s\n", temp->ten, temp->congthuc);
        temp = temp->next;
    }

    fclose(fin);
}
