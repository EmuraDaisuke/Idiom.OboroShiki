#pragma once



#include <memory>



class Pimpl final {
    public:
        ~Pimpl() noexcept;
        
        Pimpl();
        
        void Call() const;
    
    private:
        std::unique_ptr<class PimplImpl> mpImpl;
};
