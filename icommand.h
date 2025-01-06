#pragma once
#include <list>
using namespace std;

class ICommand
{
public:
    virtual void execute() = 0;
};

class MoveCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute MoveCommand" << endl;
    }
};

class RotateCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute RotateCommand" << endl;
    }
};

class CheckCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute CheckCommand" << endl;
    }
};

class BurnCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute BurnCommand" << endl;
    }
};

class MacroCommand : public ICommand
{
public:
    MacroCommand(list<ICommand*> cmds);
    ~MacroCommand();
    list<ICommand*> cmds;
    void execute();
private:
    class MacroCommandP* imp;
};

class RegisterCommand : public ICommand
{
public:
    RegisterCommand(list<string> scope, list<string> command);
    ~RegisterCommand();
    list<string> scope;
    list<string> command;
    void execute();
private:
    class RegisterCommandP* imp;
};
