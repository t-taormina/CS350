// Tyler Taormina - taormina@pdx.edu

#include <stdio.h>
#include <stdlib.h>

#include "algos.h"

#define N    4          // used for sum descent functions
#define M    7          // used for choose functions
#define P    8          // used for rod length and price array
#define INF  1000000000 // used for filling table 't' in sum descent solution

// RUNTIMES
// Rodcutting  - O(n^2) time complexity
// Rodcutting  - O(n) space complexity
// Sum descent - O(n) time complexity
// Sum descent - O(n^2) space complexity
// Choose      - O(n) time complexity
// Choose      - O(n) space complexity


// GLOBALS
// =========================================================================
//       Rod length     0  1  2  3  4  5   6   7   8
const int price[P+1] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
// Given this table solutions should be ...
// Length 4: 10 (2 length 2 pieces)
// Length 5: 13
// Length 6: 18
// Length 8: 22

// Rodcut memoized solutions table 
int rm[P+1] = {[0 ... P] = -1};

// Rodcut tabulized solutions table
int rt[P+1] = {[0 ... P] = 0};

// Minimum sum descent table
int t[N][N + 1] = {
  {2, INF, INF, INF, INF}, 
  {5, 4, INF, INF, INF},
  {1, 4, 7, INF, INF},
  {8, 6, 9, 6, INF}
};

int cm[M+1][M+1] = {{0}}; // Choose memoized solution table
int ct[M+1][M+1] = {{0}}; // Choose tabulized solution table

// =========================================================================
// END GLOBALS

int
rodcut(int n)
{
  int a, i, max;

  if (n == 0) return 0;
  max = -1;
  for (i = 1; i <= n; i++) {
    a =  price[i] + rodcut(n-i);
    if (a > max) max = a;
  }
  return max;
}

int
rodcut_memo(int n)
{
  int a, i, max;

  if (rm[n] != -1) return rm[n];
  if (n == 0) max = 0;
  else {
    max = -1;
    for (i = 1; i <= n; i++) {
      a = price[i] + rodcut_memo(n - i);
      if (a > max) max = a;
    }
  }

  rm[n] = max;
  return rm[n];
}

int
rodcut_tab(int n)
{
  int a, i, j, max;

  if (n == 0) return 0;
  for (i = 1; i <= n; i++) {
    max = -1;
    for (j = 1; j <= i; j++) {
      a = price[j] + rt[i-j];
      if (a > max) max = a;
    }
    rt[i] = max;
  }
  return rt[n];
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
  if ((r >= N - 1) || (c >= N - 1)) {
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
  int a, i, j, min;
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
choose(int n, int k)
{
  if (n == k) return 1;
  if (k == 0) return 1;
  return choose(n - 1, k - 1) + choose(n - 1, k);
}

int
choose_memo(int n, int k)
{
  if (cm[n][k] != 0) return cm[n][k];
  if (n == k || k == 0){
    cm[n][k] = 1;
    cm[n][n-k] = 1;
    return cm[n][k];
  } 
  cm[n][k] = choose_memo(n - 1, k - 1) + choose_memo(n - 1, k);
  cm[n][n-k] = cm[n][k];
  return cm[n][k];
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
      if (j == 0 || j == i) ct[i][j] = 1;
      else {
        ct[i][j] = ct[i-1][j] + ct[i-1][j-1];
      }
    }
  }
  return ct[n][k];
}
