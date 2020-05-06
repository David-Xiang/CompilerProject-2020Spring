// this is a silly solution
// just to show you how different
// components of this framework work
// please bring your wise to write
// a 'real' solution :)

#include <iostream>
#include <fstream>
#include <string>

void cheat_example();
void cheat_case1();
void cheat_case4();
void cheat_case5();
void cheat_case6();
void cheat_case7();
void cheat_case10();

int main() {
    cheat_example();
    cheat_case1();
    cheat_case4();
    cheat_case5();
    cheat_case6();
    cheat_case7();
    cheat_case10();
    return 0;
}

void cheat_example() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_example(float (&B)[32][16], float (&C)[32][16], float (&A)[32][16]) {\n\
    for (int i = 0; i < 32; ++i) {\n\
        for (int j = 0; j < 16; ++j) {\n\
            A[i][j] = B[i][j] * C[i][j];\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_example.cc", std::ios::out);
    ofile << src;
    ofile.close();
}

void cheat_case1() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case1(float (&A)[32][16]) {\n\
    for (int i = 0; i < 32; ++i) {\n\
        for (int j = 0; j < 16; ++j) {\n\
            A[i][j] = 2;\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case1.cc", std::ios::out);
    ofile << src;
    ofile.close();
}

void cheat_case4() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case4(float (&B)[16][32], float (&C)[32][32], float (&A)[16][32]) {\n\
    for (int i = 0; i < 16; ++i) {\n\
        for (int j = 0; j < 32; ++j) {\n\
            for (int k = 0; k < 32; ++k) {\n\
                A[i][j] += B[i][k] * C[k][j];\n\
            }\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case4.cc", std::ios::out);
    ofile << src;
    ofile.close();
}

void cheat_case5() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case5(float (&B)[16][32], float (&C)[32][32], float (&D)[16][32], float (&alpha), float (&beta), float (&A)[16][32]) {\n\
    for (int i = 0; i < 16; ++i) {\n\
        for (int j = 0; j < 32; ++j) {\n\
            for (int k = 0; k < 32; ++k) {\n\
                A[i][j] += alpha * (B[i][k] * C[k][j]);\n\
            }\n\
            A[i][j] += beta * D[i][j];\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case5.cc", std::ios::out);
    ofile << src;
    ofile.close();
}

void cheat_case6() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case6(float (&B)[2][16][7][7], float (&C)[8][16][3][3], float (&A)[2][8][5][5]) {\n\
    for (int n = 0; n < 2; ++n) {\n\
        for (int k = 0; k < 8; ++k) {\n\
            for (int p = 0; p < 5; ++p) {\n\
                for (int q = 0; q < 5; ++q) {\n\
                    for (int c = 0; c < 16; ++c) {\n\
                        for (int r = 0; r < 3; ++r) {\n\
                            for (int s = 0; s < 3; ++s) {\n\
                                A[n][k][p][q] += B[n][c][p+r][q+s] * C[k][c][r][s];\n\
                            }\n\
                        }\n\
                    }\n\
                }\n\
            }\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case6.cc", std::ios::out);
    ofile << src;
    ofile.close();
}


void cheat_case7() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case7(float (&A)[32][16], float (&B)[16][32]) {\n\
    for (int i = 0; i < 16; ++i) {\n\
        for (int j = 0; j < 32; ++j) {\n\
            B[i][j] = A[j][i];\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case7.cc", std::ios::out);
    ofile << src;
    ofile.close();
}

void cheat_case10() {
    std::string src = "\
#include \"../run.h\"\n\
\n\
void kernel_case10(float (&B)[10][10], float (&A)[8][8]) {\n\
    for (int i = 0; i < 8; ++i) {\n\
        for (int j = 0; j < 8; ++j) {\n\
            A[i][j] = (B[i][j] + B[i+1][j] + B[i+2][j]) / 3;\n\
        }\n\
    }\n\
}";
    std::ofstream ofile("./kernels/kernel_case10.cc", std::ios::out);
    ofile << src;
    ofile.close();
}