#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

class RandomGenerator{
public:
    static std::vector<int> create_sequence(size_t n, int min, int max){
        std::mt19937_64 engine(time(0));
        //std::mt19937_64 engine(std::random_device{}());
        std::uniform_int_distribution<int> distr(min, max);
        std::vector<int> v(n);
        for(auto i=0u; i<n; ++i)
            v[i] = distr(engine);
        return v;
    }
};

class TimeMeasure{
public:
    void start(){
        auto start_time_ = std::chrono::system_clock::now();
    }
    void stop(){
        auto stop_time_ = std::chrono::system_clock::now();
    }
     double elapsed() const {
        auto elapsed_time = stop_time_ - start_time_;
        return std::chrono::duration_cast<std::chrono::duration<double>> (elapsed_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time_, stop_time_;
};

int max(int a, int b)
{
    if(a >= b)
        return a;
    else
        return b;
}

class DemoStr{
public:
    DemoStr(): data_{nullptr}, length_{0}, capacity_{length_}{
    }

    DemoStr(DemoStr const& other): length_{other.length_}, capacity_{length_}{
        allocate(other.length_);
        copy_from(other.data_, other.length_);
    }

    DemoStr(char const* raw_str, size_t length): length_{length}, capacity_{length_}{
        allocate(length);
        copy_from(raw_str, length);
        //reformat();
    }

    DemoStr(std::vector<int> arr): length_{arr.size()}, capacity_{arr.size()}{
        allocate(length_);
        copy_from(arr);
    }

    DemoStr(std::string str): length_{str.size()}, capacity_{str.size()}{
        allocate(length_);
        copy_from(str);
    }

    explicit DemoStr(int value) {
        length_ = get_value_length(value);
        capacity_ = length_;
        allocate(length_);
        auto it = &data_[length_- 1];
        while (value > 0){
            *it = value % 10 + '0';
            --it;
            value /= 10;
        }
    }

    size_t size() {
        return length_;
    }

    void print() const {
        print(std::cout);
    }

    void print(std::ostream& out) const {
        for (auto i = 0u; i < length_; ++i)
            out << data_[i];
        //out << "\n";
    }

    //index <= length_ - 1
    char at(size_t index) const {
        return data_[index];
    }

    bool equal(DemoStr const &other) const{
        if (other.length_ != length_)
            return false;
        for (auto i = 0u; i < length_; ++i)
            if (data_[i] != other.data_[i])
                return false;

        return true;
    }

    void read_from(std::istream &in){
        char tmp;
        while (in >> tmp) {
            if (length_ >= capacity_)
                reallocate((capacity_ == 0) ? 1 : capacity_ * 2);
            data_[length_] = tmp;
            ++length_;
        }
        reformat();
    }

    void shrink_to_fit() {
        reallocate(length_);
    }

    void clear() {
        //delete[] data_;
        //data_ = nullptr;
        length_ = capacity_ = 0;
    }

    ~DemoStr(){
        delete[] data_;
        data_ = nullptr;
        length_ = capacity_ = 0;
    }

protected:
    void reallocate(size_t n){
        auto old_data = data_;

        data_ = new char [n];
        capacity_ = n;

        copy_from(old_data, std::min(n, length_));

        delete [] old_data;
    }

    void reformat() {
        for (auto i = 0u; i < length_; ++i)
            data_[i] = (i % 2 == 1) ? std::tolower(data_[i]) :
                       std::toupper(data_[i]);
    }

    size_t get_value_length(int value){
        auto len = 0ull;
        while (value > 0){
            value /= 10;
            ++len;
        }
        return len;
    }

    void allocate(size_t n){
        data_ = new char[n];
    }

    void copy_from(char const* data, size_t n) {
        for (auto i = 0u; i < n; ++i)
            data_[i] = data[i];
    }

    void copy_from(std::vector<int> arr)
    {
        for (auto i = 0u; i < arr.size(); ++i)
            data_[i] = (char)(arr[i]);
    }

    void copy_from(std::string str)
    {
        for (auto i = 0u; i < str.size(); ++i)
            data_[i] = str[i];
    }

    //friend std::ostream& operator << (std::ostream& out, DemoStr const& v);

    char* data_ = nullptr;
    size_t length_ = 0, capacity_ = 0;
};

class String: public DemoStr{
public:
    /*String(): DemoStr(){}
    String(DemoStr const& other): DemoStr(other){}
    String(char const* raw_str, size_t length): DemoStr(raw_str, length){}
    explicit String(int value): DemoStr(value){}*/
    using DemoStr::DemoStr;

    void append(String &s) {
        if(capacity_ < s.size() + length_){
            capacity_ = max(length_+s.size(), capacity_*2);
            char* new_data_ = new char[capacity_];
            for(int i=0; i<length_; ++i){
                new_data_[i] = data_[i];
            }
            char* old_data_ = data_;
            data_ = new_data_;
            delete[] old_data_;
            old_data_ = nullptr;
        }
        for(int i=0; i<s.size(); ++i){
                data_[length_+i] = s.at(i);
            }
        length_ += s.size();
    }

    std::vector<String> split(char c) {
        std::vector<String> V;
        int tmp = 0;
        for(int i=0; i<length_; ++i){
            if(data_[i] == c){
                V.push_back(String (data_+tmp, i-tmp));
                tmp = i+1;
            }
        }
        V.push_back(String (data_+tmp, length_-tmp));
        return V;
    }
};

std::ostream& operator << (std::ostream& out, DemoStr const& v){
    v.print(out);
    /*for (auto i = 0ul; i < v.length_; ++i)
        out << v.data_[i];
    out << "\n";*/
    return out;
}

std::istream& operator >> (std::istream& in, DemoStr& v){
    v.clear();
    v.read_from(in);
    return in;
}


int main()
{
    TimeMeasure timer;
    int t1, t2, dt;

    std::vector<int> n;
    n = {1, 5, 10, 15, 20, 25, 30, 35, 40};
    int N = 500000;
    int a = 1000;

    String A("0");

    std::ofstream out("Data.txt");
    if (out.is_open()){
        out << "Время работы при " << N << " итераций" << '\n';
        for (int j=0; j<n.size(); ++j){
            auto random_vec = RandomGenerator::create_sequence(n[j]*a, -10, 10);
            String B(random_vec);
            timer.start();
            t1 = time(0);
            for(int i=0; i<N; ++i){
                A.append(B);
                A.clear();
            }
            t2 = time(0);
            timer.stop();
            dt = t2 - t1;
            t2 = t1 = 0;
            out << n[j]*a << ": " << dt << '\n';
        }
    }
    out.close();
    std::cout << "Execution finished";
    //std::cout <<"ETA: " << timer.elapsed() << '\n';
    //std::cout << "Time: " << t2-t1 << '\n';
    //std::cout << str1 << '\n';

    /*
    char s1[] = "Hello, class";
    String str1(s1, sizeof(s1) - 1);

    char s2[] = "Goodbye";
    String str2(s2, sizeof(s2) - 1);

    timer.start();
    t1 = time(0);
    int a;
    std::cin >> a;
    timer.stop();
    t2 = time(0);
    std::cout <<"ETA: " << timer.elapsed() << '\n';
    std::cout << "Time: " << t2-t1 << '\n';*/

    /*
    char s3[] = "he.ll.o wo.rl.d";
    String str3(s3, sizeof(s3) - 1);

    std::vector<String> v;
    v = str3.split('.');
    std::cout << v.size() << '\n';
    for(int i=0; i<v.size(); ++i){
        std::cout << v[i] << ' ';
    }
    */
    return 0;
}
