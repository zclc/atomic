#include "atomic_opt_asm.h"

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    int a = 1;
    int * ptr = new int(1);

    cout << "ptr == expect ptr should be 2, res should be 1" << endl;
    int res = atomic_cas(ptr, 1, 2);

    cout << "*ptr = " << *ptr <<endl;
    cout << "res = " << res << endl;

    cout << "ptr != expect ptr should be 2, res should be 2" << endl;
    int res2 = atomic_cas(ptr, 1, 2);

    cout << "*ptr = " << *ptr <<endl;
    cout << "res2 = " << res2 << endl;

    return 0;
}