#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <numeric>
#include <initializer_list>

template<typename T>
auto Query(const std::vector<T>& items)
{
	return [=] (bool (*predicate)(T))
	{
		std::vector<T> results;
		std::copy_if(items.begin(), items.end(), std::back_inserter(results), predicate);
		return results;
	};
}

template<typename T>
auto Map(const std::vector<T>& items)
{
	return [=]<typename U>(U (*mapping)(T))
	{
		std::vector<T> results;
		std::transform(items.begin(), items.end(), std::back_inserter(results), mapping);
		return results;
	};
}

template<typename T> requires std::is_arithmetic<T>::value
auto Sum(const std::vector<T>& items)
{
	return std::reduce(items.begin(), items.end());
}

template<typename T>
void PrintLine(const std::vector<T>& items)
{
	std::ranges::copy(items, std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

template<typename T>
class Data
{
private:
	std::vector<T> data;

public:
	Data(const std::initializer_list<T>& initialValues) : data{ initialValues } {};

	__declspec(property(get = Get)) T DataProperty;

public:
	std::vector<T> Get()
	{
		return data;
	}
};

int32_t Triple(int32_t inputValue)
{
	return inputValue * 3;
}

bool LargerThan16(int32_t inputValue)
{
	return inputValue > 16;
}

int main()
{
	Data data{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	auto result1 = Map(data.DataProperty)(Triple);
	PrintLine(result1);

	auto result2 = Query(result1)(LargerThan16);
	PrintLine(result2);
	
	auto result3 = Sum(result2);
	std::cout << result3 << std::endl;

	return 0;
}
