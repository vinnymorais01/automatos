#define Item State*

typedef struct state
{
	int id;
	struct state** trans;
	struct state* last; //facilitador
}State;

typedef struct{
        int top;
        int size;
        Item *items;
}StackState;

StackState *createStackState(int);
int pushState(StackState*, Item);
int popState(StackState*, Item*);
int peekState(StackState*, Item*);
int sizeStackState(StackState*);
int isEmptyStackState(StackState*);
int isFullStackState(StackState*);

StackState *createStackState(int initialSize)
{
	StackState* stack = (StackState*) calloc(1, sizeof(StackState));
	stack->size=initialSize;
    stack->top=0;
    stack->items = (Item*) calloc(initialSize, sizeof(Item));
    if (!stack->items)
    {
		free(stack);
		stack=NULL;
    }
    return stack;
}

int pushState(StackState* stack, Item item)
{
    int i, response=1;
    Item *p;
    if (stack->top == stack->size)
    {
		p = (Item*) malloc(sizeof(Item)*stack->size*2);
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

int popState(StackState* stack, Item* removedItem)
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

int peekState(StackState* stack, Item* topItem)
{
	int top_exists=0;
	if (stack->top > 0)
	{
		top_exists=stack->top;
		*topItem = stack->items[stack->top-1];
	}
	return top_exists;
}

int sizeStackState(StackState* stack)
{
    int size;
    if (stack->top > 0)
        size = stack->top;
    else
        size = 0;
    return size;
}

int isEmptyStackState(StackState* stack)
{
	int empty=0;
	if (stack->top == 0)
		empty = 1;
	return empty;
}

int isFullStackState(StackState* stack)
{
	int full=0;
	if (stack->top == stack->size)
        full = 1;
	return full;
}

void clearStackState(StackState* stack)
{
    stack->top = 0;
}
