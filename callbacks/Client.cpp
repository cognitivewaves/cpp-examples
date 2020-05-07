#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "Library.h"
#include <iostream>
#include <functional>

int g_total = 0;
int g_factor = 0;

// =============================================================================
//                          Client callbacks
// =============================================================================

// -----------------------------------------------------------------------------
// Define callback function pointer
void foo1(int val)
{
    g_total = g_total + g_factor * val;
    printf("foo1(factor, val): \t\t\tg_var=%d\tfactor=%d  val=%d\n", g_total, g_factor, val);
}

// -----------------------------------------------------------------------------
// Define static member function callback
class SFoo
{
public:
    SFoo() {}

    static void sbar(int val)
    {
        msTotal += msFactor * val;
        printf("SFoo::sbar(val): \t\t\tmsTotal=%d\tfactor=%d  val=%d\n", msTotal, msFactor, val);
    }

public:
    static int  msTotal;
    static int  msFactor;
};
int SFoo::msTotal = 0;
int SFoo::msFactor = 0;

// -----------------------------------------------------------------------------
// Define callback function object
class Foo
{
public:
    Foo(int& total, int factor) : mrTotal(total), mFactor(factor) {}

    void bar(int val)
    {
        mrTotal = mrTotal + mFactor * val;
        printf("Foo::bar(val): \t\t\t\ttotal=%d\tfactor=%d  val=%d\n", mrTotal, mFactor, val);
    }

    void operator()(int val)
    {
        mrTotal = mrTotal + mFactor * val;
        printf("Foo::operator()(val): \t\t\ttotal=%d\tfactor=%d  val=%d\n", mrTotal, mFactor, val);
    }

private:
    int& mrTotal;
    int  mFactor;
};

// -----------------------------------------------------------------------------
// Implement callback function interface
class FooImpl : public IFoo
{
public:
    FooImpl(int& total, int factor) : mrTotal(total), mFactor(factor) {}

    virtual void bar(int val) override
    {
        mrTotal = mrTotal + mFactor * val;
        printf("FooImpl::bar(val): \t\t\ttotal=%d\tfactor=%d  val=%d\n", mrTotal, mFactor, val);
    }

private:
    int& mrTotal;
    int  mFactor;
};

// =============================================================================
//                          Client
// =============================================================================

void main()
{
    int total = 0;
    int factor = 5;

    std::cout << "\t\t\t\t\ttotal=" << total << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    // Library call that invokes function pointer callback
    g_total = total;
    g_factor = factor;
    libFunctionPointer(foo1);
    total = g_total;

    // Libaray call that invokes class static member function callback
    SFoo::msTotal = total;
    SFoo::msFactor = factor;
    libFunctionClasStaticMethod(SFoo::sbar);
    total = SFoo::msTotal;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    // Library call that invokes function object callback
    Foo foo(total, factor);    
    libFunctionObject<Foo>(foo);
    libFunctionObjectMethod<Foo>(&Foo::bar, &foo);
    std::cout << "------------------------------------------------------------------------" << std::endl;

    // Library call that invokes lambda function callback
    libFunctionLambda(
        // Define callback anonymous lambda function
        [&total, factor](int val) -> void
        {
            total = total + factor * val;
            printf("anonymous(val): \t\t\ttotal=%d\tfactor=%d  val=%d\n", total, factor, val);
        }
    );
    std::cout << "------------------------------------------------------------------------" << std::endl;

    // Library call the invokes interface callback
    FooImpl fooImpl(total, factor);
    libFunctionInterface(fooImpl);
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

#endif