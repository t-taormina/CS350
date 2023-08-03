/* Tyler Taormina - HW 3 Horpool's */
/* taormina@pdx.edu */

// To compile 
/*  gcc -g -Wall -o hw3 hw3TaorminaTyler.c  */

/* run ->    ./hw3  -f file.txt
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
 * run ->    ./hw3 -p Arlo -t test.txt 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define MAX 500
#define MAX_TEXT_FILE 1000
#define OPTIONS "p:f:h"

typedef struct user_input_s {
  char   *pattern;
  char   *file;
} user_input_t;

typedef struct search_items_s {
  char   *pattern;
  size_t pattern_len;
  size_t text_len;
  char   text[MAX_TEXT_FILE];
} search_items_t;

void         build_shift_array(int *, search_items_t *);
void         confirm_input(user_input_t *);
void         read_in_text(user_input_t *, search_items_t *);
void         horspool(int *, search_items_t *);
user_input_t process_cmd_line(int, char **);


int
main(int argc, char **argv)
{
  user_input_t user_input = {NULL, NULL};
  search_items_t search_items = {NULL, 0, 0};
  
  int shift_array[MAX];

  user_input = process_cmd_line(argc, argv);
  confirm_input(&user_input);
  read_in_text(&user_input, &search_items);
  build_shift_array(shift_array, &search_items);
  horspool(shift_array, &search_items);

  return EXIT_SUCCESS;
}

void 
horspool(int *shift_array, search_items_t *search_items)
{
  int i, j;

  i = search_items->pattern_len - 1;

  while (i <= search_items->text_len) {
    j = 0;

    while ((j < search_items->pattern_len) && (search_items->pattern[(int)(search_items->pattern_len) - 1 - j] == search_items->text[i-j])) {
      j++;
    }

    if (j == search_items->pattern_len){
      printf("String found at index: %ld\n", i - search_items->pattern_len + 1);
    }

    i += shift_array[(int) (search_items->text[i])];
  }
}

void
build_shift_array(int *shift_array, search_items_t *search_items)
{
  int i;
  
  for (i = 0; i < MAX; i++){
    shift_array[i] = search_items->pattern_len;
  }

  for (i = 0; i < search_items->pattern_len - 1; i++) {
    shift_array[(int) (search_items->pattern[i])] = search_items->pattern_len - 1 - i;
  }
}

void
read_in_text(user_input_t *user_input, search_items_t *search_items)
{
  FILE *fp;
  int i;
  char c;
  
  fp = fopen(user_input->file, "r");
  if (NULL == fp) {
    perror("Cannot open file for reading");
    exit(EXIT_FAILURE);
  }

  i = 0;
  while ( (c = fgetc(fp)) != EOF && (i < MAX_TEXT_FILE) ) {
    search_items->text[i] = c;
    i++;
  }
  fclose(fp);

  search_items->pattern = user_input->pattern;
  search_items->pattern_len = strlen(search_items->pattern);
  search_items->text_len = i;
}

user_input_t 
process_cmd_line(int argc, char **argv)
{
  user_input_t user_input = {NULL, NULL};
  {
    int opt = -1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
      switch (opt) {
        case 'p': 
          user_input.pattern = optarg;
          break;

        case 'f': 
          user_input.file = optarg;
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

void
confirm_input(user_input_t *user_input)
{
  if (NULL == user_input->pattern) {
    fprintf(stderr, "No provided pattern to search for. Cannot run Horspool's.\n");
    exit(1);
  }

  if (NULL == user_input->file) {
    fprintf(stderr, "No provided text file to search in. Cannot run Horspool's.\n");
    exit(2);
  }
}
