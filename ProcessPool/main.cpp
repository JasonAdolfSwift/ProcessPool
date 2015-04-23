//
//  main.cpp
//  ProcessPool
//
//  Created by sen on 15-4-22.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#include <iostream>
#include "Process.h"
#include "MessageQueue.h"
#include "ShareMemory.h"

using namespace std;

void test()
{
    ShareMemory s;
    cout << s.createShareMemory(1234, 400) << endl;
    char *addr = (char *)s.getMemoryAddress();
    cout << addr << endl;
    sleep(3);
    cout << s.createShareMemory(1245, 450) << endl;
    cout << (char *)s.getMemoryAddress() << endl;
}

int main(int argc, const char * argv[])
{
    Process::newInstance(test);
    ShareMemory s;
    cout << s.createShareMemory(1234, 400) << endl;
    strcpy((char *)s.getMemoryAddress(), "Hello wo ca");
    strcat((char *)s.getMemoryAddress(), " wo le ge qu");
    sleep(3);
    cout << s.createShareMemory(1245, 450) << endl;
    strcpy((char *)s.getMemoryAddress(), "heheheheheheh");
    wait(NULL);
    return 0;
}

