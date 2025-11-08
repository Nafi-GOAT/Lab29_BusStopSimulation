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
#include <fstream>
#include <sstream>
using namespace std;

void load_data(const string& filename, Env& env) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string stop, stage, id;

        getline(ss, stop, ',');
        getline(ss, stage, ',');
        getline(ss, id, ',');

        int index = stage_from_string(stage);
        if (index >= 0) {
            env[stop][index].push_back(id);
        }
    }

    file.close();
}

// ---- stages ----
enum Stage { WAITING = 0, ONBUS = 1, LEFT = 2 };
using Buckets = array<list<string>, 3>;
using Env = map<string, Buckets>;

int stage_from_string(const string& s) {
    if (s == "WAITING") return WAITING;
    if (s == "ONBUS")   return ONBUS;
    if (s == "LEFT")    return LEFT;
    return -1;
}

void print_env(const Env& env, int period = -1) {
    if (period < 0) cout << "\n=== Initial state ===\n";
    else            cout << "\n=== After period " << period << " ===\n";

    cout << left << setw(10) << "Stop"
         << right << setw(10) << "WAIT"
         << right << setw(10) << "ONBUS"
         << right << setw(10) << "LEFT" << "\n";
    cout << string(40, '-') << "\n";

    for (const auto& [stop, buckets] : env) {
        cout << left  << setw(10) << stop
             << right << setw(10) << buckets[WAITING].size()
             << right << setw(10) << buckets[ONBUS].size()
             << right << setw(10) << buckets[LEFT].size()
             << "\n";
    }
}

// One simulation step (simple mock rules):
// - Move 1 from WAITING → ONBUS (if any)
// - Move 1 from ONBUS   → LEFT  (if any)
// - Every 3 periods, a new WAITING passenger arrives at each stop
void simulate_step(Env& env, int t) {
    for (auto& [stop, buckets] : env) {
        if (!buckets[WAITING].empty()) {
            string id = buckets[WAITING].front();
            buckets[WAITING].pop_front();
            buckets[ONBUS].push_back(id);
        }
        if (!buckets[ONBUS].empty()) {
            string id = buckets[ONBUS].front();
            buckets[ONBUS].pop_front();
            buckets[LEFT].push_back(id);
        }
        if (t % 3 == 0) {
            buckets[WAITING].push_back("N" + to_string(t) + "_" + stop);
        }
    }
}

int main() {

    Env env;

    // MOCKUP data for Lab 29: one seed item to prove structure works
    env["Stop-A"][WAITING].push_back("P001");
    env["Stop-B"][ONBUS  ].push_back("P120");
    env["Stop-C"][LEFT   ].push_back("P300");

    print_env(env, -1);

    const int PERIODS = 25;
    for (int t = 1; t <= PERIODS; ++t) {
        simulate_step(env, t);
        // For Lab 29 we can print every 5 periods to keep output short
        if (t % 5 == 0) print_env(env, t);
    }

    cout << "\nSimulation complete.\n";
    return 0;
}






