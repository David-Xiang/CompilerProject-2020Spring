#include "../run2.h"

void grad_case9(float (&dA)[4], float (&dB)[4][6]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            dA[i] += dB[i][j];
        }
    }
}
