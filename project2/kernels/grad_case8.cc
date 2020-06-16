#include "../run2.h"

void grad_case8(float (&dA), float (&dB)[32]) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 32; ++j) {
            dA[j][i] += dB[i][j];
        }
    }
}
