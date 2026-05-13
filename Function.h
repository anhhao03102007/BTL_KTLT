#ifndef FUNCTION_H
#define FUNCTION_H
// khai bao cau truc cong thuc
typedef struct Formula
{
    char ten[100];
    char congthuc[100];
    Formula *next;
}Formula;

extern Formula* GT2;
extern Formula* XS;
extern Formula* VL;
extern Formula* CHXH;

// khai bao cac ham
int Choice();
Formula *CreateNode(char *ten, char *congthuc);
void ThemNode(Formula **head, char *ten, char *congthuc);
void XoaNode(Formula **head, char *ten);
void FreeList();
void ChuanHoa(char *name);
void ChuanHoaTen(char *name);
void SuaCongThuc(char *nameFile);
void LoadFile(Formula **List, char *nameFile);
void DisplayOutput(Formula CongThuc, char *nameFile);
void TimCongThucTheoTen( char *nameFile);
void XuatCongThuc(Formula CongThuc,char *nameFile);
void ThemCongThuc(char *nameFile);
void XoaCongThuc(char *nameFile);
void XuatDanhSachCongThuc(char *nameFile);
void drawBox(int rows, int cols, char* text);


#endif 