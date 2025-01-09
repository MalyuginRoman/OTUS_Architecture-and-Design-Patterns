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

template<class T>
class RegisterCommand : public ICommand
{
public:
    RegisterCommand(std::map<string, function<T*()>> *m_map, std::map<string, string> *m_scope);
    ~RegisterCommand();
    std::map<string, function<T*()>> *m_map;
    std::map<string, string> *m_scope;
    void execute();
    void registerType(string key_s, string key_f, function<T*()> func);
private:
    class RegisterCommandP* imp;
};
