#include<stdio.h>
#include<stdlib.h>
#include"User.h"
#include"Function.h"

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
            case 1:
                printf("Tinh nang xem tat ca cong thuc dang phat trien...\n");
                break;
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