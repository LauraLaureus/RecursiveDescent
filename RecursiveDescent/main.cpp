#include "TokenChooser.hpp"

TokenChooser* tc;
Symbol nextToken;


void espacios();

int main(int argc, const char * argv[]) {
    
    
    tc = new TokenChooser("test.ng");
    nextToken = tc->nextToken();
    espacios();
}

void espacios(){

    switch (nextToken.token) {
        case GLOBAL:
            printf("GLOBAL");
            break;
        case FUNC:
            printf("FUNC");
            break;
        case EOF:
            printf("EOF");
            break;
        default:
            printf("DEFAULT");
            break;
    }
}
