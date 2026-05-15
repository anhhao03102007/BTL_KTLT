#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"User.h"
#include"Function.h"
void drawBox(int rows, int cols, char* text) {
    int len = (int)strlen(text);
    int padding = (cols - len - 2) / 2; // Tính khoảng cách để căn giữa
    if (padding < 0) padding = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0 || i == rows - 1) && (j == 0 || j == cols - 1)) {
                printf("+");
            } else if (i == 0 || i == rows - 1) {
                printf("-");
            } else if (j == 0 || j == cols - 1) {
                printf("|");
            } else if (i == rows / 2 && j >= padding + 1 && j < padding + len + 1) {
                printf("%c", text[j - padding - 1]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }}
  void User() {
    int choice = 0;
    do {
        printf("\n");
        drawBox(5, 30, "User Menu");
        printf("1. Xem tat ca cong thuc \n");
        printf("2. Tim cong thuc theo mon hoc\n");
        printf("0. Quay lai\n");
        printf("Selection > ");
        scanf("%d", &choice); 
          
       
        while (getchar() != '\n'); // Xóa bộ đệm sau khi nhập choice

        switch(choice) {
            case 1: {
                int Chon = Choice();
                if (Chon < 1 || Chon > 4) {
                    printf("Lua chon mon hoc khong hop le!\n");
                } else {
                    switch(Chon) {
                        case 1:
                            XuatDanhSachCongThuc("data/Calculus_2.txt");
                            break;
                        case 2:
                            XuatDanhSachCongThuc("data/Probability_Statistics.txt");
                            break;
                        case 3:
                            XuatDanhSachCongThuc("data/Political_Economy.txt");
                            break;
                        case 4:
                            XuatDanhSachCongThuc("data/Physic.txt");
                            break;
                    }
                }
                break;
            }
            case 2: {
                int Chon;
                // Bỏ do...while(1) nếu bạn muốn tìm xong 1 môn rồi quay về User Menu luôn
                Chon = Choice(); 
                
                if (Chon < 1 || Chon > 4) {
                    printf("Lua chon mon hoc khong hop le!\n");
                } else {
                    switch(Chon) {
                        case 1: 
                            TimCongThucTheoTen("data/Calculus_2.txt");
                            break;
                        case 2: 
                            TimCongThucTheoTen("data/Probability_Statistics.txt");
                            break;
                        case 3: 
                            TimCongThucTheoTen("data/Political_Economy.txt");
                            break;
                        case 4: 
                            TimCongThucTheoTen("data/Physic.txt");
                            break;
                    }
                }
                break; // Thoát case 2, quay về User Menu
            }
            case 0:
                printf("Dang quay lai...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(choice != 0);
}
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
}void DisplayOutput(Formula CongThuc, char *nameFile) {
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