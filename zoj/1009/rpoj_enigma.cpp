//http://code.google.com/p/rpoj/source/browse/trunk/zoj/1009/1009.c?r=159
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char const* argv[])
{
    int i, j, n, m, t, iCase;
    char cTemp[1024];
    int iConvert[3];
    int iChange[3][26];

    iCase = 0;
    while (scanf("%d", &m) && m) {
        if (iCase++) printf("\n");
        printf("Enigma %d:\n", iCase);

        for (i = 0; i < 3; i++) {
            scanf("%s", cTemp);
            for (j = 0; j < m; j++) {
                iChange[i][cTemp[j]-'A'] = j - (cTemp[j] - 'A');
            }
        }

        scanf("%d", &n);
        while (n--) {
            scanf("%s", cTemp);
            for (i = 0; i < strlen(cTemp); i++) {
                iConvert[0] = i % m;
                iConvert[1] = (i / m) % m;
                iConvert[2] = (i / (m * m)) % m;

                t = cTemp[i] - 'A';

                for (j = 2; j >= 0; j--) {
                    t += iChange[j][(t-iConvert[j]+m)%m];
                    t = (t + m) % m;
                }
                printf("%c", t + 'a');
            }
            printf("\n");
        }
    }

    return 0;
}

