//
//  ProcessPool.h
//  ProcessPool
//
//  Created by sen on 15-4-24.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#ifndef __ProcessPool__ProcessPool__
#define __ProcessPool__ProcessPool__

#include "Process.h"
#include "MessageQueue.h"
#include "ProcessTaskQueue.h"

template<class Func, class Args>
struct Wrap
{
    Wrap() {}
    Wrap(Func _func, const Args &_args) : func(_func), args(_args) {}
    Func func;
    Args args;
};

template<class Func, class Args, int MaxSize>
class ProcessPool
{
public:
    ProcessPool();
    ~ProcessPool();
    
public:
    bool addTask(const Wrap<Func, Args> &wrap);
    bool getTask(Wrap<Func, Args> &wrap);
    
private:
    ProcessTaskQueue<Wrap<Func, Args>, MaxSize> *_queue;
};

template<class Func, class Args, int MaxSize> ProcessPool<Func, Args, MaxSize>::ProcessPool() :_queue(new ProcessTaskQueue<Wrap<Func, Args>, MaxSize>())
{
    ;
}
                                                                                                      

template<class Func, class Args, int MaxSize> ProcessPool<Func, Args, MaxSize>::~ProcessPool()
{
    delete _queue;
}

template<class Func, class Args, int MaxSize> bool ProcessPool<Func, Args, MaxSize>::addTask(const Wrap<Func, Args> &wrap)
{
    return _queue->addTask(wrap);
}

template<class Func, class Args, int MaxSize> bool ProcessPool<Func, Args, MaxSize>::getTask(Wrap<Func, Args> &wrap)
{
    auto ret = _queue->getTask(wrap);
    return ret;
}


#endif /* defined(__ProcessPool__ProcessPool__) */
