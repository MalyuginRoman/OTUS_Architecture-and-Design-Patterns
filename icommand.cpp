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
