/* Tyler Taormina - Pebbles program practicing recursive and dynamic problem solving */
/* taormina@pdx.edu */

/*  gcc -Wall -o pebbles pebbles.c  */


#include <stdio.h>
#include <stdlib.h>

int board[4][5] = {
  {0,0,1,0,1},
  {0,0,1,1,0},
  {1,0,0,0,1},
  {0,1,0,0,1}
};

int mtable[4][5] = {
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1}
};


int ttable[4][5] = {
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1}
};

int find_pebbles_naive_recursive(int, int);
int find_pebbles_memoized_recursive(int, int);
int find_pebbles_tabulized_recursive(int, int);


int 
main(int argc, char **argv)
{
  int ans1, ans2, ans3;
  ans1 = find_pebbles_naive_recursive(3, 4);
  printf("Naive implementation: %d\n", ans1);
  ans2 = find_pebbles_memoized_recursive(3, 4);
  printf("Memoized implementation: %d\n", ans2);
  ans3 = find_pebbles_tabulized_recursive(3, 4);
  printf("Tabulized implementation: %d\n", ans3);
}

// Naive recursive implementation
int
find_pebbles_naive_recursive(int r, int c)
{
  int a, b, max;

  if (r < 0 || c < 0) return 0;
  a = find_pebbles_naive_recursive(r-1, c);
  b = find_pebbles_naive_recursive(r, c-1);
  max = a;
  if (b > max) max = b;
  return board[r][c] + max;
}

// Memoized recursive implementation
int
find_pebbles_memoized_recursive(int r, int c)
{
  int a, b, max;

  if (r < 0 || c < 0) return 0;
  if (mtable[r][c] != -1) return mtable[r][c];
  a = find_pebbles_memoized_recursive(r-1, c);
  b = find_pebbles_memoized_recursive(r, c-1);

  max = a;
  if (b > max) max = b;
  mtable[r][c] = board[r][c] + max;
  return mtable[r][c];
}

// Tabulized iterative implementation
int
find_pebbles_tabulized_recursive(int r, int c)
{
  int i, j, a, b, max;

  if (r == 0 && c == 0) return board[r][c];
  for (i = 0; i <= r; i++) {
    for (j = 0; j <= c; j++) {
      if (i == 0 && j == 0) ttable[i][j] = board[i][j];
      else if (i > 0 && j > 0) {
        a = ttable[i-1][j];
        b = ttable[i][j-1];
        max = a;
        if (b > max) max = b;
        ttable[i][j] = max + board[i][j];
      }
      else if (i == 0 ) ttable[i][j] = board[i][j] + ttable[i][j-1];
      else ttable[i][j] = board[i][j] + ttable[i-1][j];
    }
  }
  return ttable[r][c];
}
