


#include "./Pimpl.h"



struct PimplImpl {
    ~PimplImpl() noexcept;
    
    PimplImpl();
    
    void Call() const;
};



// 

PimplImpl::~PimplImpl() noexcept
{
}



PimplImpl::PimplImpl()
{
}



void PimplImpl::Call() const
{
}



// 

Pimpl::~Pimpl() noexcept    {}

Pimpl::Pimpl()              :mpImpl(std::make_unique<PimplImpl>()){}

void Pimpl::Call() const    { return mpImpl->Call(); }
