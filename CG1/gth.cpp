#include<stdio.h>

void Hanoi(int n,int x,int y)
{
    if(n>=2) Hanoi(n-1,x,6-x-y);

    printf("%d を %d 軸から %d 軸へ\n",n,x,y);

    if(n>=2) Hanoi(n-1,6-x-y,y);
}

int main(void)
{
    Hanoi(3,1,3);

    return 0;
}