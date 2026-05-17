#ifndef FUNCTION_H
#define FUNCTION_H

/* ============================================================
 *  CAU TRUC DU LIEU
 * ============================================================ */
typedef struct Formula {
    char ten[100];
    char congthuc[100];
    struct Formula *next;
} Formula;

/* ============================================================
 *  HAM TIEN ICH - LINKED LIST
 * ============================================================ */
Formula *CreateNode(char *ten, char *congthuc);
void ThemNode(Formula **head, char *ten, char *congthuc);
int XoaNode(Formula **head, char *ten);
void FreeList(Formula *head);

/* ============================================================
 *  HAM TIEN ICH - CHUAN HOA CHUOI
 * ============================================================ */
void ChuanHoaTen(char *name);

/* ============================================================
 *  HAM TIEN ICH - VE KHUNG & MENU
 * ============================================================ */
int  Choice(void);

/* ============================================================
 *  HAM FILE I/O (DUNG CHUNG CHO ADMIN VA USER)
 * ============================================================ */
 void FlushStdin();
void LoadFile(Formula **head, char *nameFile);
void DisplayOutputList(Formula *List, char *nameFile);
void DisplayOutput(Formula CongThuc, char *nameFile);
void XuatDanhSachCongThuc(char *nameFile);
void TimCongThucTheoTen(char *nameFile);

#endif 