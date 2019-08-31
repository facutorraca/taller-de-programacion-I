#ifndef _VERIFIER_H_
#define _VERIFIER_H_

#include <stdbool.h>

bool controller_validate_server_parameters(int argc, char const *argv[]);

bool controller_validate_client_parameters(int argc, char const *argv[]);

bool verifier_verify_put_instruction(const char* instruction);

bool verifier_verify_get_instruction(const char* instruction);

bool verifier_verify_verify_instruction(const char* instruction);

bool verifier_verify_reset_instruction(const char* instruction);

#endif
