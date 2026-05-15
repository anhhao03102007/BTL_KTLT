#ifndef ADMIN_H
#define ADMIN_H

/* ============================================================
 *  CRUD - QUAN LY CONG THUC (CHI ADMIN MOI DUNG)
 * ============================================================ */
void ThemCongThuc(char *nameFile);
void XoaCongThuc(char *nameFile);
void SuaCongThuc(char *nameFile);
void TimCongThucTheoTen(char *nameFile);

/* Ham dieu phoi chinh cua Admin */
void Admin(void);

#endif /* ADMIN_H */