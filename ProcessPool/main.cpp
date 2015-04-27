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
#include "ProcessPool.h"
#include "ProcessTaskQueue.h"

using namespace std;

/* 只能使用内置类型 */
struct Task
{
    Task() {}
    Task(int a, int b) : a(a), b(b) {}
    void show()
    {
        cout << a << " " << b << endl;
    }
    int a;
    int b;
};

void test(Task &task)
{
    task.show();
}

void process(ProcessPool<decltype(test) *, Task, 9> &pool)
{
    sleep(1);
    Wrap<decltype(test) *, Task> wp;
    cout << pool.size() << endl;
    cout << pool.getTask(wp) << endl;
    wp.func(wp.args);
}

void process2(ProcessPool<decltype(test) *, Task, 9> &pool)
{
    sleep(2);
    Wrap<decltype(test) *, Task> wp;
    pool.getTask(wp);
    wp.func(wp.args);
}

int main(int argc, const char *argv[])
{
    ProcessPool<decltype(test) *, Task, 9> pool;
    Process child1;
    Process child2;
    cout << child1.open(process, pool) << endl;
    cout << child2.open(process2, pool) << endl;
    pool.addTask(Wrap<decltype(test) *, Task>(&test, Task(3, 4)));
    pool.addTask(Wrap<decltype(test) *, Task>(&test, Task(5, 7)));
    child1.waitChild();
    child2.waitChild();
    return 0;
}

