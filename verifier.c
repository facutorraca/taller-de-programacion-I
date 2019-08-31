#include <stdbool.h>

bool controller_validate_server_parameters(int argc, char const *argv[]) {
    return true;
}

bool controller_validate_client_parameters(int argc, char const *argv[]) {
    return true;
}

bool verifier_verify_put_instruction(const char* instruction) {
    return true;
}

bool verifier_verify_get_instruction(const char* instruction) {
    return true;
}

bool verifier_verify_verify_instruction(const char* instruction) {
    return true;
}

bool verifier_verify_reset_instruction(const char* instruction) {
    return true;
}
