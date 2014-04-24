/**
 * Official solution for task NUMBERS.
 *
 * Simply prints numbers between A and B. If A < B, then there are exactly
 * (B - A - 1) numbers in between. The only catch is that the task statement
 * does not say whether A < B, so the program checks for this case.
 *
 * Author: Linas Petrauskas
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    cout << (b - a - 1) << endl;
    for (int i = a + 1; i < b; i++) {
        cout << i;
        if (i == b - 1) {
            cout << endl;
        } else {
            cout << " ";
        }
    }
    return 0;
}
