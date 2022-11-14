#include <iostream>
#include <string>
using namespace std;
// 这里采用char有点限制：每一步运算结果都要为一个字符
const string nifixExpression = "<<1*<7-<1+1>>>*1>-<2+<1+1>>";
string postfixExpression;

typedef struct LinkedStack
{
    char data;
    struct LinkedStack* next;
}Node, *Stack;

typedef struct LinkedStackPtr
{
    Stack top;
    int count;
}NodePtr, *StackPtr;

void initStack(StackPtr stackPtr)
{
    stackPtr->top = nullptr;
    stackPtr->count = 0;
}

bool emptyJudge(StackPtr stackPtr)
{
    if (stackPtr->top == nullptr && stackPtr->count == 0) {
        return true;
    } else {
        return false;
    }
}

int elementJudge(const char& element)
{
    if (element == '<') {
        return 1;
    } else if (element == '>') {
        return 2;
    } else if (element == '+') {
        return 3;
    } else if (element == '-') {
        return 3;
    } else if (element == '*') {
        return 4;
    } else if (element == '/') {
        return 4;
    } else {
        return 0;
    }
}

void printStack(const StackPtr stackPtr)
{
    Node* p = stackPtr->top;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl << "Stack length is: " << stackPtr->count << endl;
}

void pushStack(StackPtr stackPtr, const char& value)
{
    Node* p = new Node;
    p->next = stackPtr->top;
    stackPtr->top = p;
    p->data = value;
    ++stackPtr->count;
}

char popStack(StackPtr stackPtr)
{
    if (stackPtr->top == nullptr) {
        cout << "Invalid operator! Stack is empty!" << endl;
        return '$';
    }
    Node* p = stackPtr->top;
    char element = p->data;
    stackPtr->top = p->next;
    --stackPtr->count;
    delete p;
    return element;
}

/**中缀转后缀算法说明：
 * 从左到右处理各个元素，直到末尾，可能遇到三种情况
 * 1.遇到操作数，直接加入后缀表达式
 * 2.遇到界限符，遇到"<"直接入栈；遇到">"则依次弹出栈内运算符，并加入后缀表达式，
 * 若遇到"<"或栈空则停止，若为"<"则还需弹出"<"，之后再把当前运算符压入栈
 * 3.遇到运算符，依次弹出栈中优先级高于或等于当前运算符的所有运算符，并加入后缀表达式，
 * 若遇到"<"或栈空则停止，若为"<"不要弹出"<"，之后再把当前运算符压入栈
 * 
 * 按照上述方法处理完所有运算符后，将栈中剩余运算符依次弹出，并加入后缀表达式
 */
void nifixToPostfix(StackPtr stackPtr)
{
    // nifixExpression = "<<1*<7-<1+1>>>*1>-<2+<1+1>>"
    for (int i = 0; i < nifixExpression.size(); ++i) {
        int label = elementJudge(nifixExpression[i]);
        Node* p = stackPtr->top;
        // switch里面不能进行声明！
        switch (label)
        {
        case 0: // 操作数
            postfixExpression += nifixExpression[i];
            break;
        case 1: // '<'
            pushStack(stackPtr, nifixExpression[i]);
            break;
        case 2: // '>'
            while (p->data != '<') {
                p = p->next;
                postfixExpression += popStack(stackPtr);
            }
            popStack(stackPtr);
            break;
        case 3: // '+' '-'
            while (p != nullptr && p->data != '<') {
                p = p->next;
                postfixExpression += popStack(stackPtr);
            }
            pushStack(stackPtr, nifixExpression[i]);
            break;
        case 4: // '*' '/'
            while (p != nullptr && p->data != '<' && p->data != '+' && p->data != '-') {
                p = p->next;
                postfixExpression += popStack(stackPtr);
            }
            pushStack(stackPtr,nifixExpression[i]);
            break;
        default:
            cout << "nifixToPostfix error!" << endl;
            break;
        }
    }
    Node* q = stackPtr->top;
    while (q != nullptr) {
        q = q->next;
        postfixExpression += popStack(stackPtr);
    }
}

void expressionPrint(const string& s)
{
    for (int i = 0; i < s.size(); ++i) {
        cout << s[i] << " ";
    }
    cout << endl;
}

void testAll()
{
    NodePtr s_ptr;
    initStack(&s_ptr);

    expressionPrint(nifixExpression);
    nifixToPostfix(&s_ptr);
    expressionPrint(postfixExpression);
}

int main()
{
    testAll();
    return 0;
}