#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#define STACK_SIZE 100
#define STACK_INCREMENT 10

typedef unsigned StackElement;
typedef enum{ERROR=0,OK=1}Status;
typedef enum{NO=0,YES=1}YesNo;

typedef struct stack{
   char data[STACK_SIZE];
   int num;
   int pTop;
   int pBase;
}Stack;

Stack * CreateStack(){
	Stack * pSt = (Stack*)malloc(sizeof(Stack));
	if(pSt == NULL){
		return ;
	pSt->pTop = pSt->pBase = 0;
	return pSt;
	}
}

Status ClearStack(Stack* pSt){
    pSt->pTop=pSt->pBase;
    return OK;
}

YesNo IsStackEmpty(Stack* pSt){
    if(pSt->pTop==pSt->pBase){
        return YES;
    }
    else {
        return NO;
    }
}

void PushStack(Stack* pSt,int num){
	pSt->pTop = num;
	pSt->pTop++;
}

void PopStack(Stack* pSt,int num){
	int n = pSt->pTop;
	if(n == pSt->pBase){
		return;
	}
	else{
		num = pSt->data[pSt->pTop];
		pSt->pTop--;
	}
}

int chrtodec(int chr){
    int value=0;
    if((chr>='a')&&(chr<='z'))
            chr=chr-32;
    if((chr>='0')&&(chr<='9'))
            value=chr-48;
    else if((chr>='A')&&(chr<='Z'))
            value=chr-65+10;
    return value;
}

int main(){
	char expre[STACK_SIZE],data[STACK_SIZE];
	int i,result,temp,res;
	Stack * pSt;
	pSt = CreateStack();
	printf("enter the expression: ");
	gets(expre);
	for(i=0;i<strlen(expre);i++){
		if(isdigit(expre[i])){
			PushStack(pSt,expre[i]);
		}
		
		switch(expre[i]){
			case '+':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    expre[i] = expre[i-1] + expre[i-2];
			    PushStack(pSt,expre[i]);
			    res = expre[i];
			    break;
			case '-':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    expre[i] = expre[i-2] - expre[i-1];
			    PushStack(pSt,expre[i]);
			    res = expre[i];
			    break;
			case '*':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    expre[i] = expre[i-1] * expre[i-2];
			    PushStack(pSt,expre[i]);
			    res = expre[i];
			    break;
			case '/':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    expre[i] = expre[i-2] / expre[i-1];
			    PushStack(pSt,expre[i]);
			    res = expre[i];
			    break;
	    }
    }
    chrtodec(res);
    result = res - 96;
	printf("%d",result);
	return 0;
}
