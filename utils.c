#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// return a pointer to the start of the (step+1)th token and its length
// mention that you should support ()
int readToken(Token * token, const char * string, int step){
    if(token == NULL)
        return TOKEN_BADARG;
    if(string)
        token->str = string;
    else if(token->str == NULL)
        return TOKEN_BADARG;
    do{
    // TODO
    // END of your code
    }while(step-- > 0);
    return TOKEN_SUCC;
}
