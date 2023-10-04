#include <iostream>
#include <string>
#include <typeinfo>

template<typename T>
class Monad
{
private:
    T value;

public:
    Monad(const T& initialValue) : value(initialValue) {}

    template<typename P>
    Monad<P> operator>>(P (*func)(int32_t)) const
    {
        return Monad<P>{ func(value) };
    }

    T Value() const
    {
        return value;
    }
};

int32_t Add(int32_t x)
{
    return x + 2;
}

int32_t Multiply(int32_t x)
{
    return x * 7;
}

std::string ToString(int32_t x)
{
    return std::to_string(x);
}

int main()
{
    auto operations = Monad<int32_t>{ 13 }
        >> Multiply
        >> Add
        >> ToString;
    
    auto result = operations.Value();
    std::cout << "Result: " << result << '(' << typeid(result).name() << ')' << std::endl;

    return 0;
}