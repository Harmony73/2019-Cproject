#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <math.h>
#define STACK_SIZE 100
#define STACK_INCREMENT 10

typedef unsigned Element;
typedef enum{ERROR=0,OK=1}Status;
typedef enum{NO=0,YES=1}YesNo;

typedef struct stack{
   int* pTop;
   int* pBase;
}Stack;

Status CreateStack(Stack* pSt){
	pSt->pBase = (int*)malloc(STACK_SIZE*sizeof(int));
	if(pSt->pBase == NULL){
		return ERROR;
    }
	pSt->pTop = pSt->pBase;
	return OK;
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

//外部数字入栈 
void PushStack(Stack* pSt,float num){
	*(pSt->pTop) = num;
	pSt->pTop++;
}

//栈顶数字出站 
float PopStack(Stack* pSt,float num){
	if(pSt->pTop == pSt->pBase){
		return;
	}
	else{
		pSt->pTop--;
		num =*(pSt->pTop);
	}
	return num;
}

float Culculate(){
	char expre[STACK_SIZE];
	int data[STACK_SIZE];
	int i,temp,n;
	float x,y,res;
	Stack Stack2;
	CreateStack(&Stack2);
	printf("enter the expression: ");
	gets(expre);
	for(i=0;i<strlen(expre);i++){
		if(isdigit(expre[i])){
			PushStack(&Stack2,expre[i]);
		}
		
		switch(expre[i]){  
			case '+':                     //如果识别到运算符+
			    x=PopStack(&Stack2,x); //出栈到运算符前一位 
			    y=PopStack(&Stack2,y); //出栈到运算符前两位 
				x = x - 48;
			    y = y - 48;      //将ASCII值转为输入的数值
			    res = x + y;                 //运算结果替换运算符
			    expre[i] = x + y +48;     //将结果重新转为ASCII值 
			    PushStack(&Stack2,res);  //计算结果的ASCII值入栈 
			    break;
			case '-':                     //后续步骤解释与+运算类似 
			    x=PopStack(&Stack2,y);
			    y=PopStack(&Stack2,x); //减法运算不需要进行ASCII值的转化 
			    res = y - x;
			    PushStack(&Stack2,res);
			    break;
			case '*':
			    x=PopStack(&Stack2,x);
			    y=PopStack(&Stack2,y);
			    x = x - 48;
			    y = y - 48;
			    res = x * y;
			    res = res + 48;
			    PushStack(&Stack2,res);
			    break;
			case '/':
			    x=PopStack(&Stack2,x);
			    y=PopStack(&Stack2,y);
			    x = x - 48;
			    y = y - 48;
			    res = y / x;
			    PushStack(&Stack2,res);
			    break; 
			case '^':
				x=PopStack(&Stack2,x);
			    y=PopStack(&Stack2,y);
			    x = x - 48;
			    y = y - 48;
			    expre[i] = pow(y,x);
			    PushStack(&Stack2,res);
			    res = expre[i];
			    break;
	    }
    }
    return res;
}

int main(){
	float result;
	result = Culculate();
	printf("%f",result);
	return 0;
}
