/* lambda.cpp - Checking out lambda subtleties.
 *
 * Lessons learned:
 *   - Use functional for returning lambdas.
 *   - Captured stack variables will still get corrupted.
 *   - A unique_ptr destroys its referent when it is destroyed, even
 *     if there's a reference to it surviving.
 *   - The same goes for a shared_ptr when the lambda captures it by
 *     reference.  To avoid early destruction, it would have to be
 *     copied as in factory_sp_copy.
 *
 * All this stuff makes sense, but it seems like they'd have compiler
 * warnings or something for these subtleties.
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Int {
public:
    int n;
    Int(int init, string name) :n{init}, lab{name} {}
    ~Int() { cout << lab << " is dying" << endl; }
private:
    string lab;
};

// Note that the Int dies when the function returns, so that the
// lambda uses garbage when it gets called.
std::function<void (int)> factory_up(int init)
{
    unique_ptr<Int> p {new Int(init, "Int_up")};

    return [&](int m) { cout << p->n + m << endl; }; // captures p by ref
}

// Note that the Int dies when the function returns, so that the
// lambda uses garbage when it gets called.
std::function<void (int)> factory_sp(int init)
{
    shared_ptr<Int> p {new Int(init, "Int_sp")};

    return [&](int m) { cout << p->n + m << endl; }; // captures p by ref
}

std::function<void (int)> factory_sp_copy(int init)
{
    shared_ptr<Int> p {new Int(init, "Int_sp_copy")};

    return [=](int m) { cout << p->n + m << endl; }; // captures p by copy
}

std::function<void (int)> factory(int init)
{
    int n {init};
    return [=](int m) { cout << n + m << endl; }; // captures n by copy
}

// The reference to the variable on the stack is unlike a closure
// in the normal sense.
std::function<void (int)> factory_bad(int init)
{
    int n {init};
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
    auto fn_up = factory_up(5);
    auto fn_sp = factory_sp(5);
    auto fn_sp_cp = factory_sp_copy(5);
    erase(10000);			// clear stack just in case

    cout << "nice: " << endl;
    for_each(a.begin(), a.end(), fn_nice);
    cout << "bad: " << endl;
    for_each(a.begin(), a.end(), fn_bad);
    cout << "unique_ptr: " << endl;
    for_each(a.begin(), a.end(), fn_up);
    cout << "shared_ptr: " << endl;
    for_each(a.begin(), a.end(), fn_sp);
    cout << "shared_ptr copy: " << endl;
    for_each(a.begin(), a.end(), fn_sp_cp);

    return 0;
}
