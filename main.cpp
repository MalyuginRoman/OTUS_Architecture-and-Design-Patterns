#include <iostream>
#include "ioc.h"
#include "icommand.h"
#include "object.h"
#include "producer.h"

int main(int ac, char **av)
{
    objectVector vector;
    int count = 2;
    for(int i = 0; i < count; i++)
    {
        int id = i;
        coord place;
        react state;

        place.placeX = 0.;
        place.placeY = 0.;
        place.angular = 45 * i;

        state.velocity = 100;
        state.angularVelocity = 20;
        state.fuel = 10;

        vector.add(id, state, place);
    }

    for(int i = 0; i < count; i++)
    {
        std::cout << vector.at(i)->id() << ":" << vector.at(i)->state().velocity << "," << vector.at(i)->state().angularVelocity << "," << vector.at(i)->state().fuel
                       << "," << vector.at(i)->place().placeX << "," << vector.at(i)->place().placeY << "," << vector.at(i)->place().angular << std::endl;
    }

    IocContainer<ICommand> ioc;

    // Scope1 not fuel
    ioc.registerType<MoveCommand>(
                "Scope1",
                "MoveCommand",
                [] { return new MoveCommand(); });
    ioc.registerType<RotateCommand>(
                "Scope1",
                "RotateCommand",
                [] { return new RotateCommand(); });

    ioc.resolved("MoveCommand", vector.at(0))->execute();
    ioc.resolved("RotateCommand", vector.at(0), vector.at(1))->execute();

    // Scope2 with fuel
    // формируем макрокоманды
    CheckCommand *cmd_check = new CheckCommand();
    MoveCommand *cmd_move = new MoveCommand();
    RotateCommand *cmd_rotate = new RotateCommand();
    BurnCommand *cmd_burn = new BurnCommand();
    list<ICommand*> cmd_list;
    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_move);
    cmd_list.push_back(cmd_burn);
    ioc.registerType<MacroCommand>(
                "Scope2",
                "MacroCommand1",
                [&cmd_list]() { return new MacroCommand(cmd_list); });
    ioc.resolved("MacroCommand1", vector.at(0))->execute();
    cmd_list.clear();


    cmd_list.push_back(cmd_check);
    cmd_list.push_back(cmd_rotate);
    cmd_list.push_back(cmd_burn);
    ioc.registerType<MacroCommand>(
                "Scope2",
                "MacroCommand2",
                [&cmd_list]() {return new MacroCommand(cmd_list); });

    ioc.resolved("MacroCommand2", vector.at(0), vector.at(1))->execute();

    return 0;
}
