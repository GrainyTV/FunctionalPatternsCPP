#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

static constexpr auto NotFound = std::string::npos;

auto Split(const char delimiter) -> std::function<std::vector<std::string>(const std::string&)>
{
    return [=] (const std::string& textInput)
    {
        std::vector<std::string> result;
        int32_t numberOfDelimiters = std::count(textInput.begin(), textInput.end(), delimiter);
        int32_t position = textInput.find(delimiter);
        result.reserve(numberOfDelimiters + 1);

        if (position == NotFound)
        {
            result.push_back(textInput);
        }
        else
        {
            result.push_back(textInput.substr(0, position));
            std::vector<std::string> remaining = Split(delimiter)(textInput.substr(position + 1));
            result.insert(result.end(), remaining.begin(), remaining.end());
        }

        return result;
    };
};

int main()
{
    std::string fruit{ "apple,banana,orange,grape,watermelon" };
    std::vector<std::string> tokens = Split(',')(fruit);
    
    for (const std::string& token : tokens)
    {
        std::cout << token << std::endl;
    }

    return 0;
}
