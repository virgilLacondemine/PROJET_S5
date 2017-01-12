#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h
#include "plus_grand_affichage.h"

int main(int argc, char const *argv[]) {
	srand(time(NULL));
	int r = rand()%100;
	int d =- 1;
	s_start();

	while (r != d) {
		s_boucle();
		scanf("%i",&d);

		if (is_equal(r,d)) {
			s_egal();
		} else if (r < d) {
			s_plus();
		} else if (r > d) {
			s_moins();
		}	
	}  
}
