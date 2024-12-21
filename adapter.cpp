#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

using namespace std;
namespace fs = filesystem;

int main()
{
    fs::path current_path = fs::current_path();
    fs::path file_path(current_path;

    cout << file_path.parent_path() << endl;
    return 0;
}
