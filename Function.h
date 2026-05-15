#ifndef FUNCTION_H
#define FUNCTION_H

/* ============================================================
 *  CAU TRUC DU LIEU
 * ============================================================ */
typedef struct Formula {
    char ten[100];
    char congthuc[100];
    Formula *next;
}Formula;

extern Formula* GT2;
extern Formula* XS;
extern Formula* VL;
extern Formula* CNXH;

// khai bao cac ham
int Choice();
Formula *CreateNode(char *ten, char *congthuc);
void     ThemNode(Formula **head, char *ten, char *congthuc);
void     XoaNode(Formula **head, char *ten);
void     FreeList(Formula *head);

/* ============================================================
 *  HAM TIEN ICH - CHUAN HOA CHUOI
 * ============================================================ */
void ChuanHoa(char *name);
void ChuanHoaTen(char *name);

/* ============================================================
 *  HAM TIEN ICH - VE KHUNG & MENU
 * ============================================================ */
void drawBox(int rows, int cols, char *text);
int  Choice(void);

/* ============================================================
 *  HAM FILE I/O (DUNG CHUNG CHO ADMIN VA USER)
 * ============================================================ */
void LoadFile(Formula **head, char *nameFile);
void DisplayOutput(Formula CongThuc, char *nameFile);
void TimCongThucTheoTen(char *nameFile);
void XuatCongThuc(Formula CongThuc, char *nameFile);
void ThemCongThuc(char *nameFile);
void XoaCongThuc(char *ten, char *nameFile);
void XuatDanhSachCongThuc(char *nameFile);

#endif /* FUNCTION_H */