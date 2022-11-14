#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n == 0 || n == 1) {
        return n;
    } else {
        return factorial(n - 2) + factorial(n - 1);
    }
}

int main()
{
    int x = factorial(5);
    cout << x << endl;
}