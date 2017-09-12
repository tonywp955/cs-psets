#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *p;
    char ch;

    p = fopen(argv[1], "r");

    enum STATE {
        raw = 1,
        startpot = 2,
        cmt1 = 3,
        cmt2 = 4,
        endpot = 5,
        blackhole1 = 6,
        blackhole2 = 7
    };
    
    bool block = true;
    enum STATE state = raw;
    
    while((ch = fgetc(p)) != EOF)
    {
        if(state == raw){
                if (ch == '/') {
                    state = startpot;
                }
        }else if(state == startpot){

            if (ch == '/') {
                    state = cmt1;
                    block = true;
                } else if (ch == '*') {
                    state = cmt2;
                    
                } else {
                    state = raw;
                }
        }else if (state == cmt1) {
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
        }else if (state == cmt2)                
        {if (ch == '*') {
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
        }else if (state == endpot) {
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
        } else if (state == blackhole1) {
                if (ch == ' ')
                {
                    state = cmt1;
                }
        } else if (state == blackhole2)
        { if (ch == ' ')
                {
                    state = cmt2;
                }
        }        
    
    }
}


