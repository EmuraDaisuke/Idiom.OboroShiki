#pragma	once



#include <memory>
#include "./NonInstanceable.h"
#include "./NonCopyable.h"



class Phantasma final : private NonInstanceable, private NonCopyable<Phantasma> {
	public:
		~Phantasma() noexcept;
		
		static std::unique_ptr<Phantasma> MakeUnique();
		
		static std::size_t local_size();
		void local_init();
		
		void Call() const;
};
