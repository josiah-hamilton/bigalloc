#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#include<sysexits.h>
#include<string.h>

#define BUFSIZE     1024
#define SLEEPSECONDS 36000
#define NUMPARAMS   3
#define MINPARAMS   1
#define COUNT       0
#define SLEEPDUR    1
#define PASSES      2


/*
 bigalloc
 SYNOPSYS
    bigalloc <num_bytes> [ sleep_duration number_passes ]
 DESCRIPTION
    bigalloc is a utility meant to generate memory contentions on multi-user systems.
    It operates by allocating an array whose size is num_bytes and occupies
    physical memory in a manner controlled by the user. With no additional
    parameters, the RES memory usage by the program is maximized as fast as 
    possible. With the additional parameters sleep_duration and number_passes
    The RES memory consumption is increased in number_passes passes, each pass
    increases the memory consumption by num_bytes/number_passes, and each pass
    is delimited by a sleep_duration sleep of the process. This is meant to 
    simulate programs whose memory consumption change over time


 To Do 
 Find a better way to sleep and determine termination than waiting 1000 hours
      or keyboard interrupt
*/
char usagestring[BUFSIZE] = "Usage: %s <num_bytes> [ sleep_duration number_passes ]\n";

void usage(char *__progname) {
    fprintf(stderr,usagestring,__progname);
    exit(EX_USAGE);
}


int main (int argc, char **argv) {

    char __progname[BUFSIZE];
    size_t __prognamelen = strnlen(*argv,BUFSIZE);
    strncpy(__progname,*argv,__prognamelen+1);

    if ((argc != MINPARAMS+1) && (argc != NUMPARAMS+1)) {
        usage(__progname);
        exit(1);
    }
    long *params = calloc(NUMPARAMS,sizeof(long));
#ifdef DEBUG
    printf("Memory page size _SC_PAGESIZE %d\n", getpagesize());
#endif

    // Params size, sleep period, number of passes
    long i,j;
    char *serror;
    for (i = 0; i < NUMPARAMS; i++) {
        if (i < argc-1) {
            params[i] = strtol (argv[i+1], &serror, 10);
            if (*serror != 0) {
                exit(1);
            }
        } else {
            params[i] = 1;
        }
    }

    char *x = calloc(params[COUNT],sizeof(char));
    int pagesize = getpagesize();
    long period = params[COUNT] / (params[PASSES] * pagesize);
    //long period = params[COUNT] / (params[PASSES] );

    for (j = 0; j < params[PASSES]; j++) {
        //for (i = (j*period); i < ((j+1)*period)-1; i++) {
        //    x[i] = 1;
        //}
        for(i = (j*period); i < ((j+1)*period) - 1; i++) {
            x[i*pagesize] = 1;
        }
        printf("Pass %d complete\n",j);
        sleep(params[SLEEPDUR]);
    }

    sleep(SLEEPSECONDS);
    free(x);

    return 0;

}
