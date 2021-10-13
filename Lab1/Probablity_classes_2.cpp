#include <iostream>
#include <set>
#include <random>
#include <vector>
#include <fstream>
#include <set>
#include <string>

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

    bool contains(int s) const override{
        return s == state;
    }
};

class SegmentState: public State{
private:
    int const beg, end;
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};

class MultiState: public State {
private:
    std::vector<State*> states;
public:
    MultiState(std::vector<State*> states): states{states}{
        //for(auto &s: points){
        //    states.push_back(SegmentState(s[0], s[1]));
        //}
    }

    bool contains(int s) const override{
        for(auto const &st: states){
            if(st->contains(s))
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

    bool contains(int s) const override{
        return state1->contains(s) || state2->contains(s);
    }
};

class Intersection: public State {
private:
    State const* state1;
    State const* state2;
public:
    Intersection(State const * s1, State const * s2): state1{s1}, state2{s2} { }

    bool contains(int s) const override{
        return state1->contains(s) && state2->contains(s);
    }
};

class StateFactory{
private:
    std::vector<State*> states_set;

public:
    State* create_discrete_state(int state){
        State* ptr = new DiscreteState(state);
        states_set.push_back(ptr);
        return ptr;
    }

    State* create_segment_state(int beg, int end){
        State* ptr = new SegmentState(beg, end);
        states_set.push_back(ptr);
        return ptr;
    }

    State* create_multi_state(std::vector<State*> states){
        State* ptr = new MultiState(states);
        states_set.push_back(ptr);
        return ptr;
    }

    State* create_union(State* s1, State* s2){
        State* ptr = new Union(s1, s2);
        states_set.push_back(ptr);
        return ptr;
    }

    State* create_intersection(State* s1, State* s2){
        State* ptr = new Intersection(s1, s2);
        states_set.push_back(ptr);
        return ptr;
    }

    void release(){
        for(auto ptr: states_set){
            delete ptr;
        }
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

class Test {
public:
    static void test(bool test_val, bool correct_val, std::string message = "  ")
    {
        if (test_val == correct_val)
            std::cout << "OK" << '\n';
        else
            std::cout << "Error " << message << '\n';
    }
};

void test()
{
    StateFactory SF;
    Test::test(SF.create_discrete_state(1)->contains(0), false, "0 is not in {1}");
    Test::test(SF.create_discrete_state(2)->contains(2), true, "2 is in {2}");
    Test::test(SF.create_discrete_state(0)->contains(0), true, "0 is in {0}");
    Test::test(SF.create_segment_state(1,15)->contains(54), false, "54 is not in [1, 15]");
    Test::test(SF.create_segment_state(23,870)->contains(33), true, "33 is in [23, 870]");
    Test::test(SF.create_segment_state(23,-10)->contains(33), false, "33 is not in [empty]");
    State* MS1 = SF.create_multi_state({SF.create_segment_state(28, 43),
                                       SF.create_discrete_state(50),
                                       SF.create_segment_state(48, 99)});
    Test::test(MS1->contains(50), true, "50 is in MS1");
    State* MS2 = SF.create_multi_state({SF.create_discrete_state(-10),
                                       SF.create_segment_state(-5, -13),
                                       SF.create_segment_state(-50, 78),
                                       SF.create_segment_state(12, 64)});
    Test::test(MS2->contains(34), true, "34 is in MS2");
    State* uni1 = SF.create_union(SF.create_discrete_state(62),
                                 SF.create_segment_state(1, 12));
    Test::test(uni1->contains(41), false, "41 is not in uni1");
    State* uni2 = SF.create_union(SF.create_segment_state(-10, 37),
                                 MS1);
    Test::test(uni2->contains(30), true, "30 is in uni2");
    State* intersection1 = SF.create_intersection(SF.create_segment_state(31, 76),
                                 SF.create_segment_state(65, 88));
    Test::test(intersection1->contains(69), true, "69 is in intersection1");
    State* intersection2 = SF.create_intersection(MS1, MS2);
    Test::test(intersection2->contains(41), true, "69 is in intersection1");
    Test::test(SF.create_multi_state({MS2, uni1, intersection2})->contains(100), false, "100 is not in it" );

    SF.release();
}

int main(int argc, const char * argv[]) {


    test();

    int beg = 0, end = 10;
    std::vector<State*> states;
    StateFactory SF;
    states.push_back(SF.create_discrete_state(1));
    states.push_back(SF.create_segment_state(beg, end));
    states.push_back(SF.create_multi_state({SF.create_segment_state(1, 3),
                                            SF.create_segment_state(5, 7),
                                            SF.create_discrete_state(23),
                                            SF.create_segment_state(48, 57),
                                            SF.create_discrete_state(60),
                                            SF.create_segment_state(90, 99)}));
    //states.push_back(SF.create_union(states[0], states[1]));
    //states.push_back(SF.create_intersection(states[2], states[1]));
    int size1 = 1;
    int size2 = end - beg + 1;
    int size3 = 3+3+1+10+1+10;

    int n = 3;
    int test_min, test_max;
    test_min = 0;
    test_max = 100;
    int N = 500000;

    ProbabilityTest pt(10, test_min, test_max, N);

    std::vector<double> P;
    P.push_back(static_cast<double> (size1)/(test_max - test_min + 1));
    P.push_back(static_cast<double> (size2)/(test_max - test_min + 1));
    P.push_back(static_cast<double> (size3)/(test_max - test_min + 1));

    std::cout << "Approximate prob: " << pt(states[0]) << " vs Exact prob: " << P[0] << '\n';
    std::cout << "Approximate prob: " << pt(states[1]) << " vs Exact prob: " << P[1] << '\n';
    std::cout << "Approximate prob: " << pt(states[2]) << " vs Exact prob: " << P[2] << '\n';


    int step = 1000;

    if ( 0 ){
    std::ofstream out("Data.txt");
    if (out.is_open()){
        for(auto j = 0; j < N/step+1; ++j){
            ProbabilityTest pt(10, test_min, test_max, j*step + 1);
            std::cout << j*step + 1 << " iterations" << '\n';
            out << j*step + 1 << ":";
            for(auto i=0; i<states.size(); ++i){
                //out <<"Class" << i+1 <<": " << pt(states[i]) << "; ";
                out << P[i] - pt(states[i]) << ":";
            }
            out << '\n';
        }
    }
    out.close();
    }

    SF.release();

    return 0;
}


