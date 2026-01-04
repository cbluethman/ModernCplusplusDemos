// ModernCplusplusDemos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

// Base class
class Shape
{
protected:
    int length = 0, width = 0;

public:
    Shape() = default;
    Shape(Shape const& o) = default;
    Shape& operator=(Shape const& o) = default;
    virtual ~Shape() = default;

    static int test;

    explicit Shape(int l, int w)
        : length(l), width(w)
    {
    }

    Shape(Shape&& o) noexcept
        : length(o.length), width(o.width)
    {
        std::cout << "move shape ctor" << std::endl;
    }

    Shape& operator=(Shape&& o) noexcept
    {
        std::cout << "move shape assign" << std::endl;

        if (this != &o)
        {
            length = o.length;
            width = o.width;
        }

        return (*this);
    }

    virtual int get_Area()
    {
        std::cout << "This is call to parent class area" << std::endl;
        return 1;
    }
};

// Derived class
class Square final : public Shape
{
public:
    Square(int l = 0, int w = 0)
        : Shape(l, w)
    {
    }

    int get_Area() override
    {
        std::cout << "Square area: " << length * width << std::endl;
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
    }

    int get_Area() override
    {
        std::cout << "Rectangle area: " << length * width << std::endl;
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
    virtual ~Chris() = default;

private:
    int _a = 0;

    explicit Chris(int a) : _a(a) {}
};

std::mutex mtx;

auto f()
{
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);

    lck.lock();
    std::cout << "abc" << std::endl;
    lck.unlock();

    return std::make_tuple(45, "abxc", '9');
}

void print()
{
    std::cout << "blah" << std::endl;
}

template <typename First, typename... Rest>
void print(First const& first, Rest const&... args)
{
    std::cout << first << std::endl;
    print(args...);
}

void print2(auto const& c)
{
    std::cout << c << std::endl;
}

template<typename T>
void print3(T c)
{
    std::cout << c << std::endl;

    std::cout.operator<<(c);
    std::cout.operator<<(std::endl);
}

// Demonstrates that references modify the original value
void rstuff(int& r, int& s)
{
    r = s;
}

// Demonstrates that pointer parameters are local copies - this assignment has no effect
// To modify the caller's pointer, use: void pstuff(int*& pr, int* ps)
void pstuff(int* pr, int* ps)
{
    pr = ps;  // Only modifies local copy
}

// Demonstration of a coroutine-like generator using Duff's device pattern.
// WARNING: This function is NOT thread-safe due to static variables.
// For production code, use C++20 coroutines with co_yield instead.
int64_t range(int a, int b)
{
    static long long int i;
    static int state = 0;

    switch (state)
    {
    case 0:  // start of function
        state = 1;

        for (i = a; i < b; i++)
        {
            return i;

    case 1:  // resume control straight after the return
            ;
        }
    }

    state = 0;

    return 0;
}

int Shape::test = 4;

int main()
{
    int m = 7;
    int n = 0;
    int x = 0;
    auto& z = x;
    (void)z;  // Suppress unused variable warning

    std::thread th1(f);
    std::thread th2(f);

    th1.join();
    th2.join();

    auto xx = f();

    std::cout << "addr " << &f << std::endl;

    std::cout << "type: " << typeid(f).name() << std::endl;

    std::cout << std::get<1>(xx) << std::endl;

    // Lambda demonstrating mutable and capture by reference
    [&](int a) mutable { m = ++n + a; }(4);

    std::cout << n << std::endl;

    auto lambda = [&, n](int a) mutable { std::cout << "aaa" << std::endl; };

    std::cout << "type: " << typeid(lambda).name() << std::endl;

    std::cout << m << std::endl << n << std::endl;
    lambda(4);

    std::string a = "9axQ43dr,-;34";
    std::regex re(R"([^A-Za-z])");
    std::string b = std::regex_replace(a, re, "");

    std::cout << b << std::endl;

    auto p = std::make_unique<char[]>(6);

    p[0] = 'C';
    p[1] = 'h';
    p[2] = 'r';
    p[3] = 'i';
    p[4] = 's';
    p[5] = '\0';

    std::cout << p.get() << std::endl;

    auto zz = []() { return 1024; };

    auto zzz = zz();

    std::cout << zzz << std::endl;

    int k = 1'000'000;

    std::cout << k << std::endl;

    Shape* s = nullptr;
    Square sq(5, 5);

    Rectangle rec(4, 5);

    Square sq2 = std::move(sq);
    sq2 = Square(5, 5);

    Square::test = 9;

    s = &sq;
    s->get_Area();
    s = &rec;
    s->get_Area();

    print(1, "lol", 1.1);
    print2("chris1");
    print3("chris3");

    std::vector<int> v1{ 1, 2, 3 };
    std::vector<int> v2;

    v2 = std::move(v1);

    std::cout << v1.size() << std::endl;

    for (auto const& v : v2)
    {
        std::cout << v << std::endl;
    }

    int&& g = 7 + 3;

    std::cout << g << std::endl;

    int r3 = 3, s3 = 4;
    int* pr3 = nullptr;
    int* ps3 = nullptr;

    pr3 = &r3;
    ps3 = &s3;

    // rstuff(r3, s3);
    pstuff(pr3, ps3);

    auto p2 = std::make_unique<char[]>(1024);

    // Safe way to write an int at offset 4 (avoids strict aliasing violation)
    int value = 1;
    std::memcpy(p2.get() + 4, &value, sizeof(int));

    // Demonstrating different const/pointer combinations
    int* p3 = nullptr;             // p3 is a mutable pointer to a mutable int
    int const* p4 = nullptr;       // p4 is a mutable pointer to a constant int
    int* const p5 = nullptr;       // p5 is a constant pointer to a mutable int
    int const* const p6 = nullptr; // p6 is a constant pointer to a constant int
    (void)p4; (void)p5; (void)p6;  // Suppress unused variable warnings

    std::cout << p3 << std::endl;
    std::cout << sizeof(p3) << std::endl;

    int q = 4;
    int* p7 = nullptr;
    int** p8 = nullptr;
    int*& r1 = p7;

    p7 = &q;
    p8 = &p7;

    std::cout << **p8 << std::endl;
    std::cout << *r1 << std::endl;
    std::cout << r1 << std::endl;
    std::cout << p7 << std::endl;
    std::cout << &r1 << std::endl;
    std::cout << &p7 << std::endl;

    std::vector<int> coolvec{ 1, 9, 3, 4, 5, 6, 7, 8, 2, 10 };

    auto isOdd = [](int i) { return (i % 2) == 1; };
    auto sortMe = [](int lhs, int rhs) { return lhs < rhs; };

    auto count = std::count_if(coolvec.begin(), coolvec.end(), isOdd);
    std::sort(coolvec.begin(), coolvec.end(), sortMe);

    std::cout << count << std::endl;

    for (auto const& v : coolvec)
    {
        std::cout << v << std::endl;
    }

    std::copy(coolvec.begin(), coolvec.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;

    int64_t i4 = 0;

    for (; (i4 = range(1, 5)) != 0;)
    {
        std::cout << "control at main: " << i4 << std::endl;
    }

    auto up = std::make_unique<int>(43);

    std::cout << *up << std::endl;

    int test{};

    std::cout << test << std::endl;

    return 0;
}
