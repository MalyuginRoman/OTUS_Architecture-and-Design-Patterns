#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = /*experimental::*/filesystem;

int main()
{
    fs::path current_path = fs::current_path();
    fs::path file_path(current_path;

    cout << file_path.parent_path() << endl;
    return 0;
}
