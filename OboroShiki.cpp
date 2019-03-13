


#include "./Cast.h"
#include "./OboroShiki.h"



struct OboroShikiImpl {
    ~OboroShikiImpl() noexcept;
    
    OboroShikiImpl();
    
    void Call() const;
};

OboroShikiImpl* Cast(const OboroShiki* p) { return to_ptr<OboroShikiImpl>(p); }
OboroShiki* Cast(const OboroShikiImpl* p) { return to_ptr<OboroShiki>(p); }



// 

OboroShikiImpl::~OboroShikiImpl() noexcept
{
}



OboroShikiImpl::OboroShikiImpl()
{
}



void OboroShikiImpl::Call() const
{
}



// 

OboroShiki::~OboroShiki() noexcept                   { Cast(this)->~OboroShikiImpl(); }

std::unique_ptr<OboroShiki> OboroShiki::MakeUnique() { return std::unique_ptr<OboroShiki>(Cast(new OboroShikiImpl())); }

void OboroShiki::Call() const                        { return Cast(this)->Call(); }

// local_ptr
std::size_t OboroShiki::local_size()                 { return sizeof(OboroShikiImpl); }
void OboroShiki::local_init()                        { new(this) OboroShikiImpl(); }
