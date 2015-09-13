#define ItemType char

typedef struct{
        int top;
        int size;
        ItemType *items;
}Stack;

Stack *createStack(int);
int push(Stack*, ItemType);
int pop(Stack*, ItemType*);
int peek(Stack*, ItemType*);
void printStack(Stack*);
int sizeStack(Stack*);
int isEmptyStack(Stack*);
int isFullStack(Stack*);

Stack *createStack(int initialSize)
{
	Stack* stack = (Stack*) calloc(1, sizeof(Stack));
	stack->size=initialSize;
    stack->top=0;
    stack->items = (ItemType*) calloc(initialSize, sizeof(ItemType));
    if (!stack->items)
    {
		free(stack);
		stack=NULL;
	}
    return stack;
}

int push(Stack* stack, ItemType item)
{
    int i, response=1;
    ItemType *p;
    if (stack->top == stack->size)
    {
		p = (ItemType*) malloc(sizeof(ItemType)*stack->size*2);
		if (p)
		{
			for (i=0; i<stack->top; i++)
                p[i] = stack->items[i];
			free(stack->items);
			stack->items = p;
			stack->size *= 2;
		}
		else
            response = 0;
	}
    stack->items[stack->top]=item;
    stack->top++;
    return response;
}

int pop(Stack* stack, ItemType* removedItem)
{
	int response=1;
    if (stack->top > 0)
    {
		stack->top--;
		*removedItem = stack->items[stack->top];
	}
	else
		response=0;
	return response;
}

int peek(Stack* stack, ItemType* topItem)
{
	int top_exists=0;
	if (stack->top > 0)
	{
		top_exists=stack->top;
		*topItem = stack->items[stack->top-1];
	}
	return top_exists;
}

void printStack(Stack* stack)
{
    int i;
    printf("\n");
    if (stack->top > 0)
        for (i=0; i<stack->top; i++)
            printf("Position %d: %d\n", i+1, stack->items[i]);
    else
        printf("The stack is empty.\n");
}

int sizeStack(Stack* stack)
{
    int size;
    if (stack->top > 0)
        size = stack->top;
    else
        size = 0;
    return size;
}

int isEmptyStack(Stack* stack)
{
	int empty=0;
	if (stack->top == 0)
		empty = 1;
	return empty;
}

int isFullStack(Stack* stack)
{
	int full=0;
	if (stack->top == stack->size)
        full = 1;
	return full;
}

void clearStack(Stack* stack)
{
    stack->top = 0;
}
