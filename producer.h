#pragma once
#include "object.h"

class producer
{
public:
    void start_game();
    void test_game(vector <char> message);
    void read_message(vector <char> message);

    objectVector vector_obj;
    string gameId_s, objectId_s, operationId_s, args;
    int gameId_i, objectId_i, operationId_i;
};
