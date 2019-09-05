#ifndef _VERIFIER_H_
#define _VERIFIER_H_

#include <stdbool.h>

bool verify_server_parameters(int argc, char const *argv[]);

bool verify_client_parameters(int argc, char const *argv[]);

#endif
