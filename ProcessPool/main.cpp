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

using namespace std;

void fun(int a, int b, int c)
{
    cout << a << " " << b << " " << c << endl;
}

void test()
{
    MessageQueue q;
    q.createMsgQueue(1234, 0640);
    MMsg msg;
    if(q.msgRecv(&msg, sizeof(msg), Process::getPid()) == 0)
        cout << "no data" << endl;
    cout << msg.mText << endl;
}

int main(int argc, const char * argv[])
{
    MessageQueue q;
    q.createMsgQueue(1234, 0640);
    Process::ProcessId pid = Process::newInstance(test);
    MMsg msg;
    msg.type = pid;
    strcpy(msg.mText, "Hello world");
    q.msgSend(&msg, 0);
    wait(NULL);
    return 0;
}

