#include "function.h"
set<State> SwapSort::extend(State s)
{
    set<State> SS;
    State t1 = s;
    State t2 = s;

    int tmp;
    tmp = t1[0];
    t1[0] = t1[1];
    t1[1] = tmp;
    tmp = t2[0];
    t2[0] = t2[t2.size()-1];
    t2[t2.size()-1] = tmp;
    SS.insert(t1);
    SS.insert(t2);
    return SS;
}

void SwapSort::solve(int steps)
{
    while (steps>0) {
        set<list<State>> oldPaths;
        set<list<State>> newPaths;

        for (auto p : _paths) {
            _explored.insert(p.back());
            auto SS = extend(p.back());
            for (auto s : SS) {
                auto search = _explored.find(s);
                if (search == _explored.end()) {
                    auto np = p;
                    np.push_back(s);
                    if (is_sorted(s.begin(), s.end())) {
                        _solutions.insert(np);
                    } else {
                        newPaths.insert(np);
                    }
                }
            }
            oldPaths.insert(p);
        }
        for (auto p : oldPaths) {
            _paths.erase(p);
        }
        for (auto p : newPaths) {
            _paths.insert(p);
        }
        --steps;
    }
}
