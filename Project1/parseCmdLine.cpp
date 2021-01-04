#include "parseCmdline.h"


int parseCmdLine(int argc, char *argv[], pCallback p, void *userData) {
    int argumentCounter = 0;
    bool no_error;
    char * param, *value;

    //for every item on argv
    for (int i = 1; i<argc; i++){
        param = argv[i];

        // If a key is encountered the next argument is either a value or NULL. If the program encounters a NULL returns an error. 
        if (param[0]=='-'){
            if (param[1] != '\0'){
                argumentCounter++; // increment counter by 1
                value = argv[++i]; // We offset the iteration variable so the option's value doesn't get picked up as a parameter in the next iteration
                if (value == NULL){
                    no_error = false;
                }
                else {
                    no_error = p(param + 1, value, userData); //param + 1 because the '-' isn't part of the key
                }
            }
            else{
                no_error = false;
            }
        }
        else{
            argumentCounter++; // increment counter by 1 param
            no_error = p(NULL, param, userData);
        }

        /* If we detect any errors during the parse, or the callback function does, then we stop processing info */
        if (!no_error){
            return -1;
        }
    }
    return argumentCounter; 
}