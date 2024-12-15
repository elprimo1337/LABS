#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::min; // Теперь используем std::min
using std::cerr; // Теперь используем std::cerr
using std::cout;
using std::string;
using std::max;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::stringstream;


void filltab(std::vector<int>& tab, const std::string& understring) {
    int k = understring.length();
    for (int i = 0; i < 256; ++i) {
        tab[i] = k;
    }
    for (int i = 0; i < k - 1; ++i) {
        tab[unsigned char(understring[i])] = k - 1 - i;
    }
}

std::vector<int> search(const std::string& pattern, const std::string& text, const std::vector<int>& tab, int start, int end) {
    std::vector<int> occurrences;
    int m = pattern.length();
    int n = text.length();
    int i = start + m - 1;
    int j = m - 1;

    start = max(0, start);
    end = min((int)text.length(), end); // используем std::min здесь

    while (i <= end) {
        if (i >= start && i <= end) {
            while (j >= 0 && text[i] == pattern[j]) {
                i--;
                j--;
            }
            if (j == -1) {
                occurrences.push_back(i + 1);
                i += m+1;
                j = m - 1;
            }
            else {
                int shift;
                if (j == m - 1) {
                    shift = tab[unsigned char(text[i])];
                }
                else {
                    shift = tab[unsigned char(pattern[j])]+1;
                }
                i += max(1, shift);
                j = m - 1;
            }
        }
        else {
            i++;
        }
    }
    return occurrences;
}

int main() {
    string pattern, text, rangeLine;
    int start, end;

    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        getline(inputFile, pattern);
        getline(inputFile, text);
        getline(inputFile, rangeLine);

        stringstream ss(rangeLine);
        ss >> start >> end;
        inputFile.close();
    }
    else {
        cerr << "Не удалось открыть файл input.txt" << endl; // используем std::cerr
        return 1;
    }

    vector<int> tab(256, 0);
    filltab(tab, pattern);
    vector<int> results = search(pattern, text, tab, start, end);

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        if (results.empty()) {
            outputFile << "-1" << endl;
        }
        else {
            for (int index : results) {
                outputFile << index << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    }
    else {
        cerr << "Не удалось открыть файл output.txt" << endl; // используем std::cerr
        return 1;
    }

    return 0;
}
