#include "stdio.h"

int main(int argc, char * argv[]) {
  float a;

  printf("ml' nob:\n");
  scanf("%f", & a);

  if (a != 1 && a != 2 && a != 3 && a != 4 && a != 5) {
    printf("luj");
  } else {
    if (a == 1) {
      printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
    }

    if (a == 2) {
      printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
    }

    if (a == 3) {
      printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
    }

    if (a == 4) {
      printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
    }

    if (a == 5) {
      printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
    }
  }

  return 0;
}
