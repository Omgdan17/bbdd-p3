/**
 * @file types.h
 * @author Teaching team of EDAT.
 * @date April 2023.
 * @brief ADTs Boolean, Status and pointer to comparison/print functions.
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 512
#define NCMD 7
#define NMTH 3
#define NO_ID -1

#define IBOOK 0
#define IDEL 1

/**
 * @brief ADT command
 */
typedef enum
{
    NO_CMD = -1,
    EXIT,
    ADD,
    FIND,
    DEL,
    PRINTIND,
    PRINTLST,
    PRINTREC
} Command;

/**
 * @brief ADT method
 */
typedef enum
{
    DEFAULT = -1,
    FIRST,
    BEST,
    WORST
} Method;

/**
 * @brief ADT Boolean
 */
typedef enum
{
    FALSE = 0, /*!< False value */
    TRUE = 1   /*!< True value  */
} Bool;

/**
 * @brief ADT Status
 */
typedef enum
{
    ERROR = 0, /*!< To codify an ERROR output */
    OK = 1     /*!< OK output */
} Status;

/**
 * P_ele_print type definition: pointer to a function that prints an
 * element to an output stream. It is assumed that this function returns: (1)
 * the number of characters printed upon success; or (2) a negative number in
 * case of error.
 */
typedef int (*P_ele_print)(FILE *, const void *);

/**
 * P_ele_cmp type definition: pointer to a function that compares two
 * elements. It returns an integer less than, equal to, or greater
 * than zero if e1 is found, respectively, to be less than, to match, or to be
 * greater than e2.
 */
typedef int (*P_ele_cmp)(const void *, const void *);

/**
 * P_ele_free type definition: pointer to a function that frees que memory allocated for an element.
 */
typedef void (*P_ele_free)(void *);

/**
 * P_ele_load type definition: pointer to a function that loads the data of a file on an indexbook
 */
typedef void *(*P_ele_load)(FILE *f);

/**
 * P_ele_save type definition: pointer to a function that saves the data of an indexbook in a file
 */
typedef int (*P_ele_save)(const void *, FILE *pf);

#endif /* TYPES_H_ */