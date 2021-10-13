#include <iostream>

class Handler{
public:
    virtual void* data() = 0;

    virtual void const* data() const = 0;

};

template<typename T>
class UniHandler: public Handler{
private:
    T value;

public:
    UniHandler(T val): value{val} {}

    void* data() override {return static_cast<void*>(&value); }

    void const* data() const override {return static_cast<void const*>(&value); }
};


class Any{
private:
    Handler* value;

public:
    Any(): value{nullptr} {}

    template<typename T>
    Any(T val): value{new UniHandler<T>(val)} {}

    template <typename T>
	Any(Any const &other)
	{
		delete[] value;
		value = new UniHandler<T>(other.as<T>());
	}

	~Any() {delete value;}

	template <typename T>
	Any& operator=(T val)
	{
	    delete[] value;
	    value = new UniHandler<T>(val);
	    return *this;
	}

	template <typename T>
	Any& operator=(Any const &other)
	{
	    delete[] value;
		value = new UniHandler<T>(other.as<T>());
	    return *this;
	}

	template <typename T>
	T& as() {
		auto& v = dynamic_cast<UniHandler<std::decay_t<T>>&>(*value);
		return *static_cast<std::decay_t<T>*>(v.data());
	}

	template <typename T>
	T const& as() const {
		auto const& v = dynamic_cast<UniHandler<std::decay_t<T>> const &>(*value);
		return *static_cast<std::decay_t<T> const*>(v.data());
	}

//	template <typename T>
//	friend std::ostream& operator<<(std::ostream& out, Any  a)
//    {
//        out << (*value).get_value();
//        return out;
//    }
//
//    template <typename T>
//    friend std::istream& operator>>(std::istream& out, Any& a)
//    {
//        T val;
//        out >> val;
//        a = val;
//        return out;
//    }
};

int main()
{
    Any a1(12);
    std::cout << a1.as<int>() << '\n';
    return 0;
}
