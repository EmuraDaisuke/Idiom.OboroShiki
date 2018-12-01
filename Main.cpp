


#include <random>

#include "./Lapse.h"
#include "./LocalPtr.h"
#include "./Pimpl.h"
#include "./Phantasma.h"



// 

void testLifePimpl(std::size_t nTest)
{
    Lapse l;
    for (int n = nTest; n; --n){
        Pimpl v;
    }
}



void testLifePhantasmaUnique(std::size_t nTest)
{
    Lapse l;
    for (int n = nTest; n; --n){
        auto p = Phantasma::MakeUnique();
    }
}



void testLifePhantasmaLocal(std::size_t nTest)
{
    Lapse l;
    for (int n = nTest; n; --n){
        []{
            auto p = make_local(Phantasma);
        }();
    }
}



void testLife(std::size_t nTest, int nRepeat)
{
    printf("\n\n== testLife\n");
    
    {   // 
        printf("\n== Pimpl\n");
        for (int n = nRepeat; n; --n){
            testLifePimpl(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:unique_ptr\n");
        for (int n = nRepeat; n; --n){
            testLifePhantasmaUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:local_ptr\n");
        for (int n = nRepeat; n; --n){
            testLifePhantasmaLocal(nTest);
        }
    }
}



// 

void testCallPimpl(std::size_t nTest)
{
    Pimpl v;
    Lapse l;
    for (int n = nTest; n; --n){
        v.Call();
    }
}



void testCallPhantasmaUnique(std::size_t nTest)
{
    auto p = Phantasma::MakeUnique();
    Lapse l;
    for (int n = nTest; n; --n){
        p->Call();
    }
}



void testCallPhantasmaLocal(std::size_t nTest)
{
    auto p = make_local(Phantasma);
    Lapse l;
    for (int n = nTest; n; --n){
        p->Call();
    }
}



void testCall(std::size_t nTest, int nRepeat)
{
    printf("\n\n== testCall\n");
    
    {   // 
        printf("\n== Pimpl\n");
        for (int n = nRepeat; n; --n){
            testCallPimpl(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:unique_ptr\n");
        for (int n = nRepeat; n; --n){
            testCallPhantasmaUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:local_ptr\n");
        for (int n = nRepeat; n; --n){
            testCallPhantasmaLocal(nTest);
        }
    }
}



// 

int main(int argc, char* argv[])
{
    testLife(1000000, 4);
    testCall(100000000, 4);
    return 0;
}
