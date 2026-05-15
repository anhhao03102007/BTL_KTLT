#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Function.h"

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

void XoaNode(Formula **head, char *ten) {
    Formula *current = *head;
    Formula *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->ten, ten) == 0) {
            if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("  Khong tim thay cong thuc '%s' de xoa.\n", ten);
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

/* Viet hoa ky tu dau, chu thuong phan con lai cua mot tu */
void ChuanHoa(char *name) {
    if (name == NULL || name[0] == '\0') return;
    for (int i = 0; name[i]; i++) {
        name[i] = (i == 0) ? toupper((unsigned char)name[i])
                           : tolower((unsigned char)name[i]);
    }
}

/* Chuan hoa tung tu trong chuoi (Title Case)
 * BUG FIX: khoi tao temp[] = "" tranh garbage data */
void ChuanHoaTen(char *name) {
    if (name == NULL || name[0] == '\0') return;

    char copy[100];
    strncpy(copy, name, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';

    char temp[200] = "";   /* FIX: khoi tao de strcat hoat dong dung */

    char *token = strtok(copy, " ");
    while (token != NULL) {
        ChuanHoa(token);
        strncat(temp, token, sizeof(temp) - strlen(temp) - 2);
        strncat(temp, " ",   sizeof(temp) - strlen(temp) - 1);
        token = strtok(NULL, " ");
    }

    /* Xoa khoang trang thua o cuoi */
    int len = (int)strlen(temp);
    if (len > 0 && temp[len - 1] == ' ')
        temp[len - 1] = '\0';

    strncpy(name, temp, 99);
    name[99] = '\0';
}

/* ============================================================
 *  HAM TIEN ICH - VE KHUNG & MENU
 * ============================================================ */

void drawBox(int rows, int cols, char *text) {
    int textLen = (int)strlen(text);
    if (cols < textLen + 4) cols = textLen + 4;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if ((i == 1 || i == rows) && (j == 1 || j == cols))
                printf("+");
            else if (i == 1 || i == rows)
                printf("-");
            else if (j == 1 || j == cols)
                printf("|");
            else if (i == rows / 2) {
                int startCol = (cols / 2) - (textLen / 2);
                if (startCol < 2)                    startCol = 2;
                if (startCol > cols - textLen - 1)   startCol = cols - textLen - 1;
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

/* Xoa newline thua sau scanf */
static void FlushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Choice(void) {
    int choice = 0;
    drawBox(5, 36, "Chon Mon Hoc");
    printf("  1. Giai tich 2\n");
    printf("  2. Xac suat thong ke\n");
    printf("  3. Chu nghia khoa hoc xa hoi\n");
    printf("  4. Vat li\n");
    printf("  0. Thoat\n");
    printf("  Selection > ");

    if (scanf("%d", &choice) != 1) {
        FlushStdin();
        return -1;
    }
    FlushStdin();
    return choice;
}

/* ============================================================
 *  HAM FILE I/O
 * ============================================================ */

/* Doc danh sach cong thuc tu file vao linked list
 * BUG FIX: bo dong tao newFormula thua (memory leak) */
void LoadFile(Formula **head, char *nameFile) {
    FILE *fin = fopen(nameFile, "r");
    if (fin == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fin)) {
        /* Xoa newline cuoi dong */
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, "|");
        if (token == NULL) continue;
        char ten[100];
        strncpy(ten, token, sizeof(ten) - 1);
        ten[sizeof(ten) - 1] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL) continue;

        /* Bo khoang trang dau congthuc (do dinh dang "ten | ct") */
        while (*token == ' ') token++;
        char congthuc[100];
        strncpy(congthuc, token, sizeof(congthuc) - 1);
        congthuc[sizeof(congthuc) - 1] = '\0';

        /* Xoa khoang trang cuoi ten */
        int tlen = (int)strlen(ten);
        while (tlen > 0 && ten[tlen - 1] == ' ') ten[--tlen] = '\0';

        ThemNode(head, ten, congthuc);  /* FIX: goi thang ThemNode, khong tao node thua */
    }
    fclose(fin);
}

/* Ghi mot cong thuc ra file dang khung ASCII */
void DisplayOutput(Formula CongThuc, char *nameFile) {
    FILE *fout = fopen(nameFile, "a");
    if (fout == NULL) {
        printf("  Khong the mo file: %s\n", nameFile);
        return;
    }

    char content[210];
    snprintf(content, sizeof(content), "%s | %s", CongThuc.ten, CongThuc.congthuc);
    int len  = (int)strlen(content);
    int rows = 5;
    int cols = (len + 4 > 30) ? len + 4 : 30;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0 || i == rows - 1) && (j == 0 || j == cols - 1))
                fprintf(fout, "+");
            else if (i == 0 || i == rows - 1)
                fprintf(fout, "-");
            else if (j == 0 || j == cols - 1)
                fprintf(fout, "|");
            else if (i == rows / 2) {
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
}

/* Xuat toan bo danh sach cong thuc ra man hinh */
void XuatDanhSachCongThuc(char *nameFile) {
    Formula *List = NULL;
    LoadFile(&List, nameFile);

    if (List == NULL) {
        printf("  Khong co du lieu trong file: %s\n", nameFile);
        return;
    }

    printf("\n  === DANH SACH CONG THUC ===\n");
    Formula *current = List;
    int stt = 1;
    while (current != NULL) {
        printf("  %d. %-30s | %s\n", stt++, current->ten, current->congthuc);
        current = current->next;
    }
    printf("  Tong so: %d cong thuc.\n", stt - 1);

    FreeList(List);
}