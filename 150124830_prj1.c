#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NANOSECONDS_PER_SECOND 1000000000

typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
} Node;

/*Creates a new node and links it to the previous one, if there is any */
Node* createNode(Node* prevNode, char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!! \n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = prevNode;
    return newNode;
}

//Appends a node with the new data at the end of the list
void append(Node** head_ref, Node** tail_ref, char new_data) {
    Node* last = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = createNode(NULL, new_data);
        *tail_ref = *head_ref;
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;
    }
    
    last->next = createNode(last, new_data);
    *tail_ref = last->next; 
}

/*Displays the linked list from the beginning*/
void displayList(Node* node, FILE* outputFile) {

    
    if (outputFile == NULL) {
        printf("Error opening file !! \n");
        return; // Exit with an error code
    }


    while (node != NULL) {
        printf("%c", node->data);
        fprintf(outputFile, "%c", node->data);
        node = node->next;
    }
    fprintf(outputFile,"\n");
    printf("\n");
    fclose(outputFile);
}

/*Displays the linked list in reverse*/
void displayReverseList(Node* node) {
    while (node != NULL) {
        printf("%c", node->data);
        node = node->prev;
    }
    printf("\n");
}

/*Frees memory for all nodes in the linked list*/
void freeList(Node* node) {
    Node* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

/*Reverses the linked list by swapping next and prev for each node*/
void reverseLinkedList(Node** head_Ref, Node** tail_Ref) {
    Node* current = *head_Ref;
    Node* tmp = NULL;

    while (current != NULL) {
        tmp = current->prev;
        current->prev = current->next;
        current->next = tmp;
        
        current = current->prev;
    }

    if (tmp != NULL) {
        *tail_Ref = *head_Ref;
        *head_Ref = tmp->prev;
    }
}
/*Adds two linked lists representing numbers*/
void addition(Node* tailValue1, Node* tailValue2, Node** headResultPointer, Node** tailResultPointer) {
    Node* headResult = *headResultPointer;
    Node* tailResult = *tailResultPointer;
    short sum = 0;
    Node* digitPointer1 = tailValue1;
    Node* digitPointer2 = tailValue2;
    int carry = 0;

    while (digitPointer1 != NULL || digitPointer2 != NULL) {
        if (digitPointer1 != NULL && digitPointer1->data == '.') digitPointer1 = digitPointer1->prev;
        if (digitPointer2 != NULL && digitPointer2->data == '.') digitPointer2 = digitPointer2->prev;

        if (carry) {
            if (digitPointer1 == NULL) sum = 0 + (digitPointer2->data - '0') + 1;
            else if (digitPointer2 == NULL) sum = (digitPointer1->data - '0') + 0 + 1;
            else sum = (digitPointer1->data - '0') + (digitPointer2->data - '0') + 1;
        } else {
            if (digitPointer1 == NULL) sum = 0 + (digitPointer2->data - '0');
            else if (digitPointer2 == NULL) sum = (digitPointer1->data - '0') + 0;
            else sum = (digitPointer1->data - '0') + (digitPointer2->data - '0');
        }

        if (sum >= 10) {
            append(&headResult, &tailResult, (sum % 10) + '0');
            carry = 1;
        } else {
            append(&headResult, &tailResult, sum + '0');
            carry = 0;
        }

        sum = 0;
        if (digitPointer1 != NULL) digitPointer1 = digitPointer1->prev;
        if (digitPointer2 != NULL) digitPointer2 = digitPointer2->prev;
    }

    reverseLinkedList(&headResult, &tailResult);
    *tailResultPointer = tailResult;
    *headResultPointer = headResult;
}

/*Multiplies a linked list by a single digit*/
void multiplyWithDigit(Node** headValuePointer, Node** tailValuePointer, Node** headResultPointer, Node** tailResultPointer, char dig) {
    Node* digitPointer = *tailValuePointer;
    short digit = dig - '0';
    int carry = 0;

    if (digit == 0) {
        append(headResultPointer, tailResultPointer, '0');
        return;
    }

    while (digitPointer != NULL) {
        short tmp = 0;
        if (digitPointer != NULL && digitPointer->data == '.') digitPointer = digitPointer->prev;

        if (carry != 0) {
            tmp = (digitPointer->data - '0') * digit;
            tmp = tmp + carry;
            carry = tmp / 10;
            tmp = tmp % 10;
            append(headResultPointer, tailResultPointer, tmp + '0');
        } else {
            tmp = (digitPointer->data - '0') * digit;
            carry = tmp / 10;
            tmp = tmp % 10;
            append(headResultPointer, tailResultPointer, tmp + '0');
        }

        digitPointer = digitPointer->prev;
    }

    if (carry != 0) append(headResultPointer, tailResultPointer, carry + '0');
    reverseLinkedList(headResultPointer, tailResultPointer);
}

    /*Multiplies two linked lists, treating them as large numbers*/

void multiplication(Node* headValue1, Node* headValue2, Node* tailValue1, Node* tailValue2, Node** headResultPointer, Node** tailResultPointer) {
    Node* tmp = tailValue2;
    size_t power = 0;


    

    multiplyWithDigit(&headValue1, &tailValue1, headResultPointer, tailResultPointer, tmp->data);
    tmp = tmp->prev;
    while (tmp != NULL) {
        if (tmp->data == '.') {
            tmp = tmp->prev;
            continue;
        }
        Node* headResult1 = NULL;
        Node* tailResult1 = NULL;
        Node* headResult2 = NULL;
        Node* tailResult2 = NULL;
        multiplyWithDigit(&headValue1, &tailValue1, &headResult1, &tailResult1, tmp->data);
        power++;
        for (size_t i = 0; i < power; i++) {
            append(&headResult1, &tailResult1, '0');
        }
        addition(tailResult1, *tailResultPointer, &headResult2, &tailResult2);
        free(*headResultPointer);
        *headResultPointer = headResult2;
        *tailResultPointer = tailResult2;
        tmp = tmp->prev;
        free(headResult1);
    }
}

/*Adjusts decimal point position after multiplication*/
void decimalCorrection(Node** tailValue1, size_t decimalCorrection) {
    Node* tmp = NULL;
    Node* UselessZeroPointer = NULL;
    int UselessZero = 1;

    for (; decimalCorrection > 0; decimalCorrection--) {
        if (decimalCorrection == 1) tmp = *tailValue1;
        if ((*tailValue1)->data != '0') UselessZero = 0;
        if ((*tailValue1)->data == '0' && UselessZero) {
            UselessZeroPointer = *tailValue1;
            UselessZeroPointer->prev->next = NULL;
            *tailValue1 = (*tailValue1)->prev;
            free(UselessZeroPointer);
        } else *tailValue1 = (*tailValue1)->prev;
    }

    if ((*tailValue1)->next != NULL) {
        Node* newNode = createNode(*tailValue1, '.');
        newNode->next = tmp;
        if (*tailValue1 != NULL) (*tailValue1)->next = newNode;
    }
}

/*Reads input values from file, performs multiplication, and displays the result if requested*/ 
void calculate() {
    Node* headValue1 = NULL;
    Node* headValue2 = NULL;
    Node* headResult = NULL;
    Node* tailValue1 = NULL;
    Node* tailValue2 = NULL;
    Node* tailResult = NULL;

    FILE *file = fopen("150124830_prj1_input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    
    /*first time I will open the outputfile using the "w" so all content will be deleted from previous run. */
    FILE *outputFile = fopen("150124830_prj1_output.txt", "w");


    char c;
    size_t decimalCounter = 0;
    int flag = 0;

    fprintf(outputFile,"Multiplicand: ");
    while ((c = fgetc(file)) != EOF && c != '\n') {
        append(&headValue1, &tailValue1, c);

        fprintf(outputFile,"%c", c);
        if (flag) decimalCounter++;

        if (c == '.') {
            flag = 1;
        }
    }

    flag = 0;
    
    /*for multiplier input we add a new line character. The current character is '\n' */
    fprintf(outputFile,"%c",c);
    fprintf(outputFile,"Multiplier: ");

    while ((c = fgetc(file)) != EOF && c != '\n') {
        append(&headValue2, &tailValue2, c);

        fprintf(outputFile,"%c", c);
        if (flag) decimalCounter++;

        if (c == '.') {
            flag = 1;
        }
    }

    fclose(file);

    fprintf(outputFile,"\n");

    multiplication(headValue1, headValue2, tailValue1, tailValue2, &headResult, &tailResult);
    decimalCorrection(&tailResult, decimalCounter);
    
    fprintf(outputFile, "Result: ");
    displayList(headResult,outputFile);




    freeList(headValue1);
    freeList(headValue2);
    freeList(headResult);
}

int main() {

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);  


    calculate();

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long elapsed_time = (end.tv_sec - start.tv_sec) * NANOSECONDS_PER_SECOND + (end.tv_nsec - start.tv_nsec);

    printf("Execution Time: %lld nanoseconds\n", elapsed_time);

    FILE *outputFile = fopen("150124830_prj1_output.txt", "a");
    if (outputFile == NULL) {
        printf("Error opening file !! \n");
        return 1; // Exit with an error code
    }
    
    fprintf(outputFile, "Execution Time: %lld nanoseconds.", elapsed_time);

    fclose(outputFile);

    return 0;
}
