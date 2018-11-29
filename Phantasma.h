#pragma	once



#include <memory>
#include "./NonInstanceable.h"
#include "./NonCopyable.h"



class Phantasma final : private NonInstanceable, private NonCopyable<Phantasma> {
	public:
		~Phantasma() noexcept;
		
		static std::unique_ptr<Phantasma> MakeUnique();
		
		void Call() const;
		
		// local_ptr
		static std::size_t local_size();
		void local_init();
};
