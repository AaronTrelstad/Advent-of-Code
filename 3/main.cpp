#include <iostream>
#include <fstream>
#include <cctype>

inline int parse_num(std::string str, int length, int *indexPtr)
{
    int left = 0;
    int i = *indexPtr;

    while (i < length)
    {
        char character = str[i];

        if (character == ',')
        {
            break;
        }
        else if (character < '0' || character > '9')
        {
            *indexPtr = i;
            return 0;
        }

        left = left * 10 + (character - '0');
        i++;
    }

    if (i == length)
    {
        return 0;
    }

    i++;
    int right = 0;

    while (i < length)
    {
        char character = str[i];

        if (character == ')')
        {
            break;
        }
        else if (character < '0' || character > '9')
        {
            *indexPtr = i;
            return 0;
        }

        right = right * 10 + (character - '0');
        i++;
    }

    if (i == length)
    {
        *indexPtr = i;
        return 0;
    }

    *indexPtr = i;
    return left * right;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string str;

    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            str += line;
        }
    }

    // Part 1
    char mul_chars[] = {'m', 'u', 'l', '('};

    int mul_place = 0;
    int ans = 0;

    for (int i = 0; i < str.length(); i++)
    {
        char character = str[i];

        if (mul_place != 4)
        {
            if (character == mul_chars[mul_place])
            {
                mul_place++;
            }
            else
            {
                mul_place = 0;
            }
        }
        else
        {
            ans += parse_num(str, str.length(), &i);
            mul_place = 0;
        }
    }

    std::cout << ans << std::endl;;

    // Part 2
    char do_chars[] = {'d', 'o', '(', ')'};
    char dont_chars[] = {'d', 'o', 'n', '\'', 't', '(', ')'};

    mul_place = 0;
    int do_place = 0;
    int dont_place = 0;
    ans = 0;

    for (int i = 0; i < str.length(); i++)
    {
        char character = str[i];

        if (dont_place != 7)
        {
            if (character == dont_chars[dont_place])
            {
                dont_place++;
            }
            else
            {
                dont_place = 0;

                if (mul_place != 4)
                {
                    if (character == mul_chars[mul_place])
                    {
                        mul_place++;
                    }
                    else
                    {
                        mul_place = 0;
                    }
                }
                else
                {
                    ans += parse_num(str, str.length(), &i);
                    mul_place = 0;
                }
            }
        }
        else
        {
            if (character == do_chars[do_place])
            {
                do_place++;

                if (do_place == 4)
                {
                    do_place = 0;
                    dont_place = 0;
                }
            }
            else
            {
                do_place = 0;
            }
        }
    }

    std::cout << ans << std::endl;;
}
