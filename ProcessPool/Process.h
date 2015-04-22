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
#include <iostream>

class Process
{
public:
    typedef pid_t ProcessId;
    typedef int Status;
    typedef int WaitOption;
    
    template<class Func, class ...Args>
    static ProcessId newInstance(Func&& func, Args&&... args)
    {
        ProcessId pid = 0;
        if((pid = fork()) < 0)
            return -1;
        else if(pid == 0)
        {
            func(std::forward<Args>(args)...);
            exit(0);
        }
        return pid;
    }
    
    static ProcessId getPid();
    static ProcessId getPPid();
    static ProcessId wait(Status *status = NULL);
    static ProcessId waitPid(ProcessId pid, Status *status, WaitOption opt);
    
private:
    Process();
    Process(const Process &);
    Process &operator=(const Process &);
    
};

#endif /* defined(__ProcessPool__Process__) */
