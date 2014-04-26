#include <iostream>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    if (a > b)
        swap(a, b);
    if (b - a > 1) {
        cout << (b - a - 1) << endl;
        cout << a + 1;
        for (long long i = a + 2; i <= b - 1; i++)
            cout << ' ' << i;
        cout << endl;
    } else
        cout << 0 << endl;
}
