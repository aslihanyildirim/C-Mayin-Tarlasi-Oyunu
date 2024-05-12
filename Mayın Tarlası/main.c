#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

char cerceve[MAX_SIZE][MAX_SIZE];
int i, j, n, x, y;


void mayinKoy() {
    int mayinSayisi = (n * n) * 0.05;
    srand(time(NULL)); 

    for ( i = 0; i < mayinSayisi; ++i) {
        int randomX, randomY;

        do {
            randomX = rand() % n;
            randomY = rand() % n;
        } while (
            (randomX == 0 && randomY == 0) || 
            (randomX == n - 1 && randomY == n - 1) || 
            (randomX == 0 && randomY <= 2) || 
            (randomX <= 2 && randomY == 0) || 
            (randomX == n - 1 && randomY >= n - 3) || 
            (randomX >= n - 3 && randomY == n - 1) || 
            (randomX == 1 && (randomY == 0 || randomY == 1)) || 
            (randomY == 1 && (randomX == 0 || randomX == 1)) || 
            (randomX == n - 2 && (randomY == n - 1 || randomY == n - 2)) || 
            (randomY == n - 2 && (randomX == n - 1 || randomX == n - 2)) 
        );

        if (cerceve[randomX][randomY] != 'G' && cerceve[randomX][randomY] != 'C') {
            cerceve[randomX][randomY] = 'o';
        } else {
            --i; 
        }

    }
    tehlikeliBolgeler(); 
}

void haritayiGoster() {
    printf("Mayinlar ve Tehlikeli Bolgeler:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (cerceve[i][j] == 'o' || cerceve[i][j] == 'x') {
                printf("(%d, %d) - %c\n", i, j, cerceve[i][j]);
            }
        }
    }
    printf("\nOyuna geri donebilirsiniz ama lutfen hile yapmayin!! <3\n");
}

void tehlike() { 
    x = 0;
    y = 0;
    cerceve[x][y] = 'c';
	for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if (cerceve[i][j] == '*') {
                cerceve[i][j] = '#'; 
            }
        }
    }
}


void tehlikeliBolgeler() {
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if (cerceve[i][j] == 'o') {
                if (i - 1 >= 0 && cerceve[i - 1][j] != 'o') {
                    cerceve[i - 1][j] = 'x'; 
                }
                if (i + 1 < n && cerceve[i + 1][j] != 'o') {
                    cerceve[i + 1][j] = 'x'; 
                }
                if (j - 1 >= 0 && cerceve[i][j - 1] != 'o') {
                    cerceve[i][j - 1] = 'x'; 
                }
                if (j + 1 < n && cerceve[i][j + 1] != 'o') {
                    cerceve[i][j + 1] = 'x'; 
                }
            }
        }
    }
}


void restart() { 
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            cerceve[i][j] = '#'; 
		 }
    }
    x = 0;
    y = 0;
    cerceve[x][y] = 'c'; 
    mayinKoy(); 
}

void karakter() {
	system("cls");
    char gizliHarita[MAX_SIZE][MAX_SIZE];
    haritaKopyala(gizliHarita, cerceve, n);

    int girisX = 0, girisY = 0, cikisX = n - 1, cikisY = n - 1;
    gizliHarita[x][y] = '*';

    printf("( Harita uzerindeki G: Giris / C: Cikis )\n\n");

    int yolGorundu = 0; 

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (i == x && j == y) {
                printf("c");
            } else if (i == 0 && j == 0) {
                printf("G");
            } else if (i == n - 1 && j == n - 1) {
                printf("C");
                if (yolGorundu == 1) {
                    printf("*");
                }
            } else if (cerceve[i][j] == 'x' && i == x && j == y) {
                tehlike();
                return; 
            } else {
                printf("%c", gizliHarita[i][j]);
                if (gizliHarita[i][j] == '*') {
                    yolGorundu = 1;
                }
            }
        }
        printf("\n");
    }
    char harita[MAX_SIZE][MAX_SIZE];
    int karakterX = 0; 
    int karakterY = 0; 

    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            harita[i][j] = '#';
        }
    }
    harita[karakterX][karakterY] = 'G';
    harita[n - 1][n - 1] = 'C'; 

}

void temizle(char harita[MAX_SIZE][MAX_SIZE], int n) {
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if (harita[i][j] == '*') {
                harita[i][j] = '#'; 
            }
        }
    }
}

void karakterYoluIsaretle(char harita[MAX_SIZE][MAX_SIZE], int n, int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        if (harita[x][y] != 'C') {
            harita[x][y] = '*'; 
        }
    }
}


void haritaKopyala(char hedef[MAX_SIZE][MAX_SIZE], char kaynak[MAX_SIZE][MAX_SIZE], int n) {
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if (kaynak[i][j] == 'G' || kaynak[i][j] == 'C' || kaynak[i][j] == 'c') {
                hedef[i][j] = kaynak[i][j];
            } else {
                hedef[i][j] = '#';
            }
        }
    }
}
	

	
void kurallar() {
	printf("\n###############\n");
	printf("-> 'W', 'A', 'S' ve 'D' tuslarini kullanarak istediginiz yere gidebilirsiniz.\n");
	printf("-> [X]e basarak oynadiginiz oyundaki mayinlarin yerlerini gorebilirsiniz.\n");
	printf("-> Mayinlarin konumunu gordukten sonra oyuna tekrar donebilirsiniz.\n");
	printf("-> Oyundan cikmak isterseniz [Q]ya, mayinlari tekrardan konumlandirmak isterseniz [R]ye basmaniz yeterlidir.\n");
	printf("-> 'o' mayindir ve eger gorduyseniz coktan patlamistir, oyun biter.\n");
	printf("-> Mayinlarin etrafi tehlikeli bolgelerle (x) doludur, eger eger tehlikeli bolgeye basarsaniz oyunun basina donersiniz. \n");
	printf("Oyun sizi hicbir sekilde uyarmaz. gittiginiz yollari aklinizda tutmak zorundasiniz.\n");
	printf("-> Mayin tarlasi sizin seciminize gore boyutlanir. Belirtilen boyutlar arasinda deger giriniz.\n");
	printf("-> Oyun sonunda gittiginiz yolu, mayinlari ve tehlikeli bolgeleri gorebilirsiniz.\n");
	printf("!!Lutfen hile yapmayiniz!!");
	printf("IYI OYUNLAR!!\n");
	printf(" <3 / <3 / <3 / <3 / <3 / <3 / <3 ");
	printf("\n###############\n");
}
	
	void secenekler() {
	printf("		-----------------------------------\n");
	printf("		    	   MAYIN TARLASI\n");
	printf("		-----------------------------------\n");
	printf("		1->Yeni Oyun\n");
	printf("		-----------------------------------\n");
	printf("		2->Nasil Oynanir?\n");
	printf("		-----------------------------------\n");
	printf("		3->Tesekkurler!\n");
	printf("		-----------------------------------\n");
	printf("		4->Cikis :( \n");
	printf("		-----------------------------------\n");
	}
	
	
int main() 
{
	int secim, geri;
	tehlikeliBolgeler();
	secenekler();
	printf("Secim yapiniz: ");
	scanf("%d", &secim);
	
	if(secim==1)
	{
	system("cls");
    printf("(Gireceginiz deger 7'den buyuk, 23'ten kucuk olmalidir.)\n");
    printf("Oyunun cercevesi n*n olmak uzere n degerini giriniz: "); 
    
    while ((scanf("%d", &n) != 1) || n < 7 || n > 22 ) {
        printf("Lutfen gecerli bir deger giriniz.\n");
        while (getchar() != '\n'); 
        printf("Oyunun cercevesi n*n olmak uzere n degerini giriniz: ");
    }

    restart(); 

    while (1) {
        karakter();
        char yol;
        printf("\n");
        printf("[Q] -> Cikis :( \n[G] -> Menuye Don.\n[R] -> Yeniden Baslat.\n[X] -> Mayinlari Goster.\n'W', 'A', 'S', 'D' tuslariyla hareket edebilirsiniz.: ");
        scanf(" %c", &yol);
        if ((yol == 'w' || yol == 'W') && x > 0) {
    if (cerceve[x - 1][y] != 'x') {
        x--;
        cerceve[x][y] = '*';
    } else {
        tehlike();
    }
} else if ((yol == 'a' || yol == 'A') && y > 0) {
    if (cerceve[x][y - 1] != 'x') {
        y--;
        cerceve[x][y] = '*';
    } else {
        tehlike();
    }
} else if ((yol == 's' || yol == 'S') && x < n - 1) {
    if (cerceve[x + 1][y] != 'x') {
        x++;
        cerceve[x][y] = '*';
    } else {
        tehlike();
    }
} else if ((yol == 'd' || yol == 'D') && y < n - 1) {
    if (cerceve[x][y + 1] != 'x') {
        y++;
        cerceve[x][y] = '*';
    } else {
        tehlike();
    }
}
	else if (yol == 'q' || yol == 'Q') {
            printf("Programdan cikiliyor...\n");
            break;
        } else if (yol == 'g' || yol == 'G') {
			system("cls");
			main();
        } else if (yol == 'r' || yol == 'R') {
            printf("Mayinlar yeniden konumlandiriliyor ve en basa donuyorsunuz.\n\n");
            restart();
        } 
        
		
	if (yol == 'X' || yol == 'x') {
	system("cls");
            printf("Mayinlar ve Tehlikeli Bolgeler:\n");
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    if (cerceve[i][j] == 'o' || cerceve[i][j] == 'x') {
                        printf("%c", cerceve[i][j]); 
                    } else {
                        printf("#"); 
                    }
                }
                printf("\n");
            }
            printf("\n[G] <- Geri Don\n");
            char input;
            scanf(" %c", &input);
            if (input == 'g' || input == 'G') {
			system("cls");
                continue; 
            }
        }

		
		
		 else {
            printf("Gecersiz hareket! 'W', 'A', 'S', 'D' tuslarini kullanin.\n");
        }

        if (x == n - 1 && y == n - 1) {
	system("cls");
    printf("\n\n/* /* /* /* /* /* /* /* /* /*");
    printf("\nTEBRIKLER!! Oyunu kazandiniz!\n");
    printf("/* /* /* /* /* /* /* /* /* /*\n");
	karakterYoluIsaretle(cerceve, n, x, y);
    for ( i = 0; i < n; ++i) {
        for ( j = 0; j < n; ++j) {
            if (cerceve[i][j] == 'G') {
                printf("G");
            } else if (cerceve[i][j] == 'C') {
                printf("C");
            } else if (cerceve[i][j] == '*') {
                printf("*");
            } else {
                printf("%c", cerceve[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n[G] <- Menuye Don\n");
    char input;
    scanf(" %c", &input);
    if (input == 'g' || input == 'G') {
        system("cls");
        main();
    }
    
    break; 
}


        else if (cerceve[x][y] == 'x') {
			tehlike();
		}
    }
	}
	
	
	else if(secim==2)
	{
	system("cls");
	kurallar();
	printf("\n[G] <- Geri Git\n");
	char input;
	scanf(" %c", &input);
	if (input == 'g') {
	system("cls");
	main();
	}
	}
	
	else if(secim==3)
	{
	system("cls");
	printf("\n		ASLIHAN YILDIRIM\n		Tesekkurler.");
	printf("\n[G] <- Geri Git\n");
	char input;
	scanf(" %c", &input);
	if (input == 'g') {
	system("cls");
	main();
	}
	}
	
	else if(secim==4)
	{
    printf("Programdan cikiliyor...\n");		
	return 0;
	}

	else 
	{
		system("cls");
		printf("\n		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("\n		!!!!! Gecerli bir deger giriniz!!!!!\n");
		printf("\n		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
		main();
	}

	return 0;
}
