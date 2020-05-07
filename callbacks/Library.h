#ifndef _LIBRARY_H_
#define _LIBRARY_H_

// ============================================================================
//                          Library
// ============================================================================

#include <functional>
#include <iostream>

// -----------------------------------------------------------------------------
// Invokes callback via legacy function

// Without typedef
//void libFunctionPointer(void(*cbFunction)(int val))

// With typedef
typedef void(*CallbackFunction)(int v);
void libFunctionPointer(CallbackFunction cbfn);

// -----------------------------------------------------------------------------
// Invokes callback via class static member function
void libFunctionClasStaticMethod(void(*cbSFunction)(int v));

// -----------------------------------------------------------------------------
// Invokes callback via function object
template <class T>
void libFunctionObject(T& fo)
{
    int val = 3;
    std::cout << "libFunctionObject(): cb with " << val << std::endl;

    fo.bar(val);
    fo(val);
}

// -----------------------------------------------------------------------------
// Invokes callback via function object method (member function)

// Without typdef using
//void libFunctionObjectMethod(void(T::*cbMethod)(int v), T* pFO);
//{
//    int val = 3;
//    std::cout << "libFunctionObjectMethod(): cb with " << val << std::endl;
//
//    (pFO->*cbMethod)(val);
//}

// With typedef using
template<class T>
using CallbackObjectMethod = void(T::*)(int v);

template <class T>
void libFunctionObjectMethod(CallbackObjectMethod<T> cbMethod, T* pFO)
{
    int val = 3;
    std::cout << "libFunctionObjectMethod(): cb with " << val << std::endl;

    (pFO->*cbMethod)(val);
}

// -----------------------------------------------------------------------------
// Invokes callback via lambda function
void libFunctionLambda(std::function<void(int v)> cbLambda);

// -----------------------------------------------------------------------------
// Define interface for callback
class IFoo
{
public:
    virtual void bar(int val) = 0;
};

// Invokes callback via pre-defined interface
void libFunctionInterface(IFoo& cbInterface);


#endif

