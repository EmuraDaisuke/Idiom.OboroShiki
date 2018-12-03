


#include "./Lapse.h"
#include "./LocalPtr.h"
#include "./Pimpl.h"
#include "./Phantasma.h"



// 

void testLifePimpl(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        Pimpl v;
    }
}



void testLifePhantasmaUnique(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        auto p = Phantasma::MakeUnique();
    }
}



void testLifePhantasmaLocal(int nTest)
{
    Lapse l;
    for (auto n = nTest; n; --n){
        []{
            auto p = make_local(Phantasma);
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
        printf("\n== Phantasma:unique_ptr\n");
        for (auto n = nRepeat; n; --n){
            testLifePhantasmaUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:local_ptr\n");
        for (auto n = nRepeat; n; --n){
            testLifePhantasmaLocal(nTest);
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



void testCallPhantasmaUnique(int nTest)
{
    auto p = Phantasma::MakeUnique();
    Lapse l;
    for (auto n = nTest; n; --n){
        p->Call();
    }
}



void testCallPhantasmaLocal(int nTest)
{
    auto p = make_local(Phantasma);
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
        printf("\n== Phantasma:unique_ptr\n");
        for (auto n = nRepeat; n; --n){
            testCallPhantasmaUnique(nTest);
        }
    }
    
    {   // 
        printf("\n== Phantasma:local_ptr\n");
        for (auto n = nRepeat; n; --n){
            testCallPhantasmaLocal(nTest);
        }
    }
}



// 

int main(int argc, char* argv[])
{
    testLife(100000000, 4);
    testCall(100000000, 4);
    return 0;
}
