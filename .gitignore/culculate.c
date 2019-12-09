#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <math.h>
#define STACK_SIZE 100
#define STACK_INCREMENT 10

typedef unsigned StackElement;

typedef struct {
	StackElement* pBase;
	StackElement* pTop;
	int size;
}Stack1;

typedef enum{ERROR=0,OK=1}Status;
typedef enum{NO=0,YES=1}YesNo;

typedef struct stack{
   char data[STACK_SIZE];
   float num;
   int pTop;
   int pBase;
}Stack;

Stack * CreateStack();
Status ClearStack(Stack* pSt);
YesNo IsStackEmpty(Stack* pSt);
void PushStack(Stack* pSt,int num);
void PopStack(Stack* pSt,int num);

//转化成逆波兰式的主体函数 
void TypeInAndTransport(char Expression[]);
//数据入栈的函数 
int SaveInStack(char character, Stack1* pstack);
//创建栈的函数 
int ConstructStack(Stack1* pstack);
//比较运算符优先级的函数 
int ComparePriority(char character, char expression[], int i, Stack1* pstack);
//表示优先级大小的函数 
int Priority(char x);
//数据出栈的函数 
void PopFromStack(char expression[], int i, Stack1* pstack);
//将数据全部出栈的函数 
void PopAllDatas(char expression[], int i, Stack1* pstack);

void TypeInAndTransport(char Expression[]){
	Stack1 stack;
	char character;
	int i;
	ConstructStack(&stack);
	for (i = 0;;){ 
		character = getchar();
		//判断录入的字符是
		//数字还是运算符 
		switch (character){
			//当录入的是数字的时候，
			//直接放入表达式 
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':	Expression[i] = character;
			i++;
			break;
			//当录入的是运算符的时候
			//判断优先级 
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			//比较优先级，返回值为1则继续比较 
			for (; ComparePriority(character, Expression, i, &stack) == 1;)
				i++;
			break;
			//当录入的是左括号的时候
			//直接入栈 
		case '(':	SaveInStack(character, &stack);
			break;
			//当录入的是右括号的时候
			//持续出栈直到左括号出栈 
		case ')':	for (; Expression[i - 1] != '(';){
			PopFromStack(Expression, i, &stack);
			i++;
		}
				//清除左括号 
				i--;
				Expression[i] = 0;
				break;
		default:	break;
		}
		//判断录入结束 
		if (character == '\n')
			break;
	}
	//结束后所有数据出栈 
	PopAllDatas(Expression, i, &stack);
}

int SaveInStack(char character, Stack1* pstack){
	//当超过栈的上限的时候扩大栈 
	if ((pstack->pTop - pstack->pBase) >= pstack->size){
		pstack->pBase = (StackElement*)realloc(pstack->pBase, pstack->size + STACK_INCREMENT);
		if (pstack->pBase == NULL){
			return 0;
		}
		pstack->pTop = pstack->pBase + pstack->size;
		pstack->size += STACK_INCREMENT;
	}
	//数据入栈 
	*(pstack->pTop) = character;
	pstack->pTop++;
	//表示运行成功 
	return 1;
}

int ConstructStack(Stack1* pstack){
	//获取栈的地址 
	pstack->pBase = (StackElement*)malloc(STACK_SIZE * sizeof(StackElement));
	if (pstack->pBase == NULL){
		return 0;
	}
	//栈内数据个数归零 
	pstack->pTop = pstack->pBase;
	pstack->size = STACK_SIZE;
	return 1;
}

int ComparePriority(char character, char expression[], int i, Stack1* pstack){
	//如果优先级相同，入栈 
	if (pstack->pTop == pstack->pBase){
		SaveInStack(character, pstack);
		return 0;
	}
	//栈顶为空，
	//判断最上数据
	//必须将指针下移 
	else pstack->pTop--;
	//如果优先级比栈顶小，弹出栈顶数据
	//返回1 
	if (Priority(character) < Priority(*(pstack->pTop))){
		//判断完成
		//指针归位 
		pstack->pTop++;
		PopFromStack(expression, i, pstack);
		SaveInStack(character, pstack);
		return 1;
	}
	//如果优先级比栈顶大，入栈 
	else if (Priority(character) > Priority(*(pstack->pTop))){
		//指针归位 
		pstack->pTop++;
		SaveInStack(character, pstack);
		return 0;
	}
	//如果优先级与栈顶相同，弹出栈顶数据
	//返回1 
	else if (Priority(character) == Priority(*(pstack->pTop))){
		//指针归位 
		pstack->pTop++;
		PopFromStack(expression, i, pstack);
		return 1;
	}
}

int Priority(char x){
	switch (x)
	{
	case '+':	case '-':
		return 1;
	case '*':	case '/':
		return 2;
	case '^':
		return 3;
	default:return -1;
	}
}

void PopFromStack(char expression[], int i, Stack1* pstack){
	if (pstack->pTop == pstack->pBase)
		return;
	pstack->pTop--;
	expression[i] = *(pstack->pTop);
	return;
}

void PopAllDatas(char expression[], int i, Stack1* pstack){
	//循环到栈数据数量为空 
	for (; pstack->pTop != pstack->pBase; i++){
		pstack->pTop--;
		expression[i] = *(pstack->pTop);
	}
	return;
}

//创建栈 
Stack * CreateStack(){
	Stack * pSt = (Stack*)malloc(sizeof(Stack));
	if(pSt == NULL){
		return NULL;
	pSt->pTop = pSt->pBase = 0;
	return pSt;                      //此栈的创建需要在主函数中实现 
	}
}

//将栈清空 
Status ClearStack(Stack* pSt){
    pSt->pTop=pSt->pBase;
    return OK;
}

//判断是否为空栈 
YesNo IsStackEmpty(Stack* pSt){
    if(pSt->pTop==pSt->pBase){
        return YES;
    }
    else {
        return NO;
    }
}
//外部数字入栈 
void PushStack(Stack* pSt,int num){
	pSt->pTop = num;
	pSt->pTop++;
}

//栈顶数字出站 
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

int main(){
	char expre[STACK_SIZE],data[STACK_SIZE];
	int i,temp,n;
	float res,result,x,y;
	Stack * pSt;
	pSt = CreateStack();                  //创建栈 
	printf("enter the expression: ");     //允许用户输入常规顺序的算式 
	TypeInAndTransport(expre);            //得到经过转换的逆波兰式 
	for(i=0;i<strlen(expre);i++){
		if(isdigit(expre[i])){            //判断是否为数字 
			PushStack(pSt,expre[i]);      //如果是数字，入栈 
		}
		
		switch(expre[i]){  
			case '+':                     //如果识别到运算符+
			    PopStack(pSt,expre[i-1]); //出栈到运算符前一位 
			    PopStack(pSt,expre[i-2]); //出栈到运算符前两位 
			    x = expre[i-1] - 48;
			    y = expre[i-2] - 48;      //将ASCII值转为输入的数值 
			    expre[i] = x + y;         //运算结果替换运算符 
			    res = expre[i];
			    expre[i] = x + y +48;     //将结果重新转为ASCII值 
			    PushStack(pSt,expre[i]);  //计算结果的ASCII值入栈 
			    break;
			case '-':                     //后续步骤解释与+运算类似 
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]); //减法运算不需要进行ASCII值的转化 
			    expre[i] = expre[i-2] - expre[i-1];
			    res = expre[i];
			    PushStack(pSt,expre[i]);
			    break;
			case '*':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    x = expre[i-1] - 48;
			    y = expre[i-2] - 48;
			    res = x * y;
			    expre[i] = res + 48;
			    PushStack(pSt,expre[i]);
			    break;
			case '/':
			    PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    x = expre[i-1] - 48;
			    y = expre[i-2] - 48;
			    res = y / x;
			    PushStack(pSt,expre[i]);
			    break; 
			case '^':
				PopStack(pSt,expre[i-1]);
			    PopStack(pSt,expre[i-2]);
			    x = expre[i-1] - 48;
			    y = expre[i-2] - 48;
			    expre[i] = pow(y,x);
			    PushStack(pSt,expre[i]);
			    res = expre[i];
			    break;
	    }
    }
    result = res;
	printf("%f",result);                  //输出运算结果 
	return 0;
}
