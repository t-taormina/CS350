// Tyler Taormina - taormina@pdx.edu

#include <stdio.h>
#include <stdlib.h>

#include "algos.h"


int 
main(void)
{
  int ans1 = sum_descent(0, 0);
  int ans2 = sum_descent_memo(0, 0);
  int ans3 = sum_descent_tab(0, 0);
  int ans4 = choose(7, 2);
  int ans5 = choose_memo(7, 2);
  int ans6 = choose_tab(7, 2);
  int ans7 = rodcut(5);
  int ans8 = rodcut_memo(5);
  int ans9 = rodcut_tab(5);

  printf("Answer sum          : %d\n", ans1);
  printf("Answer memo sum     : %d\n", ans2);
  printf("Answer tab sum      : %d\n", ans3);
  printf("Answer naive choose : %d\n", ans4);
  printf("Answer memo choose  : %d\n", ans5);
  printf("Answer tab choose   : %d\n", ans6);
  printf("Answer naive rodcut : %d\n", ans7);
  printf("Answer memo rodcut  : %d\n", ans8);
  printf("Answer tab rodcut   : %d\n", ans9);

  return EXIT_SUCCESS;
}
