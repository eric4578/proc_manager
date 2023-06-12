#ifndef UTILS_H_
#define UTILS_H_
typedef struct {
    const char * str;
    int len;
} Token;

enum TOKEN_CODE {TOKEN_SUCC=0, TOKEN_BADARG, TOKEN_EARLYEND};

int readToken(Token * t, const char * string, int pos);
#endif