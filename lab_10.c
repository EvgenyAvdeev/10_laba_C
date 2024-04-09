#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 2 //1 - первая задача, 2 - вторая

#if n==1

typedef struct Poly {
    int deg;
    int coeff;
    struct Poly* next;  //указатель на следующий элемент списка
}Poly;

Poly* addElem(Poly* head, int coeff, int deg) {  //добавление нового элемента
    Poly* newPoly = (Poly*)malloc(sizeof(Poly));    //создаем элемент списка и добавляем в него значения
    newPoly->coeff = coeff;
    newPoly->deg = deg;
    newPoly->next = NULL;

    if (head == NULL) { //для добавления нулевого элемента
        head = newPoly;
        return head;
    }

    Poly* current = head;
    while (current->next != NULL) {  //двигаемся в конец списка для добавления элемента
        current = current->next;
    }
    current->next = newPoly;
    return head;
}

Poly* create(Poly* L1) {    //создание списка
    printf("Max deg: ");
    int min, max;
    scanf("%d", &max);
    printf("Min deg: ");
    scanf("%d", &min);

    if (min > max) {
        printf("Min > max");
        exit(1);
    }

    int coeff;
    printf("Input coeff: ");
    for (int i = min; i <= max; i++) {
        scanf("%d", &coeff);
        if (coeff == 0) {
            continue;
        }
        L1 = addElem(L1, coeff, i);
    }
    return L1;
}



void print(Poly* L1) {  //вывод многочлена
    int flag = 0;
    Poly* poly = L1;
    while (poly != NULL) {
        if (poly->coeff != 0) {
            flag = 1;
            if (poly->deg == 0) {
                printf("(%d)", poly->coeff);
            }
            else {
                printf("(%d)*x^%d", poly->coeff, poly->deg);
            }
            if (poly->next != NULL) { 
                printf(" + "); 
            }
            poly = poly->next;
        }
        else {
            poly = poly->next;
        }
    }
    if (flag == 0) {
        printf("Poly not exist");
    }
    puts("");
}


int max_deg(Poly* L) {
    int deg;
    while (L->next != NULL) {
        L = L->next;
        if (L->next == NULL) {
            deg = L->deg;
        }
    }
    return deg;
}



Poly* sum(Poly* L1, Poly* L2, Poly* L) {
    Poly* head_1 = L1;
    Poly* head_2 = L2;
    int max_deg_1 = max_deg(L1);
    int max_deg_2 = max_deg(L2);
    while (1) {
        if (L1 != NULL && L1->deg < head_2->deg) {
            L = addElem(L, L1->coeff, L1->deg);
            L1 = L1->next;
        }
        else if (L2 != NULL && L2->deg < head_1->deg) {
            L = addElem(L, L2->coeff, L2->deg);
            L2 = L2->next;
        }
        else if (L1 != NULL && L2 != NULL && L1->deg == L2->deg) {
            L = addElem(L, L1->coeff + L2->coeff, L1->deg);
            L2 = L2->next;
            L1 = L1->next;
        }
        else if (L1 != NULL && L1->deg > max_deg_2) {
            L = addElem(L, L1->coeff, L1->deg);
            L1 = L1->next;
        }
        else if (L2 != NULL && L2->deg > max_deg_1) {
            L = addElem(L, L2->coeff, L2->deg);
            L2 = L2->next;
        }
        if (L1 == NULL && L2 == NULL) {
            break;
        }
    }
    return L;
}






int main() {
    Poly* L1 = NULL, * L2 = NULL, * L = NULL;
    while (1) {
        printf("\nChoise:\n1) Output \n2) Sum poly\n");
        
        int flag;
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            print(L1);
            break;
        case 2:
            L1 = create(L1);
            L2 = create(L2);
            L = sum(L1, L2, L);
            print(L);
            break;
        default:
            printf("ERROR");
            exit(-1);
            break;
        }
    }
    return 0;
}

#elif n==2

typedef struct Word {    //структура элемента списка
    char* word;    //указатель на слово
    struct Word* next;  //указатель на следующий элемент
    struct Word* prev;
} Word;

typedef struct DBLLinked {  //структура, содержащая информацию о списке
    unsigned int size;  //кол-во элементов в списке
    Word* head;
    Word* tail; //указатель на конец списка
} DBLLinked;

DBLLinked* createDBLLinked() {   //создание списка
    DBLLinked* tmp = (DBLLinked*)malloc(sizeof(DBLLinked));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;
}

void popFront(DBLLinked* list)
{
    //printf("\nHELP\n");
    Word* prev;
    void* tmp;
    if (list->head == NULL)
    {
        return NULL;
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head)
    {
        list->head->prev = NULL;
    }
    if (prev == list->tail)
    {
        list->tail = NULL;
    }
    free(prev);
    list->size--;


}

int find_gl(char* word) {
    char gl[] = "aAeEiIoOuUyY";
    for (int i = 0; i < strlen(gl); i++) {
        if (word[0] == gl[i]) {
            return 1;
        }
    }
    return 0;
}

Word* getNth(DBLLinked* list, unsigned int index)
{
    //printf("\nget_N\n");
    Word* tmp = NULL;
    unsigned int i;

    if (index < list->size / 2)
    {
        i = 0;
        tmp = list->head;
        while (tmp && i < index)
        {
            tmp = tmp->next;
            i++;
        }
    }
    else
    {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index)
        {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

void* deleteNth(DBLLinked* list, unsigned int index)
{
    //printf("\ndel_N\n");
    Word* elm = NULL;
    void* tmp = NULL;
    elm = getNth(list, index);
    if (elm == NULL)
    {
        return NULL;
    }
    if (elm->prev)
    {
        elm->prev->next = elm->next;
    }
    if (elm->next)
    {
        elm->next->prev = elm->prev;
    }
    tmp = elm->word;

    if (!elm->prev)
    {
        list->head = elm->next;
    }
    if (!elm->next)
    {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;

    return tmp;
}

void pushBack(DBLLinked* list, char* word) {    //добавление элемента в конец
    Word* tmp = (Word*)malloc(sizeof(Word));

    tmp->word = word;
    tmp->next = NULL;   //изменяем поля элемента
    tmp->prev = list->tail;

    if (list->tail) {   //изменяем указатель в предпоследнем элементе
        list->tail->next = tmp;
    }

    list->tail = tmp;   //изменяем указатель на конец списка

    if (list->head == NULL) {    //если список пустой, то указатель на начало = указатель на этот элемент
        list->head = tmp;
    }

    list->size++;
}

void printDBLLinked(DBLLinked* list) {   //вывод списка
    if (list->size == 0) { 
        printf("Пустой список"); 
        return;
    }

    Word* tmp = list->head; //получаем указатель на первый элемент списка
    while (tmp) {
        printf("%s", (tmp->word));
        tmp = tmp->next;
        if (tmp) { 
            printf(", "); 
        }
    }

}

void deleteDBLLinked(DBLLinked** list) { //удаление списка
    //printf("\del_list\n");
    Word* tmp = (*list)->head;
    Word* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

int check(char* s) {
    int flag = 0;
    char sim[] = "!@#$%^&*()-_`~/?{}[]|:;',=+\\ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ\t<>üöäß0§ÜÖÄ";
    size_t len = strlen(s);
    size_t len_sim = strlen(sim);
    for (int i = 0; i < len_sim; i++) {
        for (int j = 0; j < len; j++) {
            if (sim[i] == s[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    return flag;
}

void del_gl(DBLLinked* list) {
    //printf("\ndel_gl\n");
    Word* tmp = list->head;
    int index = 0;
    while (tmp) {
        //printf("word = %s", tmp->word);
        char* word = tmp->word;
        if (find_gl(word)) {
            if (index == 0) {
                popFront(list);
                index = 0;
                tmp = list->head;
                continue;
            }
            else {
                deleteNth(list, index);
                index = 0;
                tmp = list->head;
                continue;
            }
        }
        index++;
        tmp = tmp->next;
    }
    printDBLLinked(list);
}


void func(DBLLinked* list) { //функция из варианта
    printf("\nВведите количество букв (N): ");
    int N;
    scanf("%d", &N);
    if (N < 0) {
        puts("Кол-во букв не должно быть меньше 0");
        exit(-1);
    }

    DBLLinked* list_more = createDBLLinked();  //создаем два списка
    DBLLinked* list_less = createDBLLinked();

    Word* tmp = list->head;
    while (tmp) {     //проходимся по основному списку и добавляем элемент либо в первый, либо во второй список
        char* word = tmp->word;
        if (strlen(word) > N) {
            pushBack(list_more, word);
        }
        else {
            pushBack(list_less, word);
        }
        tmp = tmp->next;
    }

    printf("\nСписок со словами, длиной больше N: ");
    printDBLLinked(list_more);
    printf("\nСписок остальных слов: ");
    printDBLLinked(list_less);

    deleteDBLLinked(&list_more);
    deleteDBLLinked(&list_less);    //очищаем списки
    deleteDBLLinked(&list);
}

void main() {
    char str[200];
    printf("Input string: ");
    fgets(str, 200, stdin);

    char* point = strstr(str, ".");
    if (!point) {
        printf("\nPoint not found\n");
        exit(1);
    }

    char* istr = strtok(str, "."); //обрезаем строку до точки

    if (check(str)) {//проверка на латинские буквы
        printf("\nWRONG string\n");
        exit(1);
    }


    DBLLinked* list = createDBLLinked();   //создаем список

    istr = strtok(str, " ");   //получаем указатель на первое слово
    while (istr) {
        char* word = istr;
        pushBack(list, word);  //добавляем остальные в конец
        istr = strtok(NULL, " ");
    }

    printf("String to list of words: ");
    printDBLLinked(list);

    del_gl(list);
    deleteDBLLinked(&list);
}


#endif
