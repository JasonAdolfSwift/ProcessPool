//
//  MessageQueue.h
//  ProcessPool
//
//  Created by sen on 15-4-22.
//  Copyright (c) 2015年 sen. All rights reserved.
//

#ifndef __ProcessPool__MessageQueue__
#define __ProcessPool__MessageQueue__

#include <sys/msg.h>
#include <string.h>

typedef struct _msgStruct
{
    static const long MaxMsgLength = 2048;
    typedef long MsgType;
    MsgType type;
    char mText[MaxMsgLength];
}MMsg;

class MessageQueue
{
public:
    typedef key_t MsqKey;
    typedef int MsqId;
    typedef ssize_t MsgLength;
    typedef long MsgType;
    typedef int AccessPerm;
    typedef int IPCFlag;
    typedef long MsgGetType;
    
    MessageQueue();
    MessageQueue(MsqKey create, AccessPerm perm = 0640);
    ~MessageQueue();
    
public:
    MsqId createMsgQueue(MsqKey key, AccessPerm perm = 0640);
    bool isMsqExist(MsqKey key);
    bool closeMsgQueue();
    const MsqId &getMsqId() const;
    const MsqKey &getMsqKey() const;
    
    bool msgSend(void *msgContainer, MsgLength msglen, IPCFlag flag = 0);
    MsgLength msgRecv(void *msgContainer, MsgLength msglen, MsgGetType getType, IPCFlag flag = 0);
    
private:
    MsqId _id;
    MsqKey _key;
};


#endif /* defined(__ProcessPool__MessageQueue__) */
