#include <stdio.h>
#include <stdlib.h>

void show(int data[3][3]) {
	int l;
	printf("-------");
	for (int i=0;i<3;++i) {
		printf("\n");
		for (int j=2;j>=0;--j) {
			if (j==2)
				printf("|");
			
			l = 9 - (i*3 + j);
			if (data[i][j]==1) {
				printf("X|");	
			} else if (data[i][j]==11) {
				printf("O|");			
			} else {
				printf("%i|",l);
			}
		}
	}
	printf("\n-------\n");
}

int check_win(int data[3][3]) {
	int w;
	int b = 0;
	for (int i=0;i<8;++i) {
		w = 0;
		if (i<3) {
			w += data[i][0];
			w += data[i][1];
			w += data[i][2];
		} else if (i >= 3 && i < 6) {
			w += data[0][i-3];
			w += data[1][i-3];
			w += data[2][i-3];
		} else if (i == 6) {
			w += data[0][0];
			w += data[1][1];
			w += data[2][2];
		} else if (i == 7) {
			w += data[0][2];
			w += data[1][1];
			w += data[2][0];
		}

		if (w == 33) {
			b = 1;
		} else if (w == 3) {
			b = 2;
		}
	}
	return b;
}

void run() {
	int data[3][3];
	int x;
	int y;
	int r;
	int turn = 11;
	int n = 0;
	int win = 0;
	for (int i=0;i<3;++i) {
		for (int j=0;j<3;++j) {
			data[i][j] = -1;
		 }
	}
	show(data);

	while (n < 9 && !win) {
		if (turn == 11) 
			printf("Entrez une case Joueur 1 : ");
		else		
			printf("Entrez une case Joueur 2 : ");

		scanf("%i",&r);
		if (r>0 && r<=9) {
			x = (9-r) / 3;
			y = (9-r) % 3;
			data[x][y] = turn;

			show(data);
			turn = 12 - turn;

			n++;
			win = check_win(data);
			if (win == 2) {
				printf("Bravo J2 !\n");
			} else if (win == 1) {
				printf("Bravo J1 !\n");
			}
		}
	}
}

int main(void) {
	run();
}
