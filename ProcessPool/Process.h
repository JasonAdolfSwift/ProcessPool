//
//  Process.h
//  ProcessPool
//
//  Created by sen on 15-4-22.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#ifndef __ProcessPool__Process__
#define __ProcessPool__Process__

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <iostream>

class Process
{
public:
    typedef pid_t ProcessId;
    typedef int Status;
    typedef int WaitOption;
    typedef int SignalType;
    Process() {}
    ~Process() {}
    
public:
    template<class Func, class ...Args>
    ProcessId open(Func&& func, Args&&... args)
    {
        if((_id = fork()) < 0)
            return -1;
        else if(_id == 0)
        {
            func(std::forward<Args>(args)...);
            exit(0);
        }
        return _id;
    }
    
    ProcessId getChildId();
    bool killChild();
    ProcessId waitChild(Status *status = NULL, WaitOption opt = 0);
    static ProcessId getPid();
    static ProcessId getPPid();
    static ProcessId wait(Status *status = NULL);
    static ProcessId waitPid(ProcessId pid, Status *status, WaitOption opt);
    static bool kill(ProcessId pid, SignalType sig);
    
private:
    ProcessId _id;
    
private:
    Process(const Process &);
    Process &operator=(const Process &);
    
};

#endif /* defined(__ProcessPool__Process__) */
