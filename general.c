#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define STACK_SIZE 100
#define STACK_INCREMENT 10

typedef unsigned Element;
typedef enum { ERROR = 0, OK = 1 }Status;
typedef enum { NO = 0, YES = 1 }YesNo;

typedef struct{
	void** pTop;
	void** pBase;
	int size; 
}Stack;

void TypeInAndTransport(char expression[]);
/*功能：录入并且转化为逆波兰式
 *参数：字符串Expression
 *返回：空 
 *注意事项：无 
 */ 
int SaveInStack(char* character, Stack* pstack);
/*功能：逆波兰式转化过程入栈
 *参数：当前读取字符character，栈的地址
 *返回：正常运行返回1，否则返回0
 *注意事项：需要用到头文件<stdlib.h>
 *存在的问题：没有对空间分配失败时的情况进行操作 
 */ 
int ConstructStack(Stack* pstack);
/*功能：建立栈
 *参数：栈的地址
 *返回：创建成功返回1，否则返回0
 *注意事项：需要用到头文件<stdio.h><stdlib.h> 
 *存在的问题：没有对空间分配失败时的情况进行操作 
 */
int ComparePriority(char character, char expression[], int i, Stack* pstack);
/*功能：比较优先级的大小
 *参数：当前读取字符character，逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：需要出栈操作返回1，否则返回0
 *注意事项：无
 */ 
int Priority(char x);
/*功能：获取优先级
 *参数：运算符x
 *返回：乘方返回3，乘除返回2，加减返回1，错误返回-1
 *注意事项：无 
 */ 
void PopFromStack(char expression[], int i, Stack* pstack);
/*功能：进行一次出栈操作
 *参数：逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：空
 *注意事项：无
 *存在的问题：当栈为空的时候没有终止程序并报错 
 */ 
int PopAllDatas(char expression[], int i, Stack* pstack);
/*功能：将栈中剩余数据全部出栈
 *参数：逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：i
 *注意事项：无
 */ 

/*功能：录入并且转化为逆波兰式
 *参数：字符串Expression
 *返回：空 
 *注意事项：无 
 */

Status CreateStack(Stack* pSt);
/*功能：创建一个通用栈。 
 *输入参数：Stack2。
 *作用方式：给栈分配内存并初始化栈。
 *注意事项：需要# #include <stdio.h>和 typedef struct stack。
 */ 
Status ClearStack(Stack* pSt);
/*功能：对栈进行清空。
 *输入参数 ：Stack2。
 *作用方式：令栈顶等于栈底。
 *注意事项：需要# #include <stdio.h>，且在创建栈的函数中已经完成一次清空操作。
 */ 
YesNo IsStackEmpty(Stack* pSt);
/*功能：判断栈是否为空栈。
 *输入参数：Stack2.
 *作用方式：判断栈顶是否等于栈底。
 *注意事项：需要# #include <stdio.h>
 */ 
void PushStack(Stack* pSt, double* num);
/*功能：将一双精度浮点数入栈。
 *输入参数：Stack2和需要入栈的双精度浮点数。
 *作用方式：栈顶指针指向该浮点数，栈顶指针增加，栈长度增加。
 *注意事项：需要# #include <stdio.h>,double的处理时间略长但更精准。
 */ 
void PopStack(Stack* pSt, double* pNum);
/*功能：将一双精度浮点数入栈。
 *输入参数：Stack2和用于存储出栈数的双精度浮点数。
 *返回值：需要出栈的数的数值。
 *注意事项：需要# #include <stdio.h>，double的处理时间略长但更精准。
 */ 
double TransToFloat(char treat[]);
/*功能：将运算数组中读到的数转化为浮点数以便入栈，辅助实现逆波兰式到运算结果的运算。
 *输入参数：存储数值的数组treat。
 *返回值：数组中存储数的数值。
 *注意事项：需要# #include <stdio.h>，#include <string.h>，#include <stdlib.h>。 
 */ 
double Calculate(char expre[]);
/*功能：实现逆波兰式到最终结果的运算。
 *输入参数：转化得到的逆波兰表达式。
 *返回值：最终运算的结果。
 *注意事项：需要# #include <stdio.h>，#include <string.h>，#include <math.h>。 
 */ 

void TypeInAndTransport(char Expression[]) {
	Stack stack;
	char character[1000];
	int i = 0, j = 0,t;
	ConstructStack(&stack);
	gets(character);
	while (1) {
		if (character[j] == 0)
			break;
		if (character[j] <= '9' && character[j] >= '0') {
			Expression[i] = character[j];
			i++;
		}
		else if (character[j] == '.') {
			Expression[i] = character[j];
			i++;
		}
		else switch (character[j]) {
		case '+':
		case '-':
		case '/':
		case '*':
		case '^':	Expression[i] = ',';
			i++;
			for (; ComparePriority(character[j], Expression, i, &stack) == 1;)
				i++;
			break;
		case '(':	SaveInStack(&character[j], &stack);
			break;
		case ')':	Expression[i]=',';
			i++;
			for (; Expression[i - 1] != '(';) {
				PopFromStack(Expression, i, &stack);
				i++;
			}
			i--;
			Expression[i] = 0;
			break;
		default:	break;
		}
		j++;
		if (character[j] == '\n' || character[j] == '\0')
			break;
	}
	i=PopAllDatas(Expression, i, &stack);
	for(j=i-1;;j--){
		if(Expression[j]>='0'&&Expression[j]<='9')
		break;
		SaveInStack(&Expression[j],&stack);
	}
	j+=2;
	Expression[j-1]=',';
	i=PopAllDatas(Expression,j,&stack);
	Expression[i]='\0';
}
/*功能：逆波兰式转化过程入栈
 *参数：当前读取字符character，栈的地址
 *返回：正常运行返回1，否则返回0
 *注意事项：需要用到头文件<stdlib.h>
 *存在的问题：没有对空间分配失败时的情况进行操作 
 */
int SaveInStack(char* character, Stack* pstack) {
	if ((pstack->pTop - pstack->pBase) >= pstack->size) {
		pstack->pBase = (void*)realloc(pstack->pBase, pstack->size + STACK_INCREMENT);
		if (pstack->pBase == NULL) {
			return 0;
		}
		pstack->pTop = pstack->pBase + pstack->size;
		pstack->size += STACK_INCREMENT;
	}
	*(char *)(pstack->pTop) = *character;
	pstack->pTop++;
	return 1;
}
/*功能：建立栈
 *参数：栈的地址
 *返回：创建成功返回1，否则返回0
 *注意事项：需要用到头文件<stdio.h><stdlib.h> 
 *存在的问题：没有对空间分配失败时的情况进行操作 
 */
int ConstructStack(Stack* pstack) {
	pstack->pBase = (void*)malloc(STACK_SIZE * sizeof(double));
	if (pstack->pBase == NULL) {
		return 0;
	}
	pstack->pTop = pstack->pBase;
	pstack->size = STACK_SIZE;
	return 1;
}
/*功能：比较优先级的大小
 *参数：当前读取字符character，逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：需要出栈操作返回1，否则返回0
 *注意事项：无
 */
int ComparePriority(char character, char expression[], int i, Stack* pstack) { 
	if (pstack->pTop == pstack->pBase) {
		SaveInStack(&character, pstack);
		return 0;
	}
	else pstack->pTop--;
	if (Priority(character) <= Priority(*(char*)(pstack->pTop))) { 
		pstack->pTop++;
		PopFromStack(expression, i, pstack);
		return 1;
	}
	else{
		pstack->pTop++;
		SaveInStack(&character, pstack);
		return 0;
	}
}
/*功能：获取优先级
 *参数：运算符x
 *返回：乘方返回3，乘除返回2，加减返回1，错误返回-1
 *注意事项：无 
 */
int Priority(char x) {
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
/*功能：进行一次出栈操作
 *参数：逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：空
 *注意事项：无
 *存在的问题：当栈为空的时候没有终止程序并报错 
 */
void PopFromStack(char expression[], int i, Stack* pstack) {
	if (pstack->pTop == pstack->pBase)
		return;
	pstack->pTop--;
	expression[i] = *(char *)(pstack->pTop);
	return;
}
/*功能：将栈中剩余数据全部出栈
 *参数：逆波兰式expression，逆波兰式脚标i，栈的地址
 *返回：i
 *注意事项：无
 */
int PopAllDatas(char expression[], int i, Stack* pstack) {
	for (; pstack->pTop != pstack->pBase; i++)
	{
		pstack->pTop--;
		expression[i] = *(char *)(pstack->pTop);
	}
	return i;
}

//创建栈 
Status CreateStack(Stack* pSt) {
	pSt->pBase = (void*)malloc(STACK_SIZE * sizeof(double));
	if (pSt->pBase == NULL) {
		return ERROR;
	}
	pSt->pTop = pSt->pBase;
	return OK;
}

//清空栈 
Status ClearStack(Stack* pSt) {
	pSt->pTop = pSt->pBase;
	return OK;
}

//判断栈空 
YesNo IsStackEmpty(Stack* pSt) {
	if (pSt->pTop == pSt->pBase) {
		return YES;
	}
	else {
		return NO;
	}
}

//外部数字入栈 
void PushStack(Stack* pSt, double* num) {
	if (pSt->pBase == NULL) {
			return;
	}
	*(double *)(pSt->pTop) = *num;
	pSt->pTop++;
}

//栈顶数字出站 
void PopStack(Stack* pSt, double* pNum) {
	if (pSt->pTop == pSt->pBase) {
		return;
	}
	else {
		(double *)pSt->pTop--;
		*pNum = *(double *)(pSt->pTop);
	}
	return;
}

//转化为浮点数 
double TransToFloat(char treat[]) {
	double x = 0, y = 0, m;
	int i, j;
	for (j = 0; j <= strlen(treat); j++)
		if (treat[j] == '.')
			break;
	for (i = 0; i < j; i++) {
		if (treat[i] == '\0')
			return x;
		x = x * 10 + (float)(treat[i] - 48);
	}
	for (i = (strlen(treat) - 1); i > j; i--)
		y = y / 10 + (float)(treat[i] - 48) / 10;
	m = x + y;
	return m;
}

double Calculate(char expre[]) {
	char treat[STACK_SIZE] = { 0 };
	int i, n;
	n = 0;
	double x=0, y=0, z, res=0;
	Stack Stack2;
	CreateStack(&Stack2);
	for (i = 0; i < strlen(expre); i++) {
		if (expre[i] == '.' || (expre[i] >= '0' && expre[i] <= '9')) {
			treat[n] = expre[i];
			n++;
		}
		switch (expre[i]) {
		case '+':                     //如果识别到运算符+
			PopStack(&Stack2, &x); //出栈到运算符前一位 
			PopStack(&Stack2, &y); //将ASCII值转为输入的数值
			res = x + y;              //将结果重新转为ASCII值 
			PushStack(&Stack2, &res);  //计算结果的ASCII值入栈 
			break;
		case '-':                     //后续步骤解释与+运算类似 
			PopStack(&Stack2, &x);
			PopStack(&Stack2, &y); //减法运算不需要进行ASCII值的转化 
			res = y - x;
			PushStack(&Stack2, &res);
			break;
		case '*':
			PopStack(&Stack2, &x);
			PopStack(&Stack2, &y);
			res = x * y;
			PushStack(&Stack2, &res);
			break;
		case '/':
			PopStack(&Stack2, &x);
			PopStack(&Stack2, &y);
			res = y / x;
			PushStack(&Stack2, &res);
			break;
		case '^':
			PopStack(&Stack2, &x);
			PopStack(&Stack2, &y);
			res = pow(y, x);
			PushStack(&Stack2, &res);
			break;
		case ',':                     //得到的逆波兰式中的每两个数之间由逗号隔开 
			z = TransToFloat(treat);  //存储转化后的值 
			PushStack(&Stack2, &z);
			memset(treat,0, sizeof(treat));//treat数组清空 
			n = 0;                    //n赋0，重新开始统计数组长度 
			break;
		}
	}
	return res;
}

int main() {
	double result;
	char treat[STACK_SIZE];
	printf("Enter the expre: ");
	TypeInAndTransport(treat);
	puts(treat);
	result = Calculate(treat);
	printf("%lf", result);
	return 0;
}
