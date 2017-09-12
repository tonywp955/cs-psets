#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *p;
    char ch;
    char cho = '\0';

    p = fopen(argv[1], "r");

    const int raw = 1;
    const int startpot = 2;
    const int cmt1 = 3;
    const int cmt2 = 4;
    const int endpot = 5;
    const int blackhole1 = 6;
    const int blackhole2 = 7;

    bool block = true;
    int state = raw;
    
    while((ch = fgetc(p)) != EOF)
    {
        switch(state) {
            case raw:
                if (ch == '/') {
                    state = startpot;
                }
                break;
            case startpot:
                if (ch == '/') {
                    state = cmt1;
                    block = true;
                } else if (ch == '*') {
                    state = cmt2;
                    
                } else {
                    state = raw;
                }
                break;
            case cmt1:
                if (ch == '\n') {
                    printf("\n");
                    state = raw;
                } else if (ch == '@') {
                    state = blackhole1;
                    block = true;
                } else if (ch == ' ' && block == true){}
                else {
                    printf("%c", ch); 
                    block = false;
                }
                break;
            case cmt2:
                if (ch == '*') {
                    state = endpot;
                } else if (ch == '@') {
                    block = true;
                    state = blackhole2;
                } else if (ch == '\n'){
                    block = true;
                    printf("\n");
                }else if (ch == ' ' && block == true) {
                    //printf("what");
                }else{
                    printf("%c", ch);
                    block = false;
                }

                break;
            case endpot:
                if (ch == '/') {
                    block=false;
                    state = raw;
                } else if (ch == '*') {
                    state = endpot;
                    block = false;
                } else if (ch == '\n') {
                    state = cmt2;
                    printf("\n");
                    block = true;
                }else if (ch==' ' && block == true){
                }
                else {
                    printf("%c", ch);
                    block = false;
                    state = cmt2;
                }
                break;
            case blackhole1:
                if (ch == ' ')
                {
                    state = cmt1;
                }
                break;
            case blackhole2:
                if (ch == ' ')
                {
                    state = cmt2;
                }
            default:
                break;
        }
        cho = ch;
    }
}

