#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM_CODA 10
#define DIM_STACK 10
#define DIM_STRING 50

typedef struct {
    char articolo[DIM_STRING];
    double prezzo;
    char destinatario[DIM_STRING];
} Ordine;

typedef struct node {
    Ordine data;
    struct node* link;
} Node;

//La coda è una struttura dati astratta lineare di tipo FIFO (First In First Out)
typedef struct {
    Node *front;
    Node *back;
    int cont;
} Queue;

typedef struct {
    Node* top;
    int cont;
} Stack;

// 4_1
// prototipi funzioni per la gestione della Coda

/**algoritmo isEmptyQueue (puntatore struttura queue) → Boolean
   if (coda vuota) then
        return true
   else
        return false
*/
bool isEmptyQueue(Queue *queue) {
    return (queue->cont == 0) ? true : false;
}

/**algoritmo isFullQueue (puntatore struttura queue) → Boolean
    if (coda piena) then
        return true
    else
        return false
*/
bool isFullQueue(Queue *queue) {
    return (queue->cont >= DIM_CODA) ? true : false;
}

/**algoritmo pushQueue (puntatore struttura queue, Type val)
    if (isFullQueue(queue)) then
        stampa “errore overflow”
    else
        alloca new_node
        inserisci val in data e NULL in link
        if (isEmptyQueue(queue)) then
            front punta a new_node
            back punta a new_node
        else
            link di back punta a new_node
            back punta a new_node
        incrementa il conteggio degli elementi
*/
void pushQueue(Queue *queue, Ordine *ordine) {
    Node *newNode = NULL;

    if (isFullQueue(queue)) {
        fprintf(stderr, "\nErrore overflow: la coda è piena");
    } else {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            exit(EXIT_FAILURE);
        }
        newNode->data = *ordine;
        newNode->link = NULL;

        if (isEmptyQueue(queue)) {
            queue->front = newNode;
            queue->back = newNode;
        } else {
            queue->back->link = newNode;
            queue->back = newNode;
        }

        queue->cont++;
    }
}

/**algoritmo popQueue (puntatore struttura queue) → Type
    if (isEmptyQueue(queue)) then
        stampa “errore underflow”
        val ← -1 //val è una variabile temporanea di tipo Type
    else
        temp punta a front //temp è un puntatore temporaneo
        val ← data di front

        if (coda ha un solo elemento) then
            metti a NULL front e back
        else
            front punta a link di front

        decrementa il conteggio degli elementi
        dealloca l’elemento puntato da temp
    return val
*/
Ordine popQueue(Queue *queue) {
    Ordine returnValue;
    Node *temp = NULL;
    Ordine err = {};

    if (isEmptyQueue(queue)) {
        fprintf(stderr, "\nErrore underflow: la coda è vuota");
        returnValue = err;
    } else {
        temp = queue->front;
        returnValue = queue->front->data;

        if (queue->cont == 1) {
            queue->front = NULL;
            queue->back = NULL;
        } else {
            queue->front = queue->front->link;
            queue->cont--;
        }
        free(temp);
    }
    return returnValue;
}

void printQueue(Queue *queue) {
    Node *temp = NULL;

    temp = queue->front;
    for (int count = 0; temp != NULL; count++, temp = temp->link) {
        printf("\n[%2d] %s\n"
               "\t %lf\n"
               "\t %s",
               count, temp->data.articolo, temp->data.prezzo, temp->data.destinatario);
    }
}

// 4_2
// prototipi funzioni per la gestione dello Stack

/**algoritmo isEmptyStack (puntatore struttura stack) → Booleano
    if (stack vuoto) then
        return true
    else
        return false
*/
bool isEmptyStack(Stack *stack) {
    return (stack->cont == 0) ? true : false;
}

/**algoritmo isFullStack (puntatore struttura stack) → Booleano
    if (stack pieno) then
        return true
    else
        return false
 */
bool isFullStack(Stack *stack) {
    return (stack->cont >= DIM_CODA) ? true : false;

}

/**algoritmo pushStack (puntatore struttura stack, Type val)
    if (isFullStack(stack)) then
        stampa “errore overflow”
    else
        alloca new_node
        inserisci val in data e NULL in link

        if (isEmptyStack(stack)) then
            top punta a new_node
        else
            link di new_node punta a top
            top punta a new_node

        incrementa il conteggio degli elementi
 */
void pushStack(Stack *stack, Ordine *ordine) {
    Node *newNode = NULL;

    if (isFullStack(stack)) {
        fprintf(stderr, "\nErrore overflow: lo stack è pieno");
    } else {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            exit(EXIT_FAILURE);
        }
        newNode->data = *ordine;
        newNode->link = NULL;

        if (isEmptyStack(stack)) {
            stack->top = newNode;
        } else {
            newNode->link = stack->top;
            stack->top = newNode;
        }
        stack->cont++;
    }
}

/**algoritmo popStack (puntatore struttura stack) → Type
    if (isEmptyStack(stack)) then
        stampa “errore underflow”
        val ← -1 //val è una variabile temporanea di tipo Type
    else
        temp punta a top //temp è un puntatore temporaneo
        val ← data di top
        top punta a link di top
        decrementa il conteggio degli elementi
        dealloca l’elemento puntato da temp
    return val
 */
Ordine popStack(Stack *stack) {
    Ordine returnValue;
    Node *temp = NULL;
    Ordine err = {};

    if (isEmptyStack(stack)) {
        fprintf(stderr, "\nErrore underflow: la coda è vuota");
        returnValue = err;
    } else {
        temp = stack->top;
        returnValue = stack->top->data;

        stack->top = stack->top->link;
        stack->cont--;

        free(temp);
    }
    return returnValue;
}

void printStack(Stack *stack) {
    Node *temp = NULL;

    temp = stack->top;
    for (int count = 0; temp != NULL; count++, temp = temp->link) {
        printf("\n[%2d] %s\n"
               "\t %lf\n"
               "\t %s",
               count, temp->data.articolo, temp->data.prezzo, temp->data.destinatario);
    }
}

// 4_3 Menu e visualizzazione ordini
/*Prevedere un menu che consenta all’utente di effettuare le seguenti operazioni:
• Inserire un nuovo ordine in coda (pushQueue)
• Togliere un ordine dalla coda per processarlo (popQueue)
• Inserire un nuovo ordine nello stack per il trasporto (pushStack)
• Togliere un ordine dallo stack per consegnarlo (popStack)
• Processare il primo ordine in coda e automaticamente prepararlo per
    la consegna (popQueue seguito da pushStack)
• Stampare lo stato della coda degli ordini (printQueue)
• Stampare lo stato dello stack delle consegne (printStack)
*/
void printMenu() {
    char *operazioni[] = {
            "Inserire un nuovo ordine in coda",
            "Togliere un ordine dalla coda per processarlo",
            "Inserire un nuovo ordine nello stack per il trasporto",
            "Togliere un ordine dallo stack per consegnarlo",
            "Processare il primo ordine in coda e automaticamente prepararlo per la consegna",
            "Stampare lo stato della coda degli ordini",
            "Stampare lo stato dello stack delle consegne"
    };

    printf("\nQuale operazione vuoi effettuare:\n");
    for (int i = 1; i <= 7; ++i) {
        printf("\n[%d] %s", i, operazioni[i - 1]);
    }
    printf("\n[0] Lascia il gestore");
}

int acquisciChoice() {
    int choice;
    do {
        printf("\n>>>");
        scanf("%d", &choice);

        if (choice < 0 || choice > 7) {
            printf("\nScelta non valida, riprovare");
        }
    } while (choice < 0 || choice > 7);
    return choice;
}

Ordine acquisisciOrdine() {
    Ordine returnValue;

    printf("\nInserisci dati dell'ordine: ");
    printf("\nArticolo :");
    scanf(" %31[^\n]s", returnValue.articolo);
    printf("\nPrezzo: ");
    scanf("%lf", &returnValue.prezzo);
    printf("\nDestinatario: ");
    scanf(" %31[^\n]s", returnValue.destinatario);

    return returnValue;
}

int main()
{
    //dichiarazione e inizializzazione della Coda
    Queue queue;
    queue.front = NULL;
    queue.back = NULL;
    queue.cont = 0;

    //dichiarazione e inizializzazione dello Stack
    Stack stack;
    stack.top = NULL;
    stack.cont = 0;

    //istruzioni e chiamate per i test...
    int choice = 0;

    Ordine ordine;

    printf("\nBenvenuto nel gestore ordini:\n");

    do {
        printMenu();
        choice = acquisciChoice();
        switch (choice) {
            case 1:
                // Inserire un nuovo ordine in coda
                ordine = acquisisciOrdine();
                pushQueue(&queue, &ordine);
                break;
            case 2:
                // Togliere un ordine dalla coda per processarlo
                ordine = popQueue(&queue);
                break;
            case 3:
                // Inserire un nuovo ordine nello stack per il trasporto
                pushStack(&stack, &ordine);
                break;
            case 4:
                // Togliere un ordine dallo stack per consegnarlo
                ordine = popStack(&stack);

                break;
            case 5:
                // Processare il primo ordine in coda e automaticamente prepararlo per la consegna
                ordine = popQueue(&queue);
                pushStack(&stack, &ordine);
                break;
            case 6:
                // Stampare lo stato della coda degli ordini
                printQueue(&queue);
                break;
            case 7:
                // Stampare lo stato dello stack delle consegne
                printStack(&stack);
                break;
            case 0:
                printf("\nLeaving");
                break;
            default:
                choice = -1;
                printf("\nInput non valido, riprova");
                break;
        }
    } while (choice != 0);
    return 0;
}