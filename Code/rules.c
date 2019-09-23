#include <stdbool.h>
#include <stdlib.h>

bool number_is_valid(int number) {
    return number >= 1 && number <= 9;
}

bool position_is_valid(int row, int col) {
    bool row_is_correct = (row >= 1 && row <= 9);
    bool col_is_correct = (col >= 1 && col <= 9);
    return row_is_correct && col_is_correct;
}

int cmp_by_number(const void *num_a, const void *num_b) {
    int int_a = *(char*)num_a - '0';
    int int_b = *(char*)num_b - '0';
    return int_a - int_b;
}

bool line_is_correct(char* numbers) {
    qsort(numbers, 9, sizeof(char), cmp_by_number);
    for (int i = 1; i < 9; i++) {
        if (numbers[i-1] == numbers[i] && numbers[i] != ' ') {
            return false;
        }
    }
    return true;
}
