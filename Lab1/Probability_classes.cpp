#include <iostream>
#include <set>
#include <random>
#include <vector>

class SegmentState {
private:
    int const beg, end;
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int state): beg{state}, end{state} { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class MultiState {
private:
    std::vector<SegmentState> states;

public:
    MultiState() {}
    MultiState(int state){
        states.push_back(SegmentState(state));
    }
    MultiState(int beg, int end){
        states.push_back(SegmentState(beg, end));
    }
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

class Union {
private:
    MultiState state1, state2;
public:
    Union(MultiState s1, MultiState s2): state1{s1}, state2{s2} { }

    bool contains(int s) const {
        return state1.contains(s) || state2.contains(s);
    }
};

class Intersection {
private:
    MultiState state1, state2;
public:
    Intersection(MultiState s1, MultiState s2): state1{s1}, state2{s2} { }

    bool contains(int s) const{
        return state1.contains(s) && state2.contains(s);
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(MultiState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator()(Union const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator()(Intersection const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main(int argc, const char * argv[]) {
    MultiState d(1);
    MultiState s(0,10);
    MultiState ss({{1, 3}, {5, 7}, {23, 23}, {48, 57}, {60, 60}, {90, 99}});
    Union ds(d, s);
    Intersection sss(s, ss);
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(ds) << std::endl;
    std::cout << pt(sss) << std::endl;
    return 0;
}

