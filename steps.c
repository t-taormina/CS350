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

int ct[7 + 1][7 + 1] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}
};


// Fibonacci sequence
int
steps(int num)
{
  if (num == 1) return 1;
  if (num == 2) return 2;
  return (steps(num - 1) + steps(num - 2));
}

int
choose(int n, int k)
{
  if (n == k) return 1;
  if (k == 0) return 1;
  return choose(n - 1, k - 1) + choose(n - 1, k);
}

int
choose_memo(int n, int k)
{
  if (ct[n][k] != 0) return ct[n][k];
  if (n == k || k == 0){
    ct[n][k] = 1;
    ct[n][n-k] = 1;
    return ct[n][k];
  } 
  ct[n][k] = choose_memo(n - 1, k - 1) + choose_memo(n - 1, k);
  ct[n][n-k] = ct[n][k];
  return ct[n][k];
}

int
choose_tab(int n, int k)
{
  int i, j;
  if (n == k || k == 0) return 1;
  if (k > n) return 0;
  for (i = 0; i <= n; i++) {

    // Instead of calculating the full pascals triangle we can calculate just what we need
    // by substituting in the line below for the j portion of the for loop. 
  
    // for (j = 0; j <= i && j <= k; j++) {
    for (j = 0; j <= i ; j++) {
      if (j == 0 || j == i) ct[i][j] = 1;
      else {
        ct[i][j] = ct[i-1][j] + ct[i-1][j-1];
      }
    }
  }
  return ct[n][k];
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
  int ans = steps(5);
  int ans1 = sum_descent(0, 0);
  int ans2 = sum_descent_memo(0, 0);
  int ans3 = sum_descent_tab(0, 0);
  int ans4 = choose(7, 3);
  // int ans5 = choose_memo(7, 6);
  int ans6 = choose_tab(7, 3);

  printf("Answer steps      : %d\n", ans);
  printf("Answer sum        : %d\n", ans1);
  printf("Answer memo sum   : %d\n", ans2);
  printf("Answer tab sum    : %d\n", ans3);
  printf("Answer n choose k : %d\n", ans4);
  // printf("Answer memo choose: %d\n", ans5);
  printf("Answer tab choose : %d\n", ans6);


  // Shows restructured array
  // /*
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      printf("%d ", ct[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  // */

  return EXIT_SUCCESS;
}
