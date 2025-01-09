#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <functional>
#include <memory>
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

class AddLastCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute AddLastCommand" << endl;
    }
};

class LogerCommand : public ICommand
{
public:
    void execute()
    {
        cout << "Start execute LogerCommand" << endl;
    }
};

class EmptyCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute EmptyCommand" << endl;
    }
};

class HardStopCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute HardStopCommand" << endl;
    }
};

class SoftStopCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute SoftStopCommand" << endl;
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
    RegisterCommand(map<string, function<ICommand*()>> *m_map, map<string, string> *m_scope);
    ~RegisterCommand();
    map<string, function<ICommand*()>>* m_map;
    map<string, string>* m_scope;
    void execute();
    void registerType(string key_s, string key_f, function<ICommand*()> func);
private:
    class RegisterCommandP* imp;
};
