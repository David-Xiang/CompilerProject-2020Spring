#include "../run2.h"

void grad_case10(float (&dB)[10][8], float (&dA)[8][8]) {
    for (int h = 2; h < 10; ++h) {
        for (int j = 0; j < 8; ++j) {
            if ((h - 2 >= 0) && (h - 2 < 8)) {
                dB[h][j] += dA[h - 2][j] / 3.000000;
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            dB[i][j] += dA[i][j] / 3.000000;
        }
    }
    for (int h = 1; h < 9; ++h) {
        for (int j = 0; j < 8; ++j) {
            if ((h - 1 >= 0) && (h - 1 < 8)) {
                dB[h][j] += dA[h - 1][j] / 3.000000;
            }
        }
    }
}
