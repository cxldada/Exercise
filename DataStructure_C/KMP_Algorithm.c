#include <stdio.h>
#include <stdlib.h>

// a b a a b c
// 0 1 
void getPrefixTable(char *temp, int len, int *ret) {
    int l = 0, j = 0;
    ret[0] = 0;
    while (l < len) {
        if (j == 0 || temp[l] == temp[j]) {
            ++l;
            ++j;
            ret[l] = j;
        } else {
            j = ret[j];
        }
    }
}

int index(char *str, int slen, char *temp, int tlen) {
}

int main(int argc, char const *argv[])
{
    return 0;
}

