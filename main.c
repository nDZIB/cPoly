#include<stdio.h>
#include<math.h>


typedef struct Poly_Node
{
    int a;
    int x;
    unsigned int n;

    Poly_Node* prev;
    Poly_Node* next;
} Poly_Node;


void create_poly(Poly_Node **P)
{
    int deg;

    printf("============================================   \n\n");
    printf("Enter degree of polynomial: \n");
    printf("============================================   \n\n");
    scanf("%d", &deg);

    int coef;
    int expo;

    Poly_Node* itr = (Poly_Node*)malloc(sizeof(Poly_Node));

    printf("Enter coeficients of terms of 0 to quit");
    while(deg >= 0)
    {
        printf("COEFICIENT of term with EXPONENT= %d -:", deg);
        scanf("%d", &coef);


        if(coef != 0)
        {
            Poly_Node* node = (Poly_Node*)malloc(sizeof(Poly_Node));
            node->a = coef;
            node->n = deg;
            node->prev = NULL;
            node->next = NULL;

            --deg;
            if(*P == NULL)
            {
                *P = node;
                continue;
            }
            else
            {
                itr = *P;
                while(itr->next != NULL)
                {
                    itr= itr->next;
                }
                node->prev = itr;
                itr->next = node;
            }
        }
        else
            break;
    }
}

void display_poly(Poly_Node *p)
{
    if(p->a >= 0 && p->prev != NULL)
        printf("+");
    printf("%dX^%d", p->a, p->n);

    if(p->next != NULL)
        display_poly(p->next);
}

void add_poly(Poly_Node **R, Poly_Node *P, Poly_Node *Q)
{
    Poly_Node *cP = P;
    Poly_Node *cQ = Q;

    while(cP != NULL)
    {

        if(*R == NULL)
        {
            Poly_Node *node = (Poly_Node*)malloc(sizeof(Poly_Node));
            node->a = cP->a;
            node->n = cP->n;

            node->next = NULL;
            node->prev = NULL;

            *R = node;
        }
        else
        {
            Poly_Node *cR = *R;

            while(cR->next != NULL)
            {
                cR = cR->next;
            }

            Poly_Node *node = (Poly_Node*)malloc(sizeof(Poly_Node));
            node->a = cP->a;
            node->n = cP->n;
            node->next = NULL;
            cR->next = node;
            node->prev = cR;
        }

        cP = cP->next;
    }

    Poly_Node *cR = *R;

    if(cR == NULL)
    {
        while(cQ != NULL)
        {
            Poly_Node *node = (Poly_Node*)malloc(sizeof(Poly_Node));
            node->a = cQ->a;
            node->n = cQ->n;
            node->next = NULL;

            cR->next = node;
            node->prev = cR;
            cQ = cQ->next;
        }
    }

    else
    {
        while(cQ != NULL)
        {
            Poly_Node *cR = *R;
            while(cR != NULL)
            {
                if(cQ->n == cR->n)
                {
                    cR->a += cQ->a;
                }
                else if(cQ->n > cR->n)
                {

                    Poly_Node* n = (Poly_Node*)malloc(sizeof(Poly_Node));
                    n->a = cQ->a;
                    n->n = cQ->n;

                    n->prev = cR->prev;
                    n->next = cR;
                    cR->prev = n;
                }
                else if(cR->next == NULL)
                {
                    Poly_Node* n = (Poly_Node*)malloc(sizeof(Poly_Node));
                    n->next= NULL;
                    n->prev = cR;
                    n->a = cQ->a;
                    n->n = cQ->n;
                    cR->next = n;
                }
                cR = cR->next;
            }
            cQ = cQ->next;
        }
    }
}

int eval_poly(Poly_Node *P, int X0)
{
    if(P==NULL)
        return 0;
    else
    {
        int a = P->a * pow(X0, P->n);
        return a + eval_poly(P->next, X0);
    }
}


void multiply_poly(Poly_Node **R, Poly_Node *P, Poly_Node *Q)
{
    if(P==NULL)
    {
        *R = Q;
    }
    else if(Q == NULL)
    {
        *R = P;
    }
    else
    {
        while(P != NULL)
        {
            Poly_Node *cQ = Q;
            while(cQ != NULL)
            {
                Poly_Node *temp = (Poly_Node*)malloc(sizeof(Poly_Node));
                temp->a = (P->a)*(cQ->a);
                temp->n = (P->n)+(cQ->n);
                temp->next = NULL;

                if(*R==NULL)
                {
                    temp->prev = NULL;
                    *R = temp;
                }

                else
                {
                    Poly_Node * cR = *R;
                    while(cR != NULL)
                    {
                        if(cR->n==temp->n)
                        {
                            cR->a += temp->a;
                        }
                        else if(cR->n < temp->n)
                        {
                            temp->prev = cR->prev;
                            temp->next = cR;
                            cR->prev = temp;
                        }
                        else if(cR->next == NULL)
                        {
                            cR->next = temp;
                            temp->prev = cR;
                            break;
                        }

                        cR = cR->next;
                    }
                }
                cQ = cQ->next;
            }
            P = P->next;
        }
    }
}


Poly_Node* p1;
Poly_Node* p2;

Poly_Node* product;
Poly_Node *sum;

int main()
{
    create_poly(&p1);
    create_poly(&p2);

    add_poly(&sum, p1, p2);
    multiply_poly(&product, p1, p2);
    printf("\n == Sum == \n");
    display_poly(sum);
    printf("\n==========\n");

    printf("\n == Product == \n");
    display_poly(product);
    printf("\n==========\n");
    return 0;
}

