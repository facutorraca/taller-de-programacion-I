#ifndef _SUDOKU_CLIENT_H_
#define _SUDOKU_CLIENT_H_

#include "client.h"

#define SUCCESS 0
#define ERROR 1

int sudoku_client_start(const char* host, const char* port);

#endif
