#include <iostream>
#include <memory>
#include <cassert>
#include <optional>


//class Foo{
//public:
//    Foo(){
//        std::cout << "Foo:Foo()\n";
//    }
//
//    Foo(int, double){
//        std::cout << "Foo:Foo(int, double)\n";
//    }
//
//    void bar(){
//        std::cout << "Foo::bar()\n";
//    }
//
//
//
//    ~Foo(){
//        std::cout << "Foo:~Foo()\n";
//    }
//};
//
//void ptr_usage(std::shared_ptr<Foo> ptr){
//    ptr->bar();
//}
//struct B;
//
//struct A {
//    std::shared_ptr<B> a;
//
//    void foo() {
//        a->do_job();
//    }
//
//    void do_job() {std::cout << "some A stuff\n";}
//};
//
//struct B {
//    std::shared_ptr<A> b;
//};

struct zero_division {};

std::optional<double> div(double a, double b)
{
    if (b == 0.0)
        //std::cerr << "Zero div" <<std::endl;
        //return {};
        throw zero_division();
    return a/b;
}

void div_print(double a, double b)
{
    try{
        std::cout << div(a, b).value() << std::endl;
    }
    catch(zero_division const& e){
        std::cout << "Exception!\n";
    }
}

int main()
{
//    std::unique_ptr<Foo> smart_f(new Foo());
//    std::unique_ptr<Foo> smart_fid =
//                    std::make_shared<Foo>(1, 2.0);
//    ptr_usage(smart_f);


    assert(div(2.0, 1.0) == 2.0);
    assert(div(10.0, 2.0)== 5.0);
    std::cout << div(2.0, 1.0).value() << std::endl;
    return 0;
}
