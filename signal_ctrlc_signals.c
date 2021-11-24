#include <stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int count = 0;
char c[30];

void toolong(int arg){
   printf( "\n------------User taking too long to respond. Exiting  . . .------------\n");
    exit(0);
}

void STP(int arg){
    printf("\nSo far, '%d' Ctl-C presses were counted\n",count);
}

void INTE(int arg){
    fflush(stdout);
    count++;
    if(count == 5){
        signal(SIGALRM , toolong);
        alarm(10);
        count =0;
        printf("\nReally exit? [Y/n]: ");
        fflush(stdout);
        fgets(c,80,stdin);
        if(c[0]=='y'||c[0]=='Y'){
            printf("------------BYE--------------\n");
            fflush(stdout);
            exit(0);
        }
        else if(c[0] =='n'||c[0]=='N'){
            printf("\nContinuing\n");
            count =0;
            fflush(stdout);
            signal(SIGALRM , SIG_IGN);
        }
    }
}


int main(void){
    signal(SIGINT , INTE);
    signal(SIGTSTP , STP);
    while(1);
    return 0;
