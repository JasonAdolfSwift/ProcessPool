//
//  ShareMemory.h
//  ProcessPool
//
//  Created by sen on 15-4-23.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#ifndef __ProcessPool__ShareMemory__
#define __ProcessPool__ShareMemory__

#include <sys/shm.h>
#include <stdlib.h>

class ShareMemory
{
public:
    typedef key_t MemoryKey;
    typedef int MemoryId;
    typedef int SHMFlag;
    typedef int SHMPerm;
    typedef size_t MemorySize;
    typedef void *MemoryAddress;
    typedef const void *LinkAddress;
    
    ShareMemory();
    ShareMemory(MemoryKey create, MemoryKey size, SHMFlag flag = 0640);
    ~ShareMemory();
    
public:
    const MemoryId &getMemoryId() const;
    const MemoryKey &getMemoryKey() const;
    MemoryId createShareMemory(MemoryKey key, MemorySize size, SHMPerm flag = 0640);
    MemoryId openShareMemory(MemoryKey key, SHMFlag flag = 0640);
    MemoryAddress getMemoryAddress(LinkAddress linkAddr = NULL, SHMFlag flag = 0);
    bool freeShareMemory();
    bool isFreed() const;
    
private:
    void _init();
    
private:
    MemoryKey _key;
    MemoryId _id;
    MemoryAddress _addr;
};

#endif /* defined(__ProcessPool__ShareMemory__) */
