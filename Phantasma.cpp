


#include "./Cast.h"
#include "./Phantasma.h"



struct PhantasmaImpl {
    ~PhantasmaImpl() noexcept;
    
    PhantasmaImpl();
    
    void Call() const;
};

PhantasmaImpl* Cast(const Phantasma* p) { return to_ptr<PhantasmaImpl>(p); }
Phantasma* Cast(const PhantasmaImpl* p) { return to_ptr<Phantasma>(p); }



// 

PhantasmaImpl::~PhantasmaImpl() noexcept
{
}



PhantasmaImpl::PhantasmaImpl()
{
}



void PhantasmaImpl::Call() const
{
}



// 

Phantasma::~Phantasma() noexcept                    { Cast(this)->~PhantasmaImpl(); }

std::unique_ptr<Phantasma> Phantasma::MakeUnique()  { return std::unique_ptr<Phantasma>(Cast(new PhantasmaImpl())); }

void Phantasma::Call() const                        { return Cast(this)->Call(); }

// local_ptr
std::size_t Phantasma::local_size()                 { return sizeof(PhantasmaImpl); }
void Phantasma::local_init()                        { new(this) PhantasmaImpl(); }
