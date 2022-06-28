#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Имеются два упорядоченных кольца (одно- или двунаправленное),
// в которых могут быть одинаковые элементы. Объединить оба кольца
// в одно упорядоченное кольцо, исключив повторяющиеся элементы

struct list{
    int value;
    struct list* next;
    struct list* prev;
};

void init(struct list* head, int amount){
    struct list* ptr = head;
    int value = -1;
    fflush(stdin);
    printf("Создание нового кольца\n");
    printf("Введите число\n");
    while (!scanf("%d", &value)) {
        fflush(stdin);
        printf("Ошибка ввода!\n");
    }
    head -> value = value;
    for (int i = 0; i < amount - 1; ++i) {
        struct list* ptr1 = (struct list*) malloc(sizeof(struct list));
        fflush(stdin);
        printf("Введите число\n");
        while (!scanf("%d", &value)){
            fflush(stdin);
            printf("Ошибка ввода!\n");
        }
        ptr1 -> value = value;
        ptr -> next = ptr1;
        ptr = ptr1;
    }
    ptr -> next = head;
}

void add(struct list* head, int amount, struct list* node){
    if(head -> next == NULL){
        head -> value = node -> value;
        head -> next = head;
    } else {
        struct list* ptr = head;
        for (int i = 0; i < amount - 1; ++i) {
            ptr = ptr -> next;
        }
        ptr -> next = (struct list*) malloc(sizeof(struct list));
        ptr -> next -> value = node -> value;
        ptr -> next -> next = head;
    }
}

void output(struct list* head, int amount){
    struct list* ptr = head;
    for (int i = 0; i < amount; ++i) {
        printf("%d ", ptr -> value);
        ptr = ptr -> next;
    }
    printf("\n");
}

int getSize(){
    int amount = -1;
    while(amount <= 0){
        while (!scanf("%d", &amount)){
            fflush(stdin);
            printf("Ошибка ввода\n");
        }
        if (amount < 0){
            printf("Количество не может быть отрицательным числом или нулем\n");
        }
    }
    return amount;
}

int unite(struct list* mainHead, struct list* head1, struct list* head2, int amount1, int amount2){
    struct list *ptr1 = head1;
    struct list *ptr2 = head2;
    struct list *ptr3 = mainHead;
    int previousValue = -INT32_MAX;
    int amount = 0, ind1 = 0, ind2 = 0;
    for (int i = 0; i < amount1 + amount2; ++i) {
        while (ptr1 -> value == previousValue && ind1 < amount1){
            ptr1 = ptr1 -> next;
            ind1++;
        }
        while (ptr2 -> value == previousValue && ind2 < amount2){
            ptr2 = ptr2 -> next;
            ind2++;
        }
        if (ind1 < amount1 && ind2 < amount2){
            if (ptr1 -> value < ptr2 -> value && previousValue != ptr1 -> value){
                add(ptr3, amount, ptr1);
                previousValue = ptr1 -> value;
                amount++, ind1++;
                ptr1 = ptr1 -> next;
            } else if (ptr1 -> value > ptr2 -> value && previousValue != ptr1 -> value){
                add(ptr3, amount, ptr2);
                previousValue = ptr2 -> value;
                amount++, ind2++;
                ptr2 = ptr2 -> next;
            } else if (ptr1 -> value == ptr2 -> value && previousValue != ptr1 -> value){
                add(ptr3, amount, ptr1);
                previousValue = ptr1 -> value;
                amount++, ind1++, ind2++;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
        } else if (ind2 >= amount2 && ind1 < amount1){
            add(ptr3, amount, ptr1);
            previousValue = ptr1 -> value;
            ptr1 = ptr1 -> next;
            ind1++, amount++;
        } else if (ind1 >= amount1 && ind2 < amount2){
            add(ptr3, amount, ptr2);
            previousValue = ptr2 -> value;
            ind2++, amount++;
            ptr2 = ptr2 -> next;
        }
    }
    return amount;
}

void twoWayRing(struct list* head, int amount){
    struct list* ptr = head;
    for (int i = 0; i < amount; ++i) {
        ptr -> next -> prev = ptr;
        ptr = ptr -> next;
    }
    ptr = head -> prev;
    printf("reversed dir: ");
    for (int i = 0; i < amount; ++i) {
        printf("%d ", ptr -> value);
        ptr = ptr -> prev;
    }
    printf("\n");
    ptr = head;
    printf("straight dir: ");
    for (int i = 0; i < amount; ++i) {
        printf("%d ", ptr -> value);
        ptr = ptr -> next;
    }
}

int main() {
    struct list *head1 = (struct list*) malloc(sizeof(struct list));
    struct list *head2 = (struct list*) malloc(sizeof(struct list));
    struct list *mainHead = (struct list*) malloc(sizeof(struct list));
    mainHead -> next = NULL;
    printf("Введите количество чисел в 1 кольце\n");
    int amount1 = getSize();
    init(head1, amount1);
    printf("Введите количество чисел в 2 кольце\n");
    int amount2 = getSize();
    init(head2, amount2);
    printf("\nПервое кольцо\n");
    output(head1, amount1);
    struct list *ptr1 = head1;
    printf("Доказательство кольца\n");
    for (int i = 0; i < 50; ++i) {
        printf("%d ", ptr1 -> value);
        ptr1 = ptr1 -> next;
    }
    printf("\nВторое кольцо\n");
    output(head2, amount2);
    struct list *ptr2 = head2;
    printf("Доказательство кольца\n");
    for (int i = 0; i < 50; ++i) {
        printf("%d ", ptr2 -> value);
        ptr2 = ptr2 -> next;
    }
    printf("\nТретье кольцо\n");
    int amount = unite(mainHead, head1, head2, amount1, amount2);
    printf("amount %d\n", amount);
    output(mainHead, amount);
    struct list *ptr = mainHead;
    printf("Доказательство кольца\n");
    for (int i = 0; i < 50; ++i) {
        printf("%d ", ptr -> value);
        ptr = ptr -> next;
    }
    printf("\n");
    twoWayRing(mainHead, amount);
    return 0;
}