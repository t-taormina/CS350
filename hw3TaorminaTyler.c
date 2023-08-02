/* Tyler Taormina - HW 3 Horpool's */
/* taormina@pdx.edu */

// To compile 
/*  gcc -g -Wall -o hw3 hw3TaorminaTyler.c  */

/* run ->    ./hw3  -t file.txt
 *              this will set the text file to be searched to 'file.txt'
 *
 * run ->    ./hw3 -p dog 
 *              this will set the pattern to 'dog' and search for it in the given text 
 *              with Horspool's algorithm.
 *
 * run ->    ./hw3 -h 
 *              help message gets displayed
 *
 *
 * run ->    ./hw3 -p dog -t file.txt 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>


#define MAX 500
#define OPTIONS "p:t:h"

typedef struct user_input_s {
  char *pattern;
  char *text;
  size_t pattern_len;
  size_t text_len;
} user_input_t;

void build_shift_array(user_input_t, int *);
void horspool(user_input_t, int *);
user_input_t process_cmd_line(int, char **);

int
main(int argc, char **argv)
{
  user_input_t user_input = {NULL, NULL, 0, 0};
  int shift_array[MAX];

  user_input = process_cmd_line(argc, argv);
  build_shift_array(user_input, shift_array);
  horspool(user_input, shift_array);

  return EXIT_SUCCESS;
}

void 
horspool(user_input_t user_input, int *shift_array)
{
  int i, j;

  i = user_input.pattern_len - 1;

  while (i <= user_input.text_len) {
    j = 0;

    while ((j < user_input.pattern_len) && (user_input.pattern[(int)(user_input.pattern_len) - 1 - j] == user_input.text[i-j])) {
      j++;
    }

    if (j == user_input.pattern_len){
      printf("%ld\n", i - user_input.pattern_len + 1);
      i += shift_array[(int) (user_input.text[i])];
    } else {
      i += shift_array[(int) (user_input.text[i])];
    }
  }
}

void
build_shift_array(user_input_t user_input, int *shift_array)
{
  int i;
  
  for (i = 0; i < MAX; i++){
    shift_array[i] = user_input.pattern_len;
  }

  for (i = 0; i < user_input.pattern_len - 1; i++) {
    shift_array[(int) (user_input.pattern[i])] = user_input.pattern_len - 1 - i;
  }
}

user_input_t 
process_cmd_line(int argc, char **argv)
{
  user_input_t user_input = {NULL, NULL, 0, 0};
  {
    int opt = -1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
      switch (opt) {
        case 'p': 
          user_input.pattern = optarg;
          user_input.pattern_len = strlen(user_input.pattern);
          printf("%s  length: %ld\n", user_input.pattern, user_input.pattern_len);
          break;

        case 't': 
          user_input.text = optarg;
          user_input.text_len = strlen(user_input.text);
          printf("%s\n", user_input.text);
          break;

        case 'h':
          printf("%s:  -p <Pattern to search for>\n", argv[0]);
          printf("\t-t <Text file to search in>\n");
          exit(EXIT_SUCCESS);
          break;

        default: /* '?' */
          exit(EXIT_FAILURE);
          break;
      }
    }
  }
  return user_input;
}
