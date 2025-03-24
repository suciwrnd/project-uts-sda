#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX][MAX];
char infix[MAX], postfix[MAX], prefix[MAX];
int top = -1;

//fungsi infix to postfix
void intopost(){
    int i, j = 0;
    char simbol, next;
    top = -1;
    for (i = 0; i < strlen(infix); i++){
        simbol = infix[i];
        if (!space(simbol){
            switch (simbol){
                case '(':
                    push(&simbol);
                    break;
                case ')':
                    while (!isEmpty() && (next = *pop()) != '(')
                        postfix[j++] = next;
                    break;
                case '+': case '-': case '*': case '/': case '^':
                    while (!isEmpty() && precedence(stack[top][0]) >= precedence(simbol))
                        postfix[j++] = *pop();
                    push(&simbol);
                    break;
                default:
                    postfix[j++] = simbol;
                    break;
            }
        }
    }
    while (!isEmpty())
        postfix[j++] = *pop();
        postfix[j] = '\0';
        printf("Hasil postfix :\n%s\n", postfix);
}


//fungsi postfix ke infix
void posttoin(){
    char simbol, op1[MAX], op2[MAX], expr[MAX];
    top = -1;

    for (int i = 0; i < strlen(postfix); i++){
        simbol = postfix[i];
        if (isalnum(simbol)){
            char temp[2] = {simbol, '\0'};
            push(temp);
        }
        else{
          if (!isEmpty()) strcpy(op2, pop());
          if (!isEmpty()) strcpy(op1, pop());

          snprintf(expr, MAX, "(%s%c%s)", op1, simbol, op2);
          push(expr);
        }
    }
    printf("Hasil Infix :\n%s\n", pop());
}


//fungsi prefix ke infix
void pretoin(){
    char simbol, op1[MAX], op2[MAX], expr[MAX];
    top = -1;
    for (int i = strlen(prefix) -1; i >= 0; i--){
        simbol = prefix[i];
        if (isalnum(simbol)){
            char temp[2] = {simbol, '\0'};
            push(temp);
        }
        else{
            if (!isEmpty()) strcpy(op1, pop());
            if (!isEmpty()) strcpy(op2, pop());
            snprintf(expr, MAX, "(%s%c%s)", op1, simbol, op2);
            push(expr);
        }
    }
    printf("Hasil Infix :\n%s\n", pop());
}


int main(){
      int pilihan;
      while(1){
          //tampilkan menu
          printf("\n=====KONVERSI EKSPRESI ARITMATIKA=====");
          printf("\nSilahkan pilih konversi:\n");
          printf("1. Infix ke Postfix\n");
          printf("2. Postfix ke Infix\n");
          printf("3. Prefix ke Infix\n");
          printf("4. Infix ke Prefix\n");
          printf("5. Prefix ke Postfix\n");
          printf("6. Postfix ke Prefix\n");
          printf("7. Keluar\n");
          printf("Pilih Konversi (1/2/3/4/5/6/7) : ";
          scanf("%d", &pilihan);
          getchar(); //menghilangkan newline dari buffer


      


