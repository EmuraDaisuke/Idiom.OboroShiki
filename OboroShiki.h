#pragma once



#include <memory>
#include "./NonInstanceable.h"
#include "./NonCopyable.h"



class OboroShiki final : private NonInstanceable, private NonCopyable<OboroShiki> {
    public:
        ~OboroShiki() noexcept;
        
        static std::unique_ptr<OboroShiki> MakeUnique();
        
        void Call() const;
        
        // local_ptr
        static std::size_t local_size();
        void local_init();
};
