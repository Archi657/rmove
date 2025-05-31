/* rm implementation
to be able to avoid mistakes while deleting files this implementation will
never ever allow you to delete a file, but it will move it to the folder,
that will delete it automatically after if you do not regret your deletion.
*/
#include "../include/cli.h"
#include "../include/deleteF.h"
#include <stdio.h>

int main(int argc, char **argv){
    CLIOptions options = parseArguments(argc, argv);
    if(options.help){
        printf("Usage re [optional] [path]\n");
        printf("   -f  --force       Iteractive mode disabled\n");
        printf( "Usage re <required argument>\n");
        printf("   -hh --historical  Show history of 'deleted' files\n");
        printf("   -r  --rollback    Rollback mode\n");
        printf("   -h  --help        Help menu\n");
        return 0;
    }

    if(options.history){

    }

    if(options.rollback){

    }

    deleteF(&options);
   
}