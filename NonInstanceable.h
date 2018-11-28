#pragma	once



class NonInstanceable {
	protected:
		~NonInstanceable() noexcept									= default;
		template <class... Args> NonInstanceable(const Args&...)	= delete;
		template <class... Args> NonInstanceable(Args&&...)			= delete;
};
