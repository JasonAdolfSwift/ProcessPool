//
//  MessageQueue.cpp
//  ProcessPool
//
//  Created by sen on 15-4-22.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#include "MessageQueue.h"

MessageQueue::MessageQueue() : _key(0), _id(0)
{
    ;
}

MessageQueue::MessageQueue(MsqKey create, AccessPerm perm) : _key(create), _id(0)
{
    _id = createMsgQueue(create, perm);
}

MessageQueue::~MessageQueue()
{
    ;
}

const MessageQueue::MsqId &MessageQueue::getMsqId() const
{
    return _id;
}

const MessageQueue::MsqKey &MessageQueue::getMsqKey() const
{
    return _key;
}

bool MessageQueue::isMsqExist(MsqKey key)
{
    return msgget(key, IPC_EXCL) == -1;
}

MessageQueue::MsqId MessageQueue::createMsgQueue(MsqKey key, AccessPerm perm)
{
    _key = key;
    return _id = msgget(key, IPC_CREAT | perm);
}

bool MessageQueue::closeMsgQueue()
{
    return msgctl(getMsqId(), IPC_RMID, NULL) == 0;
}

bool MessageQueue::msgSend(void *msgContainer, MsgLength msglen, IPCFlag flag)
{
    return msgsnd(getMsqId(), msgContainer, msglen, flag) == 0;
}

MessageQueue::MsgLength MessageQueue::msgRecv(void *msgContainer, MsgLength msglen, MsgGetType getType, IPCFlag flag)
{
    return msgrcv(getMsqId(), msgContainer, msglen, getType, flag);
}
