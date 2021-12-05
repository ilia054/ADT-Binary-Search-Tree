#ifndef bbb
#define bbb
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*We will need to compare elements in our prorgram,we will create expressions to make it easier to understand 
what option to take if X  is returned from compare function*/
typedef enum { FALSE,TRUE,BIGGER, SMALLER,EQUAL} BOOL;
/*Binary tree pointer */
typedef struct BinaryTree* Node;
/*We will have a compare function which intakes 2 voids and returns a BOOL */
typedef BOOL(*cmp_fun)(void* a, void* b);
/*print function which prints the Void *a element */
typedef void (*print)(void* a);
/*PrintK elements in tree will intake root,print func,file pointer and a int  * key value*/
typedef void (*printk)(Node root, print f1, FILE* out, int* k);
/*All of our general function declerations,more specific information can be found at general function file*/
typedef void (*free_element)(void* a);
BOOL AddNode(Node *root, void* data, cmp_fun f1);
int TreeDepth(Node root);
void Print_InOrder(Node root,print f1,FILE *out);
void PrintK_InOrder(Node root, print f1, FILE* out,int *k);
BOOL Max_key(Node root, FILE* out,print f1);
void free_fun(Node root,free_element f1);
#endif // !bbb
