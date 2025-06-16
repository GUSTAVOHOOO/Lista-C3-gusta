#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    ArvAVL* avl;
    int res,i;
    //int N = 10, dados[10] = {50,25,10,5,7,3,30,20,8,15};
    //int N = 11, dados[11] = {50,25,10,5,5,7,3,30,20,8,15};
    int N = 7, dados[7] = {57,22,10,0,15,60,88};

    avl = cria_ArvAVL();

    for(i=0;i<N;i++){
        res = insere_ArvAVL(avl,dados[i]);
    }
    emOrdem_ArvAVL(avl);


    return 0;
}
