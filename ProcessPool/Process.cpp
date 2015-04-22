//
//  Process.cpp
//  ProcessPool
//
//  Created by sen on 15-4-22.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#include "Process.h"

Process::ProcessId Process::getPid()
{
    return getpid();
}

Process::ProcessId Process::getPPid()
{
    return getppid();
}

Process::ProcessId Process::wait(Status *status)
{
    return ::wait(status);
}

Process::ProcessId Process::waitPid(ProcessId pid, Status *status, WaitOption opt)
{
    return ::waitpid(pid, status, opt);
}