#include <string.h>
#include "interface.h"
#include "sudoku_server.h"
#include "sudoku_client.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, char const *argv[]) {
    if (strcmp("server", argv[1]) == 0) {
        if (verify_server_parameters(argc,argv)) {
            return sudoku_run_as_server(argv[2]);
        }
    } else if (strcmp("client", argv[1]) == 0) {
        if (verify_client_parameters(argc,argv)) {
            return sudoku_run_as_client(argv[2], argv[3]);
        }
    } else {
        print_unsupported_mode_error();
    }
    return ERROR;
}
