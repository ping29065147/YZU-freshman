// filename: StackType.h
#include <stdexcept>
using std::runtime_error;
// MAX_ITEMS: the maximum number of items on the stack. 
const int MAX_ITEMS = 5;

// Exception class thrown by Push when stack is full.
class FullStack : public runtime_error
{
    public:
        // Add exception message(Stack is Full!) when the constructor is initialized
        FullStack()
			:runtime_error("   Stack is Full!"){}
};

// Exception class thrown by Pop and Top when stack is emtpy.
class EmptyStack : public runtime_error
{
    public:
        // Add exception message(Stack is Empty!) when the constructor is initialized
        EmptyStack()
			:runtime_error("   Stack is Empty!") {}
};

class StackType
{
    public:

        // Class constructor.
        StackType();

        // Function: Determines whether the stack is full.
        bool IsFull() const;

        // Function: Determines whether the stack is empty.
        bool IsEmpty() const;

        // Function: Adds newItem to the top of the stack.
        // If (stack is full), FullStack exception is thrown;
        // otherwise, newItem is at the top of the stack.
        void Push(char item);

        // Function: Removes top item from the stack.
        // If (stack is empty), EmptyStack exception is thrown;
        // otherwise, top element has been removed from stack.
        void Pop();

        // Function: Returns a copy of top item on the stack.
        // If (stack is empty), EmptyStack exception is thrown;
        // otherwise, top element has been removed from stack.
        char Top();

    private:
        int top;
        char items[MAX_ITEMS];		
};

StackType::StackType()
	:top(0)
{
}

bool StackType::IsFull() const
{
	if (top == MAX_ITEMS)
		return true;
	return false;
}

bool StackType::IsEmpty() const
{
	if (top == 0)
		return true;
	return false;
}

void StackType::Push(char item)
{
	if (!IsFull()) {
		items[top] = item;
		top++;
	}
	else
		throw FullStack();
}

void StackType::Pop()
{
	if (!IsEmpty())
		top--;
	else
		throw EmptyStack();
}

char StackType::Top()
{
	if (!IsEmpty())
		return items[top-1];
	else
		throw EmptyStack();
}