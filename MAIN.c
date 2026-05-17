#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define MAGENTA "\033[35m"
#define BG_BLUE "\033[44m"

void loadingAnimation() {
    system("cls");

    printf(CYAN "=============================================================\n" RESET);
    printf(CYAN "|" BOLD YELLOW "   CHUONG TRINH QUAN LY CONG THUC - BAI TAP LON KTLT   " RESET CYAN "|\n" RESET);
    printf(CYAN "=============================================================\n" RESET);
    Sleep(800);

    printf(WHITE "\n  Dang khoi dong he thong");
    for (int i = 0; i < 3; i++) {
        Sleep(400);
        printf(YELLOW "." RESET);
    }
    printf("\n\n" RESET);
    Sleep(300);

    // Thanh loading với màu động
    int totalSteps = 20;
    printf("  " CYAN "Loading: [" RESET);

    for (int i = 0; i < totalSteps; i++) {
        Sleep(100);

        // Đổi màu theo tiến trình
        if (i < 7)
            printf(RED "#" RESET);        
        else if (i < 14)
            printf(YELLOW "#" RESET);     
        else
            printf(GREEN "#" RESET);      

        printf(WHITE "\b\b\b\b\b] %3d%%", (i + 1) * 5);
        printf("\033[%dD", (i + 2));      
    }

    printf(CYAN "] " GREEN BOLD "100%%" RESET "\n\n");
    Sleep(300);

    printf(CYAN "  =============================================================\n" RESET);
    printf(GREEN BOLD "                     >> Completed ! <<\n" RESET);
    printf(CYAN "  =============================================================\n\n" RESET);

    printf(YELLOW "  Nhan " BOLD "[Enter]" RESET YELLOW " de tiep tuc..." RESET);
    _getch();
    system("cls");
}

int main() {
    int choice;
    system("cls");
    loadingAnimation();
    do {
        hienThiMenuChinh();
        printf("\nVui long nhap lua chon cua ban (0-2): ");
        scanf("%d", &choice);
        xoaBoDemDauVao();

        switch (choice) {
            case 1:
                if (dangNhapQuanTriVien()) {
                    Admin();
                } else {
                    printf("\n[THAT BAI] Dang nhap Admin that bai. Vui long thu lai!\n");
                }
                break;
            case 2:
                User();
                break;
            case 0:
                printf("\nCam on ban da su dung chuong trinh. Tam biet!\n");
                break;
            default:
                printf("\n[LOI] Lua chon khong ton tai. Vui long chon tu 0 den 2!\n");
        }
    } while (choice != 0);
    return 0;
}