#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string>

bool isSafe(std::vector<int> values, int &count)
{
    int length = values.size();
    int prev = values[0];

    bool is_increasing = true;
    bool is_decreasing = true;

    for (int i = 1; i < length; i++)
    {
        int num = values[i];

        if (num >= prev)
        {
            is_decreasing = false;
        }

        if (num <= prev)
        {
            is_increasing = false;
        }

        if (std::abs(num - prev) > 3)
        {
            is_increasing = false;
            is_decreasing = false;
        }

        prev = num;
    }

    if (is_increasing || is_decreasing)
    {
        return true;
    }

    return false;
}

int main()
{
    std::ifstream inputFile("input.txt");
    int count = 0;

    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            std::vector<int> values;
            std::stringstream ss(line);
            std::string value;
            bool safe = true;

            while (ss >> value)
            {
                values.push_back(std::stoi(value));
            }

            if (isSafe(values, count))
            {
                count++;
                continue;
            }

            for (int i = 0; i < values.size(); i++)
            {
                std::vector<int> new_values = values;
                new_values.erase(new_values.begin() + i);

                if (isSafe(new_values, count))
                {
                    count++;
                    break;
                }
            }
        }

        std::cout << count << std::endl;
    }
}
