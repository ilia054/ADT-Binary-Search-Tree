#include "Header.h"
/*A structure for our binary tree node*/
typedef struct BinaryTree
{
	void* key;
	struct BinaryTree* right;
	struct BinaryTree* left;
};
/*Function Name:Add Node
Input:Node ptr,void * value, compare function
Output: Creates a tree node if value is not found in our tree, if succesfull returns TRUE=1 else returns FALSE=0 to indicate
Weather we had success or failure*/
BOOL AddNode(Node *root, void* data, cmp_fun f1)
{
	BOOL result;
	Node tmp,parent;
	tmp = *root;
	parent = *root;
	if (NULL == tmp)// Check to see if we even have a tree crated, so we wont do extra work
	{
		tmp = (Node)malloc(sizeof(struct BinaryTree));
		if (NULL == tmp)
			return FALSE;
		else
		{
			tmp->key = data;
			tmp->left = NULL;
			tmp->right = NULL;
			*root = tmp;
			
			return TRUE;
		}
	}
	// if prior condition was not met we will need to know where to add our new node
	else
	{
		/*Algorithem:We will go throught our tree and always check to see which side we need to go 
		if our compare function returns equal, we already have that node in our tree we will send FALIURE and finish program
		else we will go through tree, if we recive a bigger result from cmp fun, we will go to right side of tree, if we return smaller
			we will go through the left side*/
		while (NULL != tmp)
		{
			parent= tmp;
			result = f1(tmp->key, data);
			if (EQUAL == result)
				return FALSE;
			else if (BIGGER == result)
				tmp = tmp->left;
			else tmp = tmp->right;
		}
		/*We found to which node we need to add our current key*/
		tmp = (Node)malloc(sizeof(struct BinaryTree));
		if (NULL == tmp)
			return FALSE;
		tmp->key = data;
		tmp->left = NULL;
		tmp->right = NULL;
		if (BIGGER == result)
			parent->left = tmp;
		else parent->right= tmp;
	}
	return TRUE;

}
/*Function name:TreeDepth
Input:Node pointer
output:Depth of tree*/
int TreeDepth(Node root)
{
	int right=0, left=0;
	if (NULL == root)
		return -1;
	left = 1 + TreeDepth(root->left);
	right = 1 + TreeDepth(root->right);
	if (left > right)
		return left;
	else return right;
};
/*Function name:Print_InOrder
Input:Node pointer, print function,file output*/
void Print_InOrder(Node root, print f1,FILE *out)
{
	/*Algorithem:We will go into the left side of tree to ensure we get lowest value first
	after we hit a NULL we know we reached the smallest value in tree, we will print in and go 
	to right side of tree until we reach another NULL*/
	if (NULL == root)
		return;
	else Print_InOrder(root->left, f1,out);
	f1(root->key,out);
    Print_InOrder(root->right, f1,out);
	return;
}
/*Function name:Max_Key
Input:Node pointer,File pointer, print func 
output:Finds the Biggest value key in tree, prints it to file,and returns FALSE or TRUE to indicate success of failure of mission*/
BOOL Max_key(Node root, FILE* out, print f1)
{
	Node helper;
	helper = root;
	if (NULL == root)
		return FALSE;//If our root is a NULL we dont have any tree, no need to go further
	/*Other wise we will go throught all of out right side of tree, since the max is on the right side*/
	else
	{
		while (NULL != helper->right)
		{
			helper = helper->right;
		}
		f1(helper->key, out);
	}
	return TRUE;
};
/*Function name:PrintK_InOrder
input:Node pointer,Print function,File pointer,int pointer
output:Prints the K smallest keys in our tree */
void PrintK_InOrder(Node root, print f1, FILE* out, int* k)
{
	/*Algorithem:We will go into our left side of the tree until we hit a null
	null=smallest key is reached,we will start printing and reduce K by 1 each time
	we will keep priting until key!=0, when we printed K amount of keys we will stop function*/
	if ((*k)==0)
		return;
    if (NULL == root)
		return;
	 else PrintK_InOrder(root->left, f1, out, k);
	if ((*k))
	{
		f1(root->key, out);
		(*k)--;
	}
	PrintK_InOrder(root->right, f1, out, k);
	return;
};
/*Function name:Free_fun
input:Node pointer
output:Frees the key in the node then frees the node itself*/
void free_fun(Node root,free_element f1)
{
	/*Algorithem:We will go to the leafs in our tree, release the key which is void *, then release the node itself
	until the tree is empty*/
	if (NULL == root)
		return;
	free_fun(root->left,f1);
	free_fun(root->right,f1);
	f1(root->key);
	free(root);
	return;
};