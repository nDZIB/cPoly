#include<stdio.h>
#include<math.h>

//STRUCTURE OF A POLYNOMIAL
typedef struct Poly_Node
{
    int a;  //COEFFICIENT OF TERM
    unsigned int n; //EXPONENT OF POLYNOMIAL NODE

    Poly_Node* prev;    //POINTER TO PREVIOUS TERM IN POLYNOMIAL
    Poly_Node* next;    //POINTER TO NEXT NODE IN POLYNOMIAL
} Poly_Node;

//FUNCTION TO CREATE POLYNOMIAL: NB:: Customize to suit needs. stops creating polynomial nodes when input coefficient=0
void create_poly(Poly_Node **P)
{
    //GET THE DEGREE OF the polynomial
    int deg;

    printf("============================================   \n\n");
    printf("\n Enter degree of polynomial: \n");
    printf("============================================   \n\n");
    scanf("%d", &deg);

    int coef;
    int expo;

    // CREATE AN ITERATOR TO USE IN NAVIGATING THROUGH THE POLYNOMIALS AND CREATING NODES
    Poly_Node* itr = (Poly_Node*)malloc(sizeof(Poly_Node));

    printf("Enter coeficients of terms or 0 to quit\n");

    //WHILE INPUT DEGREE PPOLYNOMIAL IS GREATER OR EQUAL TO ZERO CREATE NODES
    while(deg >= 0)
    {
        // GET THE NODE'S COEFFICIENT FROM STDIN
        printf("COEFICIENT of term with EXPONENT= %d -:", deg);
        scanf("%d", &coef);


        // IF INPUT COEFFICIENT IS DIFFERENT FROM ZERO, CREATE NODE nb: REMOVE THIS CHECK IF THE INTENTION IS
        //TO HAVE POLYNOMIALS MISSING TERMS
        if(coef != 0)
        {
            // ALLOCATE MEMORY FOR A NEW POLYNOMIAL NODE AND SET ITS EXPONENT AND COEFFICIENT
            Poly_Node* node = (Poly_Node*)malloc(sizeof(Poly_Node));
            node->a = coef;
            node->n = deg;
            node->prev = NULL;
            node->next = NULL;


            --deg;

            //IF THIS IS THE FIRST TERM OF THE POLYNOMIAL
            if(*P == NULL)
            {
                *P = node;
                continue;
            }
            else // OTHERWISE IF THE POLYNOMIAL ALREADY HAS TERMS, LOOP TO END OF THE POLYNOMIAL USING THE ITERATOR
            {
                //AND APPEND THE NEW NODE
                itr = *P;
                while(itr->next != NULL)    // THE LAST POLYNOMIAL TERM HAS ITS NEXT POINTER POINTING TO NULL
                {
                    itr= itr->next;
                }
                node->prev = itr;       // APPEND THE NEWLY CREATED NODE AT THE END OF THIS POLYNOMIAL
                itr->next = node;
            }
        }
        else
            break;      // STOP IF THE COEFFICIENT INPUTTED == 0
    }
}

//RECURSIVELY PRINT EACH TERM A POLYNOMIAL
void display_poly(Poly_Node *p)
{
    if(p==NULL)
    {
        return; //RETURN IF CURRENT TERM IS UNDEFINED
    }
    else        //OTHERWISE IF CURRENT TERM IS DEFINED
    {
        if(p->a >= 0 && p->prev != NULL)    //IF THIS TERM'S COEFFICIENT IS POSITIVE AND IS NOT THE FIRST TERM OF POLYNOMIAL
            printf("+");                    //PREPEND A '+' nb: FIRST TERM OF POLYNOMIAL HAS ITS PREV POINTER POINTING TO NULL
        printf("%dX^%d", p->a, p->n);       //FORMAT THE CURRENT TERM AND PRINT TO STDOUT

        if(p->next != NULL)
            display_poly(p->next);          //PRINT THE NEXT TERM OF POLYNOMIAL
    }
}


//ADD TWO POLYNOMIALS TO GET A NEW POLYNOMIAL
void add_poly(Poly_Node **R, Poly_Node *P, Poly_Node *Q)
{
    //MAKE COPIES OF THE ORIGINAL POLYNOMIALS FOR USE AS ITERATORS ON THOSE POLYNOMIALS
    Poly_Node *cP = P;
    Poly_Node *cQ = Q;

    // COPY THE CONTENTS OF THE FIRST POLYNOMIAL INTO THE POLYNOMIAL TO HOLD THE SUM, NAMED RESULTS POLYNOMIAL
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

    Poly_Node *cR = *R;     //GET A A PONITER TO THE HEAD OF THE RESULTS POLYNOMIAL

    if(cR == NULL)          //IF RESULTS POLYNOMIAL HAS UNDEFINED HEAD, i.e THE FIRST POLYNOMIAL WAS UNDEFINED
    {                       //SIMPLY COPY THE SECOND POLYNOMIAL INTO THE RESULTS POLYNOMIAL
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

    else        // OTHERWISE IF THE RESULTS POLYNOMIAL HAS TERMS IN IT
    {
        while(cQ != NULL)       //LOOP THROUGH THE SECOND POLYNOMIAL
        {
            Poly_Node *cR = *R;
            while(cR != NULL)   //FOR EACH TERM IN THE RESULTS POLYNOMIAL, COMPARE ITS EXPONENT TO  THE CURRENT TERM OF SECOND POLYNOMIAL
            {
                if(cQ->n == cR->n)  //IF BOTH EXPONENTS ARE EQUAL SUM THEIR COEFICIENTS AS SAVE AS NEW COEFICENT FOR THAT TERM IN THE RESULTS POLYNOMIAL
                {
                    cR->a += cQ->a;
                }
                else if(cQ->n > cR->n)      // IT THE CURRENT TERM IN THE SECOND POLYNOMIAL HAS A HIGHER EXPONENT THAN THAT IN THE RESULTS POLYNOMIAL,
                {                           // INSERT IT INTO THE RESULTS POLYNOMIAL JUST BEFORE THE CURRENT TERM

                    Poly_Node* n = (Poly_Node*)malloc(sizeof(Poly_Node));
                    n->a = cQ->a;
                    n->n = cQ->n;

                    n->prev = cR->prev;
                    n->next = cR;
                    cR->prev = n;
                }
                else if(cR->next == NULL)   // IF NONE OF THE CHECKS HOLDS AND THIS THE LAST TERM IN THE RESULTS POLYNOMIAL,
                {                              //APPEND THE CURRENT TERM FROM THE SECOND POLYNOMIAL TO THE RESULTS POLYNOMIAL
                    Poly_Node* n = (Poly_Node*)malloc(sizeof(Poly_Node));
                    n->next= NULL;
                    n->prev = cR;
                    n->a = cQ->a;
                    n->n = cQ->n;
                    cR->next = n;
                }
                cR = cR->next; // PROCCEED TO NEXT TERM OF RESULTS POLYNOMIAL
            }
            cQ = cQ->next;      //PROCCEED TO NEXT TERM OF THE SECOND POLYNOMIAL
        }
    }
}


// EVALUATE THE VALUE OF THE POLYNOMIAL
int eval_poly(Poly_Node *P, int X0)
{
    if(P==NULL)     //IF POLYNOMIAL IS UNDEFINED, RETURN 0
        return 0;
    else
    {
        int a = P->a * pow(X0, P->n);
        return a + eval_poly(P->next, X0);
    }
}

// MULTIPLY TWO POLYNOMIALS TO OBTAIN A NEW POLYNOMIAL
void multiply_poly(Poly_Node **R, Poly_Node *P, Poly_Node *Q)
{
    if(P==NULL)  //IF ONE POLYNOMIAL IS UNDEFINED, THE PRODUCT OF THE TWO POLYNOMIALS SHOULD BE THE OTHER POLYNOMIAL
    {
        *R = Q;
    }
    else if(Q == NULL)
    {
        *R = P;
    }
    else    //OTHERWISE IF BOTH POLYNOMIALS ARE DEFINED
    {
        while(P != NULL)        //FOR EACH TERM IN THE FIRST POLYNOMIAL,
        {
            Poly_Node *cQ = Q;
            while(cQ != NULL)   //MULTIPLY IT BY EACH TERM IN THE SECOND POLYNOMIAL AND ADD EACH PRODUCT TO THE RESULTS POLYNOMIAL
            {
                Poly_Node *temp = (Poly_Node*)malloc(sizeof(Poly_Node));    //REPLACE THIS WITH A CALL TO THE ADD_POLY FUNCTION INSTEAD
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

