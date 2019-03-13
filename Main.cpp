


#if _OPENMP//[
#include <omp.h>
#endif//]

#include "./Lapse.h"
#include "./LocalPtr.h"
#include "./Pimpl.h"
#include "./OboroShiki.h"



// 

void testLifePimpl(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        Pimpl v;
    }
}



void testLifeOboroShikiUnique(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        auto p = OboroShiki::MakeUnique();
    }
}



void testLifeOboroShikiLocal(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        []{
            auto p = make_local(OboroShiki);
        }();
    }
}



void testLife(int nTest, int nRepeat)
{
    printf("\n\n== testLife\n");
    
    {   // 
        printf("\n== Pimpl\n");
        for (auto n = nRepeat; n; --n){
            testLifePimpl(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:unique_ptr\n");
        for (auto n = nRepeat; n; --n){
            testLifeOboroShikiUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:local_ptr\n");
        for (auto n = nRepeat; n; --n){
            testLifeOboroShikiLocal(nTest);
        }
    }
}



// 

void testOpmpPimpl(int nTest)
{
    #if _OPENMP//[
    Lapse l;
    #pragma omp parallel for
    for (auto n = nTest; n > 0; --n){
        Pimpl v;
    }
    #else//][
    printf("n/a\n");
    #endif//]
}



void testOpmpOboroShikiUnique(int nTest)
{
    #if _OPENMP//[
    Lapse l;
    #pragma omp parallel for
    for (auto n = nTest; n > 0; --n){
        auto p = OboroShiki::MakeUnique();
    }
    #else//][
    printf("n/a\n");
    #endif//]
}



void testOpmpOboroShikiLocal(int nTest)
{
    #if _OPENMP//[
    Lapse l;
    #pragma omp parallel for
    for (auto n = nTest; n > 0; --n){
        []{
            auto p = make_local(OboroShiki);
        }();
    }
    #else//][
    printf("n/a\n");
    #endif//]
}



void testOpmp(int nTest, int nRepeat)
{
    printf("\n\n== testOpmp\n");
    
    {   // 
        printf("\n== Pimpl\n");
        for (auto n = nRepeat; n; --n){
            testOpmpPimpl(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:unique_ptr\n");
        for (auto n = nRepeat; n; --n){
            testOpmpOboroShikiUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:local_ptr\n");
        for (auto n = nRepeat; n; --n){
            testOpmpOboroShikiLocal(nTest);
        }
    }
}



// 

void testCallPimpl(int nTest)
{
    Pimpl v;
    Lapse l;
    for (auto n = nTest; n; --n){
        v.Call();
    }
}



void testCallOboroShikiUnique(int nTest)
{
    auto p = OboroShiki::MakeUnique();
    Lapse l;
    for (auto n = nTest; n; --n){
        p->Call();
    }
}



void testCallOboroShikiLocal(int nTest)
{
    auto p = make_local(OboroShiki);
    Lapse l;
    for (auto n = nTest; n; --n){
        p->Call();
    }
}



void testCall(int nTest, int nRepeat)
{
    printf("\n\n== testCall\n");
    
    {   // 
        printf("\n== Pimpl\n");
        for (auto n = nRepeat; n; --n){
            testCallPimpl(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:unique_ptr\n");
        for (auto n = nRepeat; n; --n){
            testCallOboroShikiUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== OboroShiki:local_ptr\n");
        for (auto n = nRepeat; n; --n){
            testCallOboroShikiLocal(nTest);
        }
    }
}



// 

int main(int argc, char* argv[])
{
    testLife(100000000, 4);
    testOpmp(100000000, 4);
    testCall(100000000, 4);
    return 0;
}
