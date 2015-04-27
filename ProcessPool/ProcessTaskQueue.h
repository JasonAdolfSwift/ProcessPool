//
//  ProcessTaskQueue.h
//  ProcessPool
//
//  Created by sen on 15-4-24.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#ifndef __ProcessPool__ProcessTaskQueue__
#define __ProcessPool__ProcessTaskQueue__

#include <algorithm>
#include "ShareMemory.h"

template<class FuncWrap, int MaxSize>
class ProcessTaskQueue
{
public:
    typedef unsigned long ULong;
    
    ProcessTaskQueue();
    ~ProcessTaskQueue();
    
public:
    bool addTask(const FuncWrap &pkg);
    bool getTask(FuncWrap &pkg);
    ULong size() const;
    bool isEmpty() const;
    bool isFull() const;
    ULong &getFrontPointer() const;
    ULong &getRearPointer() const;
    
private:
    ShareMemory _shm;
    mutable ULong *_integers;
    FuncWrap *_tasks;
};

template<class FuncWrap, int MaxSize> ProcessTaskQueue<FuncWrap, MaxSize>::ProcessTaskQueue()
{
    _shm.createShareMemory(12346, sizeof(ULong) * 2 + sizeof(FuncWrap) * MaxSize);
    _integers = static_cast<ULong *>(_shm.getMemoryAddress());
    _tasks = static_cast<FuncWrap *>(static_cast<void *>(_integers + 2)); /* 偏移2个ULong后面的都是FuncWrap的内容 */
}

template<class FuncWrap, int MaxSize> ProcessTaskQueue<FuncWrap, MaxSize>::~ProcessTaskQueue()
{
    _shm.freeShareMemory();
}

template<class FuncWrap, int MaxSize> typename ProcessTaskQueue<FuncWrap, MaxSize>::ULong &ProcessTaskQueue<FuncWrap, MaxSize>::getFrontPointer() const
{
    return _integers[0];
}

template<class FuncWrap, int MaxSize> typename ProcessTaskQueue<FuncWrap, MaxSize>::ULong &ProcessTaskQueue<FuncWrap, MaxSize>::getRearPointer() const
{
    return _integers[1];
}

template<class FuncWrap, int MaxSize> bool ProcessTaskQueue<FuncWrap, MaxSize>::addTask(const FuncWrap &pkg)
{
    if(isFull())
        return false;
    _tasks[getRearPointer()++] = pkg;
    getRearPointer() %= MaxSize;
    return true;
}

template<class FuncWrap, int MaxSize> bool ProcessTaskQueue<FuncWrap, MaxSize>::getTask(FuncWrap &pkg)
{
    if(isEmpty())
        return false;
    pkg = _tasks[getFrontPointer()++];
    getFrontPointer() %= MaxSize;
    return true;
}

template<class FuncWrap, int MaxSize> typename ProcessTaskQueue<FuncWrap, MaxSize>::ULong ProcessTaskQueue<FuncWrap, MaxSize>::size() const
{
    return (getRearPointer() + MaxSize - getFrontPointer()) % MaxSize;
}

template<class FuncWrap, int MaxSize> bool ProcessTaskQueue<FuncWrap, MaxSize>::isEmpty() const
{
    return getRearPointer() == getFrontPointer();
}

template<class FuncWrap, int MaxSize> bool ProcessTaskQueue<FuncWrap, MaxSize>::isFull() const
{
    return (getRearPointer() + 1) % MaxSize == getFrontPointer();
}

#endif /* defined(__ProcessPool__ProcessTaskQueue__) */
