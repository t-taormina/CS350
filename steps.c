// Tyler Taormina 
//
/*  gcc -g -Wall -o steps steps.c   */

#include <stdio.h>
#include <stdlib.h>

#define N  4
#define INF  1000000000

int t[N][N + 1] = {
  {2, INF, INF, INF, INF}, 
  {5, 4, INF, INF, INF},
  {1, 4, 7, INF, INF},
  {8, 6, 9, 6, INF}
};


int
steps(int num)
{
  if (num == 1) return 1;
  if (num == 2) return 2;
  return (steps(num - 1) + steps(num - 2));
}

int
sum_descent(int r, int c) {
  int a, b, min;
  if ((r >= N - 1) || (c >= N - 1)) {
    return t[r][c];
  }
  a = sum_descent(r + 1, c);
  b = sum_descent(r + 1, c + 1);
  min = a;
  if (b < min) min = b;
  return t[r][c] + min;
}

int
sum_descent_memo(int r, int c) {
  int a, b, min;
  if ((r >= N -1) || (c >= N -1)) {
    t[N-r-1][N-c] = t[r][c];
    return t[r][c];
  }

  if (t[N-r-1][N-c] != INF) {
    return t[N-r-1][N-c];
  } 

  b = sum_descent_memo(r + 1, c + 1);
  a = sum_descent_memo(r + 1, c);
  min = b;
  if (a < min) min = a;
  t[N-r-1][N-c] = t[r][c] + min;
  return t[N-r-1][N-c];
}

int
sum_descent_tab(int r, int c) 
{
  int i, j, a, min;
  if (r == N)
    return t[r][c];

  for (i = N-2; i >= 0; i--) {
    for (j = 0; j < i + 1; j++) {
      min = t[i][j] + t[i+1][j];
      a = t[i][j] + t[i+1][j+1];
      if (a < min) min = a;
      t[i][j] = min;
    }
  }
  return t[r][c];
}

int 
main(int argc, char *argv[])
{
  int i, j;
  //int ans = steps(5);
  int ans1 = sum_descent(0, 0);
  int ans2 = sum_descent_memo(0, 0);
  int ans3 = sum_descent_tab(3, 3);

  //printf("Answer steps   : %d\n", ans);
  printf("Answer sum     : %d\n", ans1);
  printf("Answer memo sum: %d\n", ans2);
  printf("Answer tab sum : %d\n", ans3);


  // Shows restructured array
  /*
  for (i = 0; i < N; i++) {
    for (j = 0; j < N + 1; j++) {
      if (t[i][j] != INF) printf("%d ", t[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  */

  return EXIT_SUCCESS;
}
