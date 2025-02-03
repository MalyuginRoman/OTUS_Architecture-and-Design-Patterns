#pragma once
#include <iostream>
#include "icommand.h"
#include "minor.h"
#include "object.h"

const double eps = 10E-6;

struct coord_unterval
{
public:
  double Xmax;
  double Xmin;
  double Ymax;
  double Ymin;
};

struct system_okr
{
public:
  int id_syst_okr;
  bool isEmpty;
  int countObject;
  coord_interval XY;
  std::vector<int> obj_id;
};

class MoveCommandP
{
public:
  object* obj;
  std::map<int, system_okr>* p_map_a;
  std::map<int, system_okr>* p_map_b;

  MoveCommandP(std::map<int, system_okr>* p_map_a,
               std::map<int, system_okr>* p_map_b,
               object* obj) :
        p_map_a(p_map_a), p_map_b(p_map_b), obj(obj) {}
};

MoveCommand::MoveCommand(std::map<int, system_okr>* p_map_a,
                         std::map<int, system_okr>* p_map_b,
                         object* obj) :
        imp(new MoveCommandP(p_map_a, p_map_b, obj)) {}

MoveCommand::~MoveCommand() { delete imp; }

void MoveCommand::execute()
{
  CheckPositionCommand* cmd_search;
  std::cout << "CommandMove" << std::endl;
  if(imp->obj->place().placeX < 0 && imp->obj->place().placeY < 0)
    throw std::runtime_error ("Object not found");
  if(!imp->obj->getVelocity(imp->obj, 0))
    throw std::runtime_error ("Unknow velocity");
  std::cout << "Start position  [" << imp->obj->place().placeX << ", " << imp->obj->place().placeY << "]" << std::endl;
  if(!imp->obj->getPosition(imp->obj, dt))
    throw std::runtime_error ("Unknown position");
  else
  {
    cmd_search->excute(imp->p_map_a, imp->obj);
    cmd_search->excute(imp->p_map_b, imp->obj);
  }
  std::cout << "Finish position [" << imp->obj->place().placeX << ", " << imp->obj->place().placeY << "]" << std::endl;
}

int MoveCommand::get_Id_cmd()
{
  return CommandMove;
}

object* MoveCommand::obj() const
{
  return imp->obj;
}

std::map<int, system_okr>* MoveCommand::p_map_a() const
{
  return imp->p_map_a;
}

std::map<int, system_okr>* MoveCommand::p_map_b() const
{
  return imp->p_map_b;
}

void CheckPositionCommand::execute(std::map<int, system_okr>* p_map, object*obj)
{
  std::cout << "I am here!" << std::endl;
  std::cout << "Finish position [" << imp->obj->place().placeX << ", " << imp->obj->place().placeY << "]" << std::endl;

  bool change_place = false;
  int count_map_chize = p_map->size();
  for(int i = 0; i < count_map_chize; i++)
  {
    if(!p_map->at(i).isEmpty)
    {
      double x1 = p_map->at(i).XY.Xmin;
      double x2 = p_map->at(i).XY.Xmax;
      double y1 = p_map->at(i).XY.Ymin;
      double y2 = p_map->at(i).XY.Ymax;
      double current_X = obj->place().placeX;
      double current_Y = obj->place().placeY;
      bool isX = ((x1 - current_X) < eps) && (current_X - x2) < eps));
      bool isY = ((y1 - current_Y) < eps) && (current_Y - y2) < eps));
      if(isX && isY)
      {
        p_map->at(j).countObject--;
        if(p_map->at(i)countObject == 0)
          p_map->at(j).isEmpty = true;
        std::cout << "object id:" << p_map->at(i).obj_id.front() << " delete from " << p_map->at(i).id_syst_okr << " in p_map_c_a " << std::endl;
        p_map->at(j).obj_id.pop_back(id_obj);
        change_place = true;
      }
    }
    if(change_place)
    {
      double current_X = vector->at(i)->place().placeX;
      double current_Y = vector->at(i)->place().placeY;
      int count1 = p_map.size();
      for(int j = 0; j < count1; ++j)
      {
        double x1 = p_map->at(j).XY.Xmin;
        double x2 = p_map->at(j).XY.Xmax;
        double y1 = p_map->at(j).XY.Ymin;
        double y2 = p_map->at(j).XY.Ymax;
        bool isX = ((x1 - current_X) < eps) && (current_X - x2) < eps));
        bool isY = ((y1 - current_Y) < eps) && (current_Y - y2) < eps));
        if(isX && isY)
        {
          p_map->at(j).countObject++;
          p_map->at(j).isEmpty = false;
          int id_obj = obj->id();
          p_map->at(j).obj_id.push_back(id_obj);
          std::cout << "object id:" << p_map->at(j).obj_id.front() << " rewrite from " << p_map->at(j).id_syst_okr << " in p_map_c_a " << std::endl;
          bool change_place = false;
          break;
        }
      }
    }
  }
}
