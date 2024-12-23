#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>

int main()
{
      std::filesystem::path current_path = std::filesystem::current_path();
      std::filesystem::path file_path(current_path);
      std::list<std::string> list1, list2, list11, list12, list13, list14,
                             list3, list4, list41, list42, list43, list44;
      std::list<std::string> listFileName;

      std::cout << file_path.parent_path() << std::endl;

      for (auto &p : std::filesystem::recursive_directory_iterator(file_path.parent_path()))
        {
          if(p.path().extension() == ".h")
          {
            std::cout << p.path().parent_path() << " _ " << p.path().filename() << std::endl;
            
            std::string current_file = p.path().filename().generic_string();
            std::string readFileName = p.path().parent_path().generic_string() + "/" +
                                  p.path().filename().generic_string();
            std::fstream readFile(readFileName);
            if (!readFile.is_open())
            {
                std::cout << "File " << readFileName << " not be opened" << std::endl;
            }
            else
            {
                if(current_file == "imoving.h")
                {
                    std::string str;
                    while(readFile >> str)
                    {
                        if(str == "virtual")
                        {
                            readFile >> str;
                            list1.push_back(str);
                            readFile >> str;
                            list2.push_back(str);
                            readFile >> str;
                            readFile >> str;
                            list11.push_back(str);
                            readFile >> str;
                            list12.push_back(str);
                            readFile >> str;
                            list13.push_back(str);
                            readFile >> str;
                            list14.push_back(str);
                        }
                    }
                    std::string fileWriteName =
                            p.path().parent_path().generic_string() + "/" +
                            p.path().filename().replace_extension(".cpp").generic_string();
                    std::cout << fileWriteName << std::endl;
                    listFileName.push_back(fileWriteName);
                    std::ofstream f;
                    f.open(fileWriteName, ios::out);
                    {
                        f << "#include \"object.h\"" << std::endl;
                        f << "class IMoving" << std::endl;
                        int count = list1.size();
                        for(int i = 0; i < count; i++)
                        {
                            f << list1.front()  << " " << list2.front() << "("
                              << list11.front() << " " << list12.front();
                            if(i % 2 == 0)
                                f << " " << list13.front()  << " " << list14.front();
                            f << ")" << std::endl;
                            f << "{" << std::endl;
                                if(list2.front() == "getPosition")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IMovable:position.get\", obj);" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list2.front() == "getVelocity")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IMovable:velocity.get\", obj);" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list2.front() == "setPosition")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IMovable:position.set\", obj," << std::endl;
                                    f << "  newValue).Execute();" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list2.front() == "setVelocity")
                                {
                                    f << "  return 0;" << std::endl;
                                }
                            f << "}" << std::endl;
                            list1.erase(list1.begin());
                            list2.erase(list2.begin());
                            list11.erase(list11.begin());
                            list12.erase(list12.begin());
                            list13.erase(list13.begin());
                            list14.erase(list14.begin());
                        }
                    }
                    f.close();
                }
                else if(current_file == "irotateble.h")
                {
                    std::string str;
                    while(readFile >> str)
                    {
                        if(str == "virtual")
                        {
                            readFile >> str;
                            list3.push_back(str);
                            readFile >> str;
                            list4.push_back(str);
                            readFile >> str;
                            readFile >> str;
                            list41.push_back(str);
                            readFile >> str;
                            list42.push_back(str);
                            readFile >> str;
                            list43.push_back(str);
                            readFile >> str;
                            list44.push_back(str);
                        }
                    }
                    std::string fileWriteName =
                            p.path().parent_path().generic_string() + "/" +
                            p.path().filename().replace_extension(".cpp").generic_string();
                    std::cout << fileWriteName << std::endl;
                    listFileName.push_back(fileWriteName);
                    std::ofstream f;
                    f.open(fileWriteName, ios::out);
                    {
                        f << "#include \"object.h\"" << std::endl;
                        f << "class IRotateble" << std::endl;
                        int count = list3.size();
                        for(int i = 0; i < count; i++)
                        {
                            f << list3.front()  << " " << list4.front() << "("
                              << list41.front() << " " << list42.front();
                            if(i % 2 == 0)
                                f << " " << list43.front()  << " " << list44.front();
                            f << ")" << std::endl;
                            f << "{" << std::endl;
                                if(list4.front() == "getAngular")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IRotateble:angular.get\", obj);" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list4.front() == "getAngularVelocity")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IRotateble:angular_velocity.get\", obj);" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list4.front() == "setAngularVelocity")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IRotateble:angular_velocity.set\", obj," << std::endl;
                                    f << "  newValue).Execute();" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                                else if(list4.front() == "setAngular")
                                {
                                    f << "  IoC.Resolve(\"Spaceship.Operations.IRotateble:angular.set\", obj," << std::endl;
                                    f << "  newValue).Execute();" << std::endl;
                                    f << "  return 0;" << std::endl;
                                }
                            f << "}" << std::endl;
                            list3.erase(list3.begin());
                            list4.erase(list4.begin());
                            list41.erase(list41.begin());
                            list42.erase(list42.begin());
                            list43.erase(list43.begin());
                            list44.erase(list44.begin());
                        }
                    }
                    f.close();
                }
                else
                {
                    std::cout << current_file << " - file not using" << std::endl;
                }
            }
            readFile.close();
          }
        }
      int count = listFileName.size();
      for(int i = 0; i < count; i++)
      {
        std::filesystem::remove(listFileName.front());
        listFileName.erase(listFileName.begin());
      }
    return 0;
}
