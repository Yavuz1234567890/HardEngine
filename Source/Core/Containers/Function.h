#ifndef FUNCTION_H_
#define FUNCTION_H_

template <typename T> class Function;

template<typename R, typename... Args>
class Function<R(Args...)>
{
private:
	template <R(*Function)(Args...)> 
	static R FunctionStub(void*, Args... args)
	{
		return (Function)(args...);
	}

	template <typename C, R(C::*Function)(Args...)>
	static R ClassMethodStub(void* instance, Args... args)
	{
		return (static_cast<C*>(instance)->*Function)(args...);
	}

	template <typename C, R(C::*Function)(Args...) const>
	static R ClassMethodStub(void* instance, Args... args)
	{
		return (static_cast<C*>(instance)->*Function)(args...);
	}
public:
	Function()
		: m_Instance(nullptr),
		m_Handle(nullptr)
	{

	}

	Function(const Function& rhs)
		: m_Instance(rhs.m_Instance),
		m_Handle(rhs.m_Handle)
	{

	}

	template <typename T>
	Function(const T& value)
	{
		m_Instance = (void*)&value;
		m_Handle = [](void* instance, Args... args) -> R 
		{
			const T& function = *(const T*)instance;
			return function(args...);
		};
	}

	Function& operator=(const Function& rhs)
	{
		m_Instance = rhs.m_Instance;
		m_Handle = rhs.m_Handle;
		return *this;
	}

	R operator()(Args... args) const
	{
		return m_Handle(m_Instance, args...);
	}

	template<R(*Function)(Args...)>
	void Bind()
	{
		m_Instance = nullptr;
		m_Handle = &FunctionStub<Function>;
	}

	template<typename T, R(T::*Function)(Args...)>
	void Bind(T* instance)
	{
		m_Instance = instance;
		m_Handle = &ClassMethodStub<T, Function>;
	}
private:
	R(*m_Handle)(void*, Args...);
	void* m_Instance;
};

#endif
