#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#ifdef _WIN32
#include "getopt_win.h"
#else
#include <unistd.h>
#include <getopt.h>
#endif

#include "gauth.h"


static void usage(FILE* fp) {
    fprintf(fp,
            "gauth-cli [options] <b32-secret>\n"
            " -h               Print this message\n"
            " b32-secret       base32 secret key\n"
            );
}

int main (int argc, char **argv){

    const char *secret = NULL;
    int index;
    int c;
    unsigned int step_sec = 30;

    opterr = 0;

    while ((c = getopt (argc, argv, "h")) != -1)
        switch (c){
        case 'h':
            usage(stdout);
            return 0;
        case '?':
        default:
            if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            usage(stderr);
            return 1;
        }

    for (index = optind; index < argc; index++)
        secret = argv[index];

    if(!secret || strlen(secret) < 2){
         fprintf(stderr, "Secret is too short\n");
        return 1;
    }

    const unsigned long tm = (const unsigned long)time(NULL) / step_sec;
    int totp = generateCode(secret, tm);
    fprintf(stdout, "%06d\n", totp);
    return 0;
}
