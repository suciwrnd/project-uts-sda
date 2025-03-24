#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX][MAX];
char infix[MAX], postfix[MAX], prefix[MAX];
int top = -1;

int space(char c) {
    return (c == ' ' || c == '\t');
}
void push(char *c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    strcpy(stack[++top], c);
}

char *pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isEmpty() {
    return (top == -1);
}

//mengatur urutan operasi
int precedence(char a) {
    return (a == '+' || a == '-') ? 1 : (a == '*' || a == '/') ? 2 : (a == '^') ? 3 : 0;
    }

// Fungsi untuk membalik string
void reverseString(char *str) {
    int i, j;
    char temp;
    int len = strlen(str);
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

//fungsi infix to postfix
void intopost() {
    int i, j = 0;
    char simbol, next;
    top = -1; // Reset stack

    for (i = 0; i < strlen(infix); i++) {
        simbol = infix[i];

        if (!space(simbol)) {
            switch (simbol) {
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
    printf("Hasil postfix : \n%s\n", postfix);
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

// fungsi infix ke prefix
void InToPre(char *infix, char *prefix) {
    char stack[MAX];
    int top = -1, j = 0;
    reverseString(infix);
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) prefix[j++] = infix[i];
        else if (infix[i] == ')') stack[++top] = infix[i];
        else if (infix[i] == '(') while (top != -1 && stack[top] != ')') prefix[j++] = stack[top--];
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) prefix[j++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    while (top != -1) prefix[j++] = stack[top--];
    prefix[j] = '\0';
    reverseString(prefix);
}

// fungsi prefix ke postfix
void PreToPost(char *prefix, char *postfix) {
    char stack[MAX][MAX];
    int top = -1, len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            char op[2] = {prefix[i], '\0'};
            strcpy(stack[++top], op);
        } else {
            char op1[MAX], op2[MAX], res[MAX];
            strcpy(op1, stack[top--]);
            strcpy(op2, stack[top--]);
            sprintf(res, "%s%s%c", op1, op2, prefix[i]);
            strcpy(stack[++top], res);
        }
    }
    strcpy(postfix, stack[top]);
}

// postfix ke prefix
void PostToPre(char *postfix, char *prefix) {
    char stack[MAX][MAX];
    int top = -1, len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        if (isalnum(postfix[i])) {
            char op[2] = {postfix[i], '\0'};
            strcpy(stack[++top], op);
        } else {
            char op1[MAX], op2[MAX], res[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);
            sprintf(res, "%c%s%s", postfix[i], op1, op2);
            strcpy(stack[++top], res);
        }
    }
    strcpy(prefix, stack[top]);
}

// Fungsi untuk menunggu user menekan enter sebelum kembali ke menu
void pressEnterToContinue() {
    printf("\nsilahkan tekan enter untuk kembali ke menu.");
    getchar(); // Menunggu input enter
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
          printf("Pilih Konversi (1/2/3/4/5/6/7) : ");
          scanf("%d", &pilihan);
          getchar(); //menghilangkan newline dari buffer
switch (pilihan) {
            case 1:
                printf("\n--Konversi infix ke postfix--\n");
                printf("Masukkan ekspresi infix: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0'; // Hapus newline
                intopost();
                printf("Ekspresi postfix: %s\n", postfix);
                pressEnterToContinue();
                break;
            case 2:
                printf("\n--Konversi postfix ke infix--\n");
                printf("Masukkan ekspresi postfix: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0'; 
                posttoin();
                printf("Ekspresi infix: %s\n", infix);
                pressEnterToContinue();
                break;
            case 3:
                printf("\n--Konversi prefix ke infix--\n");
                printf("Masukkan ekspresi prefix: ");
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = '\0'; 
                pretoin();
                printf("Ekspresi infix: %s\n", infix);
                pressEnterToContinue();
                break;
            case 4:
                printf("\n--Konversi infix ke prefix--\n");
                printf("Masukkan ekspresi infix: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0'; // Hapus newline
                InToPre(infix, prefix);
                printf("Ekspresi Prefix: %s\n", prefix);
                pressEnterToContinue();
                break;
            case 5:
                printf("\n--Konversi prefix ke postfix--\n");
                printf("Masukkan ekspresi prefix: ");
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = '\0'; 
                PreToPost(prefix, postfix);
                printf("Ekspresi Postfix: %s\n", postfix);
                pressEnterToContinue();
                break;
            case 6:
                printf("\n--Konversi postfix ke prefix--\n");
                printf("Masukkan ekspresi postfix: ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0'; 
                PostToPre(postfix, prefix);
                printf("Ekspresi Prefix: %s\n", prefix);
                pressEnterToContinue();
                break;
            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    }
    return 0;
}
