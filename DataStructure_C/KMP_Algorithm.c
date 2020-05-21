#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getPrefixTable(char *temp, int len, int *ret) {
    int i = 0, j = -1;
    ret[0] = -1;
    while (i < len) {
        if (j == -1 || temp[i] == temp[j]) {
            ++i;
            ++j;
            if (i < len)
                ret[i] = j;
        } else {
            j = ret[j];
        }
    }
}

int search_index(char *str, char *temp, int pos) {
    int i = pos, j = 0;
    int slen = strlen(str);
    int tlen = strlen(temp);
    int next[tlen];
    getPrefixTable(temp, tlen, next);
    while (i < slen && j < tlen) {
        if (j == -1 || str[i] == temp[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j >= tlen)
        return i - tlen;
    else return 0;
}

int main(int argc, char const *argv[])
{
    char *str = "BBC ABCDAB ABCDABCDABDE";
    char *temp = "ABCDABD";
    int index = search_index(str, temp, 10);
    printf("index: %d", index);

    return 0;
}

