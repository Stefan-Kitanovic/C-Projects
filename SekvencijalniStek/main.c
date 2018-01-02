#include <stdio.h>
#include <stdlib.h>

typedef struct stek
{
    int * data;         /// stek
    int capacity;       /// kolko mozemo imati
    int amount;         /// kolko trenutno imamo
}STACK;

void Push(STACK * st, int data);
int Pop(STACK * st);
void Init(STACK * st);

int main()
{
    STACK st;
    Init(&st);

    Push(&st, 10);
    Push(&st, 20);
    Push(&st, 30);
    Push(&st, 40);
    Push(&st, 50);
    Push(&st, 60);
    Push(&st, 70);
    Push(&st, 80);
    Push(&st, 90);
    Push(&st, 100);
    Push(&st, 110);
    Push(&st, 120);

    printf("%d\n", st.data[0]);
    printf("%d\n", st.data[1]);
    printf("%d\n", st.data[2]);
    printf("%d\n", st.data[3]);
    printf("----------------------\n");
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));
    printf("%d\n", Pop(&st));


    return 0;
}

void Init(STACK * st)
{
    st->capacity = 4;
    st->amount = 0;
    st->data = NULL;
}

void Push(STACK * st, int data)
{
    if ( st->capacity == st->amount )
    {
        printf("Cannot push.\n");
        return;
    }

    st->amount = st->amount + 1;
    st->data = realloc(st->data, st->amount * sizeof(int));
    st->data[st->amount - 1] = data;
}

int Pop(STACK * st)
{
    if ( st->amount <= 0)
    {
        printf("Unable to pop empty stack!\n");
        return -1;
    }

    int data = st->data[st->amount - 1];
    st->amount = st->amount - 1;

    return data;
}
