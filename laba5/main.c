#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
    char sign;
    int num;
    struct tree *left, *right;
};

struct stack
{
    char c;
    struct stack* next;
};

char* polish(const char*, struct stack**);
char pop(struct stack**);
struct stack* push(struct stack**, char);
int priority(char);
struct tree* add(struct tree*, char, int);
int calc(struct tree*);
int flag = 1;

int main(){
    struct tree* node = NULL;
    struct stack* elem = NULL;
    char* str;
    int i, number;
    if (!(str = (char*)malloc(50))) {
        puts("Ошибка при работе с памятью!");
        return 0;
    }
    puts("Введите выражение");
    fflush(stdin);
    fgets(str,100,stdin);
    str = polish(str, &elem);
    puts(str);
    i = strlen(str);
    i--;
    while (i >= 0){
        if (*(str + i) == '/' || *(str + i) == '*' || *(str + i) == '-' || *(str + i) == '+'){
            node = add(node, *(str + i), 0);
            i--;
        }
        if (*(str + i) == ' ') i--;

        if (*(str + i) >= '0' && *(str + i) <= '9')
        {
            number = 0; int mn = 1;
            while (*(str + i) >= '0' && *(str + i) <= '9')
            {
                number += (*(str + i) - '0') * mn;
                mn *= 10;
                i--;
            }
            node = add(node, ' ', number);
        }
    }
    printf("Результат вычисления: %d\n", calc(node));
    return 0;
}

char* polish(const char* str, struct stack** node){
    int i = 0, point = 0;
    char* out;
    if (!(out = (char*)malloc(50))) {
        puts("Ошибка при работе с памятью!");
        return 0;
    }
    while (*(str + i) != '\0' && *(str + i) != '='){
        while (*(str + i) == ' ') i++; //propysk probelov
        if (*(str + i) == ')'){
            while ((*node)->c != '(') //esli zakruvaiyshchaya skobka, vutalkivaem iz steka vse elementu do otkruvaiyshchei skobki i samy skobky
                *(out + point++) = pop(node);
            pop(node);
        }
        if (*(str + i) >= '0' && *(str + i) <= '9'){ //esli tsifra - v stroky
            while (*(str + i) >= '0' && *(str + i) <= '9'){
                *(out + point++) = *(str + i);
                i++;
            }
            *(out + point++) = ' ';
            i--;
        }
        if (*(str + i) == '(') { //esli '(' - zapisuvaem ee stek
            *node = push(node, '(');
        }
        if (*(str + i) == '+' || *(str + i) == '-' || *(str + i) == '*' || *(str + i) == '/'){ //esli znak - vutalkivaem iz steka vse elementu s nizshim
            while ((*node != NULL) && (priority((*node)->c) >= priority(*(str + i)))) //prioritetom i zapisuvaem znak v stek
                *(out + point++) = pop(node);
            *node = push(node, *(str + i));
        }
        i++;
    }
    while (*node != NULL) //zapisuvaem v stroky ostavshiesya elementy
        *(out + point++) = pop(node);
    *(out + point) = '\0';
    return out;
}

struct stack* push(struct stack** node, char c){
    struct stack* s;
    s = (struct stack*)malloc(sizeof(struct stack));
    s -> c = c;
    s -> next = *node;
    return s;
}

char pop(struct stack** node){
    char c;
    struct stack* ptr;
    if (!*node) return '\0';
    ptr = *node;
    c = ptr -> c;
    if (ptr -> c == '(' || ptr -> c == '+' || ptr -> c == '-' || ptr -> c == '*' || ptr -> c == '/') {
        *node = ptr -> next;
    }
    else *node = NULL;
    free(ptr);
    return c;
}

int priority(char c){
    switch (c){
        case '*': case '/': return 3;
        case '+': case '-': return 2;
        case ')': return 1;
        default: return 0;
    }
}

struct tree* add(struct tree* node, char symbol, int number){
    if (!node){
        if (!(node = (struct tree*)malloc(sizeof(struct tree)))) {
            puts("Ошибка при работе с памятью!");
            return 0;
        }
        node -> num = number;
        node -> sign = symbol;
        node -> left = node -> right = NULL;
        flag = 1;
        return node;
    }
    if (node -> sign == ' ') { //если записано число, возвращаемся
        return node;
    }
    if (!node -> right){ //запись вправо
        node -> right = add(node -> right, symbol, number);
        return node;
    }
    if (node -> right){
        if (node -> right -> sign != ' ') { //если записано не число, записываем число сюда
            node -> right = add(node -> right, symbol, number);
        } else { //число
            flag = 0;
            node -> left = add(node -> left, symbol, number); //иначе записываем влево
        }
    }
    if (node -> right && flag == 0) {
        node -> left = add(node -> left, symbol, number);
    }
    return node;
}

int calc(struct tree* node){
    if (node){
        if (node -> left) {
            node -> num = calc(node -> left);
        }
        if (node -> right) {
            switch (node -> sign) {
                case '+':
                    node -> num += calc(node -> right);
                    break;
                case '-':
                    node -> num -= calc(node -> right);
                    break;
                case '*':
                    node -> num *= calc(node -> right);
                    break;
                case '/':
                    node -> num /= calc(node -> right);
                    break;
            }
        }
    }
    return node -> num;
}
