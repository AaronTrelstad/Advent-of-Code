#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void sort(std::vector<int>& array, int length) {
    bool swapped;

    for (int i = 0; i < length - 1; i++) {
        swapped = true;

        for (int j = 0; j < length - i - 1; j++) {
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    std::vector<int> nums1;
    std::vector<int> nums2;
    int total_distance = 0;

    if (inputFile.is_open()) {
        std::string line;
        int length = 0;

        while (std::getline(inputFile, line)) {
            length++;

            int space = line.find(' ');
            nums1.push_back(std::stoi(line.substr(0, space)));
            nums2.push_back(std::stoi(line.substr(space+1)));
        }

        sort(nums1, length);
        sort(nums2, length);

        // Part 1

        for (int i = 0; i < length; i++) {
            total_distance += std::abs(nums1[i] - nums2[i]);
        }

        std::cout << total_distance << std::endl;

        // Part 2

        std::unordered_map<int, int> frequencies;
        int similarity_score = 0;

        for (int i = 0; i < length; i++) {
            int num = nums2[i];

            if (frequencies.count(num) > 0) {
                frequencies[num]++;
            } else {
                frequencies[num] = 1;
            }
        }

        for (int i = 0; i < length; i++) {
            similarity_score +=  nums1[i] * frequencies[nums1[i]];
        }

        std::cout << similarity_score << std::endl;

    }
}
