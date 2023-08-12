// Tyler Taormina 


#include <stdio.h>
#include <stdlib.h>

#include "algos.h"

#define N    4  // used for sum descent functions
#define M    7  // used for choose functions
#define P    8  // used for rod length and price array
#define INF  1000000000

//       Rod length     0  1  2  3  4  5   6   7   8
const int price[P+1] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
// Given this table solutions should be ...
// Length 4: 10 (2 length 2 pieces)
// Length 5: 
// Length 6: 
// Length 8: 

int t[N][N + 1] = {
  {2, INF, INF, INF, INF}, 
  {5, 4, INF, INF, INF},
  {1, 4, 7, INF, INF},
  {8, 6, 9, 6, INF}
};

int ct[M+1][M+1] = {{0}};
int tt[M+1][M+1] = {{0}};


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

    // Instead of calculating the full pascals triangle we can calculate just what we need.
    // The ine below will create the full triangle. 
    for (j = 0; j <= i && j <= k; j++) { // comment this line
    // for (j = 0; j <= i ; j++) { // uncomment this line for full triangle
      if (j == 0 || j == i) tt[i][j] = 1;
      else {
        tt[i][j] = tt[i-1][j] + tt[i-1][j-1];
      }
    }
  }
  return tt[n][k];
}

int
sum_descent(int r, int c) 
{
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
sum_descent_memo(int r, int c)
{
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
rodcut(int n)
{
  return 0;
}
