#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_NOME 50
#define NUM_TEST 15

typedef struct
{
    char nome[DIM_NOME];
    float gradi;
    int bottiglie;
} Birra;

typedef struct nodo
{
    Birra key;
    struct nodo *parent;
    struct nodo *left;
    struct nodo *right;
} Nodo;

/* -------------------------------
 Funzioni gia' implementate:
 ------------------------------- */
Birra acquisisci_birra();
void stampa_birra(Birra b);

Nodo* crea_nodo(Birra b);
Nodo* carica_test();

/* -------------------------------
 Funzioni da implementare:
 ------------------------------- */
Nodo* insert_nodo(Nodo* root, Nodo* new_node);
void inorder(Nodo* root);
void preorder(Nodo* root);
void postorder(Nodo* root);

int profondita(Nodo* root);
int max(int v1, int v2);

Nodo* ricerca(Nodo* root, char* nome_birra);

Nodo* abr_min(Nodo* root);
Nodo* abr_max(Nodo* root);

Nodo* abr_succ(Nodo* x);
Nodo* abr_pred(Nodo* x);

Nodo* delete_node(Nodo* root, Nodo* nodo);

int main()
{
    Nodo *root = NULL; // Radice dell'ABR

    //variabili ausiliarie
    int scelta;
    Birra tmp_birra;
    Nodo* tmp_nodo;
    int prof;
    char tmp_nome[DIM_NOME];


    do
    {
        //Menu con le operazioni disponibili
        printf("\nMENU:\n");
        printf("1) inserisci nuova birra \n");
        printf("2) visita INORDER \n");
        printf("3) visita PREORDER \n");
        printf("4) visita POSTORDER \n");
        printf("5) calcolo profondita \n");
        printf("6) ricerca di una birra \n");
        printf("7) ricerca del minimo \n");
        printf("8) ricerca del massimo \n");
        printf("9) ricerca del precedente di una birra \n");
        printf("10) ricerca del successore di una birra \n");
        printf("11) cancellazione di una birra \n");
        printf("12) carica birre di test (in un ABR vuoto)\n");
        printf("13) esci \n");

        printf("scelta: ");
        scanf("%d", &scelta);

        switch(scelta)
        {
            case 1:
                tmp_birra = acquisisci_birra();
                tmp_nodo = crea_nodo(tmp_birra);
                root = insert_nodo(root, tmp_nodo);
                break;

            case 2:
                inorder(root);
                break;

            case 3:
                preorder(root);
                break;

            case 4:
                postorder(root);
                break;

            case 5:
                prof = profondita(root);
                printf("\nProfondita: %d\n", prof);
                break;

            case 6:
                printf("\nBirra da cercare: ");
                getchar();
                scanf("%[^\n]s", tmp_nome);
                tmp_nodo = ricerca(root, tmp_nome);

                if(tmp_nodo != NULL)
                    printf("\nTrovata birra %s\n", tmp_nodo->key.nome);
                else
                    printf("\nBirra %s non trovata\n", tmp_nome);
                break;

            case 7:
                tmp_nodo = abr_min(root);
                printf("Il minimo e': %s\n", tmp_nodo->key.nome);
                break;

            case 8:
                tmp_nodo = abr_max(root);
                printf("Il minimo e': %s\n", tmp_nodo->key.nome);
                break;

            case 9:
                printf("\nBirra da cercare: ");
                getchar();
                scanf("%[^\n]s", tmp_nome);
                tmp_nodo = ricerca(root, tmp_nome);

                if(tmp_nodo != NULL)
                {
                    tmp_nodo = abr_pred(tmp_nodo);
                    if(tmp_nodo != NULL)
                        printf("\nIl precedente e': %s\n", tmp_nodo->key.nome);
                    else
                        printf("\nNon esiste un precedente\n");
                }

                else
                    printf("\nBirra non trovata\n");
                break;

            case 10:
                printf("\nBirra da cercare: ");
                getchar();
                scanf("%[^\n]s", tmp_nome);
                tmp_nodo = ricerca(root, tmp_nome);

                if(tmp_nodo != NULL)
                {
                    tmp_nodo = abr_succ(tmp_nodo);
                    if(tmp_nodo != NULL)
                        printf("\nIl successore e': %s\n", tmp_nodo->key.nome);
                    else
                        printf("\nNon esiste un successore\n");
                }

                else
                    printf("\nBirra non trovata\n");
                break;

            case 11:
                printf("\nBirra da cercare: ");
                getchar();
                scanf("%[^\n]s", tmp_nome);
                tmp_nodo = ricerca(root, tmp_nome);

                if(tmp_nodo != NULL)
                {
                    root = delete_node(root, tmp_nodo);
                    printf("\nNodo eliminato\n");
                }

                else
                    printf("\nBirra non trovata\n");
                break;

            case 12:
                root = carica_test();
                break;

            case 13:
                printf("\nCiao!\n");
                break;

            default:
                printf("\nScelta non valida\n");

        }

    } while(scelta != 13);


    return 0;
}


/* -------------------------------
 Funzioni gia' implementate (NON MODIFICARE):
 ------------------------------- */
Birra acquisisci_birra()
{
    Birra b;
    getchar();

    printf("nome: ");
    scanf("%[^\n]s", b.nome);
    getchar();

    printf("gradi: ");
    scanf("%f", &b.gradi);

    printf("bottiglie: ");
    scanf("%d", &b.bottiglie);

    return b;
}

void stampa_birra(Birra b)
{
    printf("--------------------- \n");
    printf("nome:  %s \n", b.nome);
    printf("gradi: %.1f \n", b.gradi);
    printf("bottiglie: %d \n", b.bottiglie);
    printf("--------------------- \n");
}

Nodo* crea_nodo(Birra b)
{
    Nodo* new_node = (Nodo*)malloc(sizeof(Nodo));
    if(new_node != NULL)
    {
        new_node->key = b;
        new_node->parent = NULL;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

Nodo* carica_test()
{
    Nodo *root = NULL;
    int i;
    Birra elenco[NUM_TEST] = {{"Ichnusa", 4.7, 3}, {"Founders", 5.7, 15}, {"Peroni", 4.7, 2},
                              {"San Miguel", 3.2, 4}, {"Miller", 4.7, 7}, {"Guinnes", 4.2, 1},
                              {"Best Brau", 4.7, 12}, {"Barley", 5.0, 7}, {"Chouffe", 8.0, 12},
                              {"Franziskaner", 5, 10}, {"Heineken", 5.0, 7}, {"Kwak", 8.0, 14},
                              {"Paulaner", 5.5, 10}, {"Rubiu", 4.5, 10}, {"Tuborg", 5.0, 3}};


    for(i = 0; i < NUM_TEST; i++)
    {
        Nodo *new_birra = crea_nodo(elenco[i]);
        root = insert_nodo(root, new_birra);
    }

    return root;
}


/* -------------------------------
 Funzioni da implementare:
 ------------------------------- */
/*
algoritmo insert_nodo(puntatore a radice, puntatore a nuovo_nodo) → puntatore a Nodo
y ← NULL
x ← puntatore a radice
while (x ≠ NULL) do // L’algoritmo cerca un cammino discendente dalla radice
    y ← x // fino ad una foglia; x segue il cammino, y punta al padre di x
    if (key di nuovo_nodo < key di x) then
    x ← figlio sx di x
    else
    x ← figlio dx di x

// usciti da questo ciclo y è il puntatore al padre del nuovo nodo
padre di nuovo_nodo ← y
if (y == NULL) then
    radice ← nuovo_nodo
else if (key di nuovo_nodo < key di y) then
    figlio sx di y ← nuovo_nodo
else
    figlio dx di y ← nuovo_nodo
return puntatore a radice
*/
Nodo* insert_nodo(Nodo* root, Nodo* new_node) {
    Nodo *y = NULL, *x = root;
    while (x != NULL) {
        y = x;
        if (strcmp(new_node->key.nome, x->key.nome) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    new_node->parent = y;
    if (y == NULL) {
        root = new_node;
    } else if (strcmp(new_node->key.nome, y->key.nome) < 0) {
        y->left = new_node;
    } else {
        y->right = new_node;
    }
    return root;
}

/*
algoritmo inorder(puntatore a Nodo r) → void
if(r == NULL) then
    return
inorder(figlio sx di r)
visita il nodo r    // stampa contenuto di r
inorder(figlio dx di r)
*/
void inorder(Nodo* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    stampa_birra(root->key);
    inorder(root->right);
}

/*
algoritmo preorder(puntatore a Nodo r) → void
if(r == NULL) then
    return
visita il nodo r // stampa contenuto di r
preorder(figlio sx di r)
preorder(figlio dx di r)
*/
void preorder(Nodo* root) {
    if (root == NULL) {
        return;
    }
    stampa_birra(root->key);
    preorder(root->left);
    preorder(root->right);
}

/*
algoritmo postorder(puntatore a Nodo r) → void
if(r == NULL) then
    return
postorder(figlio sx di r)
postorder(figlio dx di r)
visita il nodo r // stampa contenuto di r*/
void postorder(Nodo* root){
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    stampa_birra(root->key);
}

/*
algoritmo profondità(puntatore a Nodo r) → intero
if(r == NULL) then
    return 0
sx ← profondità(figlio sx di r)
dx ← profondità(figlio dx di r)
return 1 + max(sx, dx)*/
int profondita(Nodo* root){
    if (root == NULL) {
        return 0;
    }
    int sx = profondita(root->left);
    int dx = profondita(root->right);
    return 1 + max(sx, dx);
}

int max(int v1, int v2)
{
    return v1 > v2 ? v1 : v2;
}

/*
algoritmo ric_abr_ric(puntatore a Nodo radice, Type chiave) → puntatore a Nodo
if(radice == NULL) then
    return NULL
if(chiave == key di radice) then
    return radice
if(chiave < key di radice) then
    return ric_abr_ric(figlio sx di radice, chiave)
return ric_abr_ric(figlio dx di radice, chiave)
*/
Nodo* ricerca(Nodo* root, char* nome_birra){
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(nome_birra, root->key.nome) == 0) {
        return root;
    }
    if (strcmp(nome_birra, root->key.nome) < 0) {
        return ricerca(root->left, nome_birra);
    }
    return ricerca(root->right, nome_birra);
}

/*
algoritmo abr_min(puntatore a Nodo radice) → puntatore a Nodo
nodo ← radice
while(figlio sinistro di nodo ≠ NULL) do
    nodo ← figlio sinistro di nodo
return nodo
*/
Nodo* abr_min(Nodo* root){
    Nodo* nodo = root;
    while (nodo->left != NULL) {
        nodo = nodo->left;
    }
    return nodo;
}

/*
algoritmo abr_max(puntatore a Nodo radice) → puntatore a Nodo
nodo ← radice
while(figlio destro di nodo ≠ NULL) do
    nodo ← figlio destro di nodo
return nodo
*/
Nodo* abr_max(Nodo* root){
    Nodo* nodo = root;
    while (nodo->right != NULL) {
        nodo = nodo->right;
    }
    return nodo;
}

/*
algoritmo abr_pred(puntatore a Nodo x) → puntatore a Nodo
if(figlio sx di x ≠ NULL) then
return abr_max(figlio sx di x)
y ← padre di x
while(y ≠ NULL and x == figlio sx di y) do
x ← y
y ← padre di y
return y
*/
Nodo* abr_pred(Nodo* x){
    Nodo *y = NULL;
    if (x->left != NULL) {
        return abr_max(x->left);
    }
    y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

/*
algoritmo abr_succ(puntatore a Nodo x) → puntatore a Nodo
if(figlio dx di x ≠ NULL) then
return abr_min(figlio dx di x)
y ← padre di x
while(y ≠ NULL and x == figlio dx di y) do
x ← y
y ← padre di y
return y
*/
Nodo* abr_succ(Nodo* x){
    Nodo *y = NULL;
    if (x->right != NULL) {
        return abr_min(x->right);
    }
    y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

/*
algoritmo delete_nodo(puntatore a radice, puntatore a nodo) → puntatore a Nodo
if(figlio sx di nodo == NULL or figlio dx di nodo == NULL) then
    y ← nodo
else
    y ← abr_succ(nodo)

if(figlio sx di y ≠ NULL) then
    x ← figlio sx di y
else
    x ← figlio dx di y

if(x ≠ NULL) then
    padre di x ← padre di y

if(padre di y == NULL) then
    radice ← x
else if(figlio sx di padre di y == y) then
    figlio sx di padre di y ← x
else
    figlio dx di padre di y ← x

if(y ≠ nodo) then
    key di nodo ← key di y

dealloca y
return radice
*/
Nodo* delete_node(Nodo* root, Nodo* nodo){
    Nodo* y = NULL;
    Nodo* x = NULL;

    if (nodo->left == NULL || nodo->right == NULL) {
        y = nodo;
    } else {
        y = abr_succ(nodo);
    }

    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != NULL) {
        x->parent = y->parent;
    }

    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != nodo) {
        nodo->key = y->key;
    }
    free(y);
    return root;
}
