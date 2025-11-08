//
//
// COMSC 210 || Mehraj Hasan Nafi
// IDE Used : Visual Studio Code
//
//
#include <iostream>
#include <string>
#include <map>
#include <array>
#include <list>
#include <iomanip>
using namespace std;

// ---- stages ----
enum Stage { WAITING = 0, ONBUS = 1, LEFT = 2 };
using Buckets = array<list<string>, 3>;
using Env = map<string, Buckets>;


