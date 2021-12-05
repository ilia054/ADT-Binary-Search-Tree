#include "Header.h"
/*Function name:Compare
input:void *, void*, elements to compare
output: returns 1 out of 3 options
BIGGER,SMALLER,EQUAL which are boolian expressions do indicate if a is bigger small or equal then compared element*/
BOOL  compare(void* a, void* b)
{
	if (*(int*)a > * (int*)b)
		return BIGGER;
	else if (*(int*)a < *(int*)b)
		return SMALLER;
	else return EQUAL;
}
/*Function name:print_char
input:void *,FILE pointer
output:Prints a char into designated file pointer*/
void print_char(void* a,FILE *out)
{
	fprintf(out,"%d ", *(int*)a);
	return;
}
void release(void* a)
{
	free(a);
	return;
}
int main()
{
	FILE* ins, * out;
	int cnt = 0;//We will add a counter to count number of nodes we have in tree so function 5 will be easier to handle
	if (!(ins = fopen("instructions.txt", "r")))
	{
		printf("could not open instructions file");
		return;
	}
	out = fopen("output.txt", "w");
	if (!out)
	{
		printf("could not open output file");
		return;
	}
	int option = 0;
	BOOL result; // result will hold the returned boolian expression returned from our functions
	Node root = NULL;
	int* data;// We will need to allocate memory for every keys so that our tree will hold diffrent elements
	/*We will keep scaning the instuction file to know what action would need to be preformed 
	and use cases to call the functions needed*/
	while (fscanf(ins, "%d", &option) == 1)
	{
		out = fopen("output.txt", "a");
		if (!out)
		{
			free_fun(root, release);
			printf("could not open output file");
			return;
		}
		switch (option)
		{
		/*Case 1 creates a tree node*/
		case 1 :
			cnt++;// we have another new node! need to 1 to node counter
			data= (int*)malloc(sizeof(int));//We will need to allocate memory so that our keys wont all have the same value
			if (NULL == data)
			{
				free_fun(root,release);
				printf("Memory allocation for Key input failed! program will now exit");
				exit(1);

			}
			fscanf(ins, "%d",data);
			result=AddNode(&root,data,compare);
			// If we got FALSE as a result an error occurdt, we will need to free tree and let user know 
			if (FALSE == result)
				fprintf(out, "Cannot create another Node using [%d]!",*(int*)data);
			 else fprintf(out, "%d was added to the tree\n", *data);
			break;
			/*Case 2 prints the keys in our tree using InOrder sequence*/
		case 2:
			Print_InOrder(root, print_char,out);
			fprintf(out, "\n");
			break;
			/*Case 3 prints the Height of the tree*/
		case 3:
			fprintf(out, "The Height of the tree is:%d\n",TreeDepth(root));
			break;
			/*Case 4 find the MAX value of key in out tree*/
		case 4:
			fprintf(out, "The max is:");
			result = Max_key(root, out, print_char);
			/*If we got FALSE as a result an error has happend, need to let user know*/
			if (FALSE == result)
				fprintf(out, "Cannot Find Max value in empty Tree,Please create a tree first!");
			fprintf(out, "\n");
			break;
			/*Case 5 prints the K amount of smallest Keys in out tree*/
		case 5:
			fscanf(ins, "%d", &option);
			/*Compare our count of nodes to user requested K print option, if K>CNT we cannot print K keys, let user know*/
			if (!option)
				fprintf(out, "Cannot print 0 keys!");

			else if (option > cnt)
				fprintf(out, "There are no %d elements in this tree", option);
			else
			{
				fprintf(out,"There are %d small elements in this tree:",option);
				PrintK_InOrder(root, print_char, out, &option);
			}
			fprintf(out, "\n");
			break;
		}
		fclose(out);
	}
	free_fun(root,release);

	

	return 0;
}
