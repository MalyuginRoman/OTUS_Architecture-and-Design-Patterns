#pragma once
#include <iostream>
#include "object.h"

class object;

class Message
{
public:
    int gameId;
    int objectId;
    int operationId;
    object* args;

    Message(int gameId, int objectId,
            int operationId, object* args)
    {
        this->gameId = gameId;
        this->objectId = objectId;
        this->operationId = operationId;
        this->args = args;
    }

    int getGameId()
    {
        return gameId;
    }
    int getObjectId()
    {
        return objectId;
    }
    int getOperationId()
    {
        return operationId;
    }
    object* getArgs()
    {
        return args;
    }
};

class Builder
{
public:
    int gameId;
    int objectId;
    int operationId;
    object* args;

    Builder* setGameId(int gameId)
    {
        this->gameId = gameId;
        return this;
    }
    Builder* setObjectId(int objectId)
    {
        this->objectId = objectId;
        return this;
    }
    Builder* setOperationId(int operationId)
    {
        this->operationId = operationId;
        return this;
    }
    Builder* setArgs(object* args)
    {
        this->args = args;
        return this;
    }
    Message* build()
    {
        return new Message(gameId, objectId, operationId, args);
    }
};
