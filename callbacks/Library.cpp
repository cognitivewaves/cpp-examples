#include "Library.h"

// Invokes callback via legacy function

// -----------------------------------------------------------------------------
//void libFunctionPointer1(void(*cbFunction)(int v))   // Without typedef
//{
//    int val = 2;
//    std::cout << "libFunctionPointer(): cb with " << val << std::endl;
//
//    cbFunction(val);
//}

void libFunctionPointer(CallbackFunction cbFunction)          // With typedef
{
    int val = 2;
    std::cout << "libFunctionPointer(): cb with " << val << std::endl;

    cbFunction(val);
}

// -----------------------------------------------------------------------------
// Invokes callback via class static member function
void libFunctionClasStaticMethod(void(*cbSFunction)(int v))
{
    int val = 2;
    std::cout << "libFunctionStaticMethod(): cb with " << val << std::endl;

    cbSFunction(val);
}

// -----------------------------------------------------------------------------
// Invokes callback via lambda function
void libFunctionLambda(std::function<void(int v)> cbLambda)
{
    int val = 4;
    std::cout << "libFunctionLambda(): cb with " << val << std::endl;

    cbLambda(val);
}

// -----------------------------------------------------------------------------
// Invokes callback via pre-defined interface
void libFunctionInterface(IFoo& cbInterface)
{
    int val = 5;
    std::cout << "libFunctionInterface(): cb with " << val << std::endl;

    cbInterface.bar(val);
}
