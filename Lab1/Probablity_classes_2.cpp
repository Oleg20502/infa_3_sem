#include <iostream>
#include <set>
#include <random>
#include <vector>
#include <fstream>

class State{
public:
    virtual bool contains(int s) const = 0;

    virtual ~State() = default;
};

class DiscreteState: public State {
private:
    int const state;
public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState: public State{
private:
    int const beg, end;
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class MultiState: public State {
private:
    std::vector<SegmentState> states;
public:
    MultiState(std::vector<std::vector<int>> points){
        for(auto &s: points){
            states.push_back(SegmentState(s[0], s[1]));
        }
    }

    bool contains(int s) const {
        for(auto &st: states){
            if(st.contains(s))
                return true;
        }
        return false;
    }
};

class Union: public State {
private:
    State* state1;
    State* state2;
public:
    Union(State* s1, State* s2): state1{s1}, state2{s2} { }

    bool contains(int s) const {
        return state1->contains(s) || state2->contains(s);
    }
};

class Intersection: public State {
private:
    State* state1;
    State* state2;
public:
    Intersection(State* s1, State* s2): state1{s1}, state2{s2} { }

    bool contains(int s) const {
        return state1->contains(s) && state2->contains(s);
    }
};

class StateFactory{
public:
    static State* create_discrete_state(int state){
        return new DiscreteState(state);
    }

    static State* create_segment_state(int beg, int end){
        return new SegmentState(beg, end);
    }

    static State* create_multi_state(std::vector<std::vector<int>> points){
        return new MultiState(points);
    }

    static State* create_union(State* s1, State* s2){
        return new Union(s1, s2);
    }

    static State* create_intersection(State* s1, State* s2){
        return new Intersection(s1, s2);
    }

    static void release(State* ptr){
        delete ptr;
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(State* state) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (state->contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main(int argc, const char * argv[]) {

    int beg = 0, end = 10;
    std::vector<State*> states;
    states.push_back(StateFactory::create_discrete_state(1));
    states.push_back(StateFactory::create_segment_state(beg, end));
    states.push_back(StateFactory::create_multi_state({{1, 3}, {5, 7}, {23, 23}, {48, 57}, {60, 60}, {90, 99}}));
    //states.push_back(StateFactory::create_union(states[0], states[1]));
    //states.push_back(StateFactory::create_intersection(states[2], states[1]));
    int n = 3;
    int test_min, test_max;
    test_min = 0;
    test_max = 100;

    int N = 100;
    int step = 1000;
    /*
    std::ofstream out("Data.txt");
    if (out.is_open()){
        for(auto j = 0; j<N; ++j){
            ProbabilityTest pt(10, test_min, test_max, j*step + 1);
            //out << j*100 + 1 << " iterations: ";
            out << j*100 + 1 <<":";
            for(auto i=0; i<states.size(); ++i){
                //out <<"Class" << i+1 <<": " << pt(states[i]) << "; ";
                out << pt(states[i]) << ":";
            }
            out << '\n';
        }
    }
    out.close();
*/
    ProbabilityTest pt(10, test_min, test_max, N*step);
    int size1 = 1;
    int size2 = end - beg + 1;
    int size3 = 3+3+1+10+1+10;

    double P1 = static_cast<double> (size1)/(test_max - test_min + 1);
    double P2 = static_cast<double> (size2)/(test_max - test_min + 1);
    double P3 = static_cast<double> (size3)/(test_max - test_min + 1);

    std::cout << "Approximate prob: " << pt(states[0]) << " vs Exact prob: " << P1 << '\n';
    std::cout << "Approximate prob: " << pt(states[1]) << " vs Exact prob: " << P2 << '\n';
    std::cout << "Approximate prob: " << pt(states[2]) << " vs Exact prob: " << P3 << '\n';

    for (auto s : states)
        StateFactory::release(s);

    return 0;
}


