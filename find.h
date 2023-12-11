#ifndef FIND_H_
#define FIND_H_

#include "types.h"
#include "index.h"

Status find(Index *index, FILE *db, int key);

#endif