#include <iostream>
#include "icommand.h"
using namespace std;

class MacroCommandP
{
public:
    list<ICommand*> cmds;

    MacroCommandP(list<ICommand*> cmds) :
        cmds(cmds)
    {
    }
};

MacroCommand::MacroCommand(list<ICommand*> cmds) :
    imp(new MacroCommandP(cmds))
{
}

MacroCommand::~MacroCommand() { delete imp;}

void MacroCommand::execute()
{
    cout << "Start execute of MacroCommand" << endl;
    if(imp->cmds.empty())
        throw runtime_error ("Сommand list is empty");
    for(ICommand* i : imp->cmds)
    {
        try
        {
            i->execute();
        } catch (...) {
            throw runtime_error ("Pass the error up");
        }
    }
}

class RegisterCommandP
{
public:
    template<class T>
    using FuncType = function<T*()>;
    map<string, FuncType<ICommand>> *m_map;
    map<string, string> *m_scope;

    RegisterCommandP(map<string, FuncType<ICommand>> *m_map, map<string, string> *m_scope) :
        m_map(m_map),
        m_scope(m_scope)
    {
    }
};

template<class T>
RegisterCommand<T>::RegisterCommand(map<string, function<T*()>> *m_map, map<string, string> *m_scope) :
    imp(new RegisterCommandP(m_map, m_scope))
{
}

template<class T>
RegisterCommand<T>::~RegisterCommand() { delete imp;}

template<class T>
void RegisterCommand<T>::execute()
{
}

template<class T>
void RegisterCommand<T>::registerType(string key_s, string key_f, function<T*()> func)
{
        m_scope->emplace(key_s, key_f);
        m_map.emplace(key_f, func);
        cout << "Registre " << key_f << " in " << key_s << endl;
}
