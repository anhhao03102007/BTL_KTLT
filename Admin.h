#ifndef ADMIN_H
#define ADMIN_H

/* ============================================================
 *  CRUD - QUAN LY CONG THUC (CHI ADMIN MOI DUNG)
 * ============================================================ */
void ChuanHoaTen(char *ten);
void ThemCongThuc(char *nameFile,char *tenMon);
void XoaCongThuc(char *nameFile,char *tenMon);
void SuaCongThuc(char *nameFile,char *tenMon);
void TimCongThucTheoTen(char *nameFile,char *tenMon);

void Admin();

#endif /* ADMIN_H */