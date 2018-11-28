


#include "./Phantasma.h"



struct PhantasmaImpl {
	~PhantasmaImpl() noexcept;
	
	PhantasmaImpl();
	
	void Call() const;
};

PhantasmaImpl* Cast(const Phantasma* p)	{ return reinterpret_cast<PhantasmaImpl*>(const_cast<Phantasma*>(p)); }
Phantasma* Cast(const PhantasmaImpl* p)	{ return reinterpret_cast<Phantasma*>(const_cast<PhantasmaImpl*>(p)); }



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

Phantasma::~Phantasma() noexcept					{ Cast(this)->~PhantasmaImpl(); }

std::unique_ptr<Phantasma> Phantasma::MakeUnique()	{ return std::unique_ptr<Phantasma>(Cast(new PhantasmaImpl())); }

std::size_t Phantasma::local_size()					{ return sizeof(PhantasmaImpl); }
void Phantasma::local_init()						{ new(this) PhantasmaImpl(); }

void Phantasma::Call() const						{ return Cast(this)->Call(); }
