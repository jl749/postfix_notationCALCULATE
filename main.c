#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 30
#define MAX_EXPR_SIZE 30

/*in stack priority && in coming priority*/
int isp[]={0,10,4,4,5,5,5,0}; //(,),+,-,*,/,%,eos
int icp[]={20,10,4,4,5,5,5,0}; //( treated differently when it is in stack and when it is a token

/*represent priority*/
typedef enum{
    lparen,rparen,
    plus,minus,times,divide,mode,
    eos,
    operand
}PRECEDENCE;

//char expression[MAX_EXPR_SIZE]; //string
PRECEDENCE stack[MAX_STACK_SIZE]; //operators only
int top=-1;

void push(PRECEDENCE e){
    if(top>=MAX_STACK_SIZE-1){
        puts("stack full");
        return;
    }
    stack[++top]=e; // top++ , stack[top]=e;
    //puts("pushed");
}
PRECEDENCE* pop(){
    if(top<0){
        puts("stack empty");
        return;
    }
    //puts("popped");
    return &stack[top--]; //tmp=stack[top] , top-- , return tmp
}
PRECEDENCE peek(){
    if(top<0){
        puts("stack empty");
        return;
    }
    return stack[top];
}

PRECEDENCE mapPrecedence(char* token){
    switch(*token){
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
        case '%': return 6;
        //case ' ': return 7; //eos
        default: return 8; //operand
    }
}
char mapToken(PRECEDENCE* precedence){
    switch(*precedence){
        case 0: return;
        case 1: return;
        case 2: return '+';
        case 3: return '-';
        case 4: return '*';
        case 5: return '/';
        case 6: return '%';
    }
}

char* toPostfix(char* input){
    char* postfix=(char*)malloc(MAX_EXPR_SIZE*sizeof(char)); //to save postfix expression
    int n=0;

    memset(stack,NULL,MAX_STACK_SIZE);
    push(eos);

    int i;
    for(i=0;i<strlen(input);i++){
        if(mapPrecedence(input[i])==operand)
            postfix[n++]=input[i];
        else if(input[i]==')'){
            while(peek()!='('){
                postfix[n++]=mapToken(pop());
            }
            pop();
        }
        else if(icp[mapPrecedence(input[i])]>isp[peek()]) //convert char to corresponding Precedence value and compare with stack[top]'s Precedence
            push(mapPrecedence(input[i]));
        else{
            while(icp[mapPrecedence(input[i])]>isp[peek()] && top>-1){ //'(' treated 0 in isp
                    //trim???
                if(peek()==0) //ignore '('
                    break;
                postfix[n++]=mapToken(pop());
            }
        }
    }

}

int main()
{
    printf("Hello world!\n");
    return 0;
}
