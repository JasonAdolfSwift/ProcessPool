//
//  ShareMemory.cpp
//  ProcessPool
//
//  Created by sen on 15-4-23.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#include "ShareMemory.h"

ShareMemory::ShareMemory() : _id(0), _key(0), _addr(NULL)
{
    ;
}

ShareMemory::ShareMemory(MemoryKey create, MemoryKey size, SHMFlag flag) : _addr(NULL)
{
    _id = createShareMemory(create, size, flag);
}

ShareMemory::~ShareMemory()
{
    if(isFreed() != true)
        freeShareMemory();
}

const ShareMemory::MemoryId &ShareMemory::getMemoryId() const
{
    return _id;
}

const ShareMemory::MemoryKey &ShareMemory::getMemoryKey() const
{
    return _key;
}

ShareMemory::MemoryId ShareMemory::createShareMemory(MemoryKey key, MemorySize size, SHMPerm flag)
{
    _init();
    return _id = shmget(_key = key, size, IPC_CREAT | flag);
}

ShareMemory::MemoryId ShareMemory::openShareMemory(MemoryKey key, SHMFlag flag)
{
    _init();
    return _id = shmget(_key = key, 0, flag);
}

void ShareMemory::_init()
{
    if(!isFreed())
        freeShareMemory();
}

ShareMemory::MemoryAddress ShareMemory::getMemoryAddress(LinkAddress linkAddr, SHMFlag flag)
{
    if(!_addr)
        _addr = shmat(getMemoryId(), linkAddr, flag);
    return _addr;
}

bool ShareMemory::isFreed() const
{
    return getMemoryId() == 0;
}

bool ShareMemory::freeShareMemory()
{
    auto ret = (shmdt(getMemoryAddress()) == 0);
    ret &= (shmctl(getMemoryId(), IPC_RMID, 0) == 0);
    _addr = NULL;
    _key = 0;
    _id = 0;
    return ret;
}
