// ModernCplusplusDemos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <memory>
#include <tuple>
#include <utility>
#include <mutex>

using namespace std;

// Base class
class Shape
{
protected:
    int length = 0, width = 0;

public:
    Shape() = default;
    Shape(Shape const& o) = default;
    Shape& operator=(Shape const& o) = default;
    //    Shape(Shape&& o) = default;
    //    Shape& operator=(Shape&& o) = default;
    virtual ~Shape() {}

    static int test;

    explicit Shape(int l, int w)
    {
        length = l;
        width = w;
    }
    Shape(Shape&& o) noexcept
    {
        cout << "move shape ctor" << endl;

        length = move(o.length);
        width = move(o.width);
    }
    Shape& operator=(Shape&& o) noexcept
    {
        cout << "move shape assign" << endl;

        if (this != &o)
        {
            length = move(o.length);
            width = move(o.width);
        }

        return (*this);
    }

    virtual auto get_Area() -> int
    {
        cout << "This is call to parent class area" << endl;
        return 1;
    }
} circle;

// Derived class
class Square final : public Shape
{
public:
    Square(int l = 0, int w = 0)
        : Shape(l, w)
    {
    } // declaring and initializing derived class
    // constructor
    auto get_Area() -> int override
    {
        cout << "Square area: " << length * width << endl;
        return (length * width);
    }
};

// Derived class
class Rectangle final : public Shape
{
public:
    Rectangle(int l = 0, int w = 0)
        : Shape(l, w)
    {
    } // declaring and initializing derived class
    // constructor
    auto get_Area() -> int override
    {
        cout << "Rectangle area: " << length * width
            << endl;
        return (length * width);
    }
};

class Chris
{
public:
    Chris() = default;
    Chris(Chris const& o) = default;
    Chris& operator=(Chris const& o) = default;
    Chris(Chris&& o) = default;
    Chris& operator=(Chris&& o) = default;
    virtual ~Chris() {}

private:
    int _a = 0;

    Chris(int a) : _a(a)
    {
        _a = a;
    }

};

std::mutex mtx;

auto f(void) -> auto
{
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);

    lck.lock();
    cout << "abc" << endl;
    lck.unlock();

    return (make_tuple(45, "abxc", '9'));
}

void print()
{
    cout << "blah" << endl;
}

template <typename First, typename... Rest>
void print(First const& first, Rest &&... args)
{
    std::cout << first << std::endl;
    print(args...);
}

void print2(auto const& c)
{
    cout << c << endl;
}

template<typename T>
void print3(T c)
{
    cout << c << endl;

    cout.operator<<(c);
    cout.operator<<(endl);
}

void rstuff(int& r, int& s)
{
    r = s;
}

void pstuff(int* pr, int* ps)
{
    pr = ps;
}

int64_t range(int a, int b)
{
    static long long int i;
    static int state = 0;

    switch (state)
    {
    case 0: // start of function
        state = 1;

        for (i = a; i < b; i++)
        {
            return (i);

            // Returns control
    case 1:
        ; // resume control straight after the return
        }
    }

    state = 0;

    return (0);
}

int Shape::test = 4;

auto main() -> int
{
    int m = 7;
    int n = 0;
    int x = 0;
    auto& z = x;

    thread th1(f);
    thread th2(f);

    th1.join();
    th2.join();

    auto xx = f();

    cout << "addr " << &f << endl;

    cout << "type: " << typeid(f).name() << endl;

    cout << get<1>(xx) << endl;

    [&, nq = 0] (int a) mutable -> auto { m = ++n + a; return 256; }(4);

    cout << n << endl;

    auto f = [&, n](int a) mutable -> auto { cout << "aaa" << endl; };

    cout << "type: " << typeid(f).name() << endl;

    cout << m << endl << n << endl;
    f(4);

    string a = "9axQ43dr,-;34";
    regex re(R"([^A-Za-z])");
    string b = regex_replace(a, re, "");

    cout << b << endl;

    unique_ptr< char[] > p(new char[6]);

    p[0] = 'C';
    p[1] = 'h';
    p[2] = 'r';
    p[3] = 'i';
    p[4] = 's';
    p[5] = 0;

    cout << p << endl;

    auto zz = []() -> auto { return 1024; };

    auto zzz = zz();

    cout << zzz << endl;

    int k = 1'000'000;

    cout << k << endl;

    Shape* s;
    Square sq(5, 5); // making object of child class Square

    Rectangle rec(
        4, 5); // making object of child class Rectangle

    Square sq2 = move(sq);
    sq2 = Square(5, 5);

    Square::test = 9;

    s = &sq;
    s->get_Area();
    s = &rec;
    s->get_Area();

    print(1, "lol", 1.1);
    print2("chris1");
    print3("chris3");

    vector< int > v1{ 1, 2, 3 };
    vector< int > v2;

    v2 = move(v1);

    cout << v1.size() << endl;

    for (auto const& v : v2)
    {
        cout << v << endl;
    }

    int&& g = 7 + 3;

    cout << g << endl;

    int r3 = 3, s3 = 4;
    int* pr3;
    int* ps3;

    pr3 = &r3;
    ps3 = &s3;

    //rstuff(r3, s3);
    pstuff(pr3, ps3);

    char* p2 = new char[1024];

    *(int*)(p2 + 4) = 1;

    delete[] p2;

    int* p3 = nullptr;             // p3 is a mutable pointer to a mutable int
    int const* p4 = nullptr;       // p4 is a mutable pointer to a constant int
    int* const p5 = nullptr;       // p5 is a constant pointer to a mutable int
    int const* const p6 = nullptr; // p6 is a constant pointer to a constant int

    cout << p3 << endl;
    cout << sizeof(p3) << endl;

    int q = 4;
    int* p7;
    int** p8;
    int*& r1 = p7;

    p7 = &q;
    p8 = &p7;

    cout << **p8 << endl;
    cout << *r1 << endl;
    cout << r1 << endl;
    cout << p7 << endl;
    cout << &r1 << endl;
    cout << &p7 << endl;

    vector<int> coolvec{ 1, 9, 3, 4, 5, 6, 7, 8, 2, 10 };

    auto isOdd = [](int i) -> bool { return(i % 2) == 1; };
    auto sortMe = [](int a, int b) -> bool { return(a < b); };

    int64_t count = count_if(coolvec.begin(), coolvec.end(), isOdd);
    sort(coolvec.begin(), coolvec.end(), sortMe);

    cout << count << endl;

    for (auto const& v : coolvec)
    {
        cout << v << endl;
    }

    copy(coolvec.begin(), coolvec.end(), std::ostream_iterator<int>(std::cout, " "));

    cout << endl;

    int64_t i4;  // For really large numbers

    for (; i4 = range(1, 5);)
    {
        cout << "control at main :" << i4 << endl;
    }


    unique_ptr<int> up{ new int{ 43 } };

    cout << *up << endl;

    int test{ };

    cout << test << endl;

    //vector< unique_ptr<int>> uv;
}
