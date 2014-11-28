/* lambda.cpp - Checking out lambda subtleties.
 *
 * Lessons learned:
 *   - Use functional for returning lambdas.
 *   - Captured stack variables will still get corrupted.
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

std::function<void (int)> factory(int init)
{
    int n {5};
    return [=](int m) { cout << n + m << endl; }; // captures n by copy
}

// The reference to the variable on the stack is unlike a closure
// in the normal sense.
std::function<void (int)> factory_bad(int init)
{
    int n {5};
    return [&](int m) { cout << n + m << endl; }; // captures n by ref
}

int erase(int n)
{
    char buf[1024];
    char *p = buf, *end = p + sizeof buf;

    for (; p < end; ++p)
	*p = n++;
    return buf[sizeof buf - 1];
}

int main(void)
{
    vector<int> a {1,2,3};

    //auto fn = [&](int m) { cout << n + m << endl; }; // captures n by ref
    auto fn_nice = factory(5);
    auto fn_bad = factory_bad(5);
    erase(10000);			// clear stack just in case

    cout << "nice: " << endl;
    for_each(a.begin(), a.end(), fn_nice);
    cout << "bad: " << endl;
    for_each(a.begin(), a.end(), fn_bad);

    return 0;
}
