#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"

#define BUFFER_SIZE 512

//---------------------------------------------------------
// functions to manage pointer types
//---------------------------------------------------------

// INT
int *int_init(int a) {
  int *r = NULL;

  r = (int *)malloc(sizeof(int));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

int int_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (*(int *)c1 - *(int *)c2);
}

void *int_copy(const void *a) {
  int *c = NULL;

  if (!a)
    return NULL;

  c = int_init(*(int *)a);
  return (void *)c;
}

void int_free(void *a) { free((int *)a); }

int int_print(FILE *pf, const void *a) { return fprintf(pf, "%d", *(int *)a); }

// CHAR
char *char_init(char a) {
  char *r = NULL;

  r = (char *)malloc(sizeof(char));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

void *char_copy(const void *a) {
  char *c = NULL;

  if (!a)
    return NULL;

  c = char_init(*(char *)a);
  return (void *)c;
}

int char_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (*(char *)c1 - *(char *)c2);
}

void char_free(void *a) { free((char *)a); }

int char_print(FILE *pf, const void *a) {
  if (!pf || !a)
    return -1;

  return fprintf(pf, "%c", *(char *)a);
}

// FLOAT
float *float_init(float a) {
  float *r = NULL;

  r = (float *)malloc(sizeof(float));
  if (!r) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  *r = a;
  return r;
}

void *float_copy(const void *a) {
  float *c = NULL;

  if (!a)
    return NULL;

  c = float_init(*(float *)a);
  return (void *)c;
}

int float_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;
  if (*(float *)c1 > *(float *)c2)
    return 1;
  else if (*(float *)c2 > *(float *)c1)
    return -1;
  else
    return 0;
}

void float_free(void *a) { free((float *)a); }

int float_print(FILE *pf, const void *a) {
  if (!pf || !a)
    return -1;
  return fprintf(pf, "%f", *(float *)a);
}

//  String
void *string_copy(const void *src) { return strdup(src); }

int string_cmp(const void *c1, const void *c2) {
  if (!c1 || !c2)
    return 0;

  return (strcmp(*(char **)c1, *(char **)c2));
}

void string_free(void *src) { free((char *)src); }

int string_print(FILE *pf, const void *src) {
  if (!pf || !src)
    return -1;
  return fprintf(pf, "%s", (char *)src);
}

//---------------------------------------------------------
//---------------- conversion functions -------------------
//---------------------------------------------------------

/**  Convert string to integer pointer
 *
 * error handling as in
 * https://wiki.sei.cmu.edu/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number
 **/
void *str2int(const char *str) {
  char *end;
  int *si = malloc(sizeof(int));

  if (!si)
    return NULL;

  errno = 0;
  const long sl = strtol(str, &end, 10);

  if (end == str) {
    fprintf(stderr, "%s: not a decimal number\n", str);
  } else if ('\0' != *end) {
    fprintf(stderr, "%s: extra characters at end of input: %s\n", str, end);
  } else if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno) {
    fprintf(stderr, "%s out of range of type long\n", str);
  } else if (sl > INT_MAX) {
    fprintf(stderr, "%ld greater than INT_MAX\n", sl);
  } else if (sl < INT_MIN) {
    fprintf(stderr, "%ld less than INT_MIN\n", sl);
  } else {
    *si = (int)sl;
    return si;
  }

  free(si);
  return NULL;
}

/* convert string to string, i.e duplicate string*/
void *str2str(const char *str) { return strdup(str); }

/* convert string to char pointer */
void *str2chr(const char *str) {
  char *c = malloc(sizeof(char));
  if (!c)
    return NULL;
  *c = str[0];
  return c;
}