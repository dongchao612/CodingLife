#include <iostream>
#include <thread>
#include "xdata.h"
using namespace std;

void ThreadMain()
{
    cout << "Thread Main" << endl;
}
int main()
{
    thread th(ThreadMain);
    cout << "test make" << endl;
    th.join();
    xdata d;
    return 0;
}