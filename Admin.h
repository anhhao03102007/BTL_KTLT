#ifndef ADMIN_H
#define ADMIN_H

/* ============================================================
 *  CRUD - QUAN LY CONG THUC (CHI ADMIN MOI DUNG)
 * ============================================================ */
void ChuanHoaTen(char *ten);
void ThemCongThuc(char *nameFile);
void XoaCongThuc(char *nameFile);
void SuaCongThuc(char *nameFile);
void TimCongThucTheoTen(char *nameFile);

void Admin();

#endif /* ADMIN_H */