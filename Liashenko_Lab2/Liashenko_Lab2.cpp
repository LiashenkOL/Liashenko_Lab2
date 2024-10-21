#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

map<char, double> englishFreq = {
    {'A', 8.08}, {'B', 1.67}, {'C', 3.18}, {'D', 3.99}, {'E', 12.56},
    {'F', 2.17}, {'G', 1.80}, {'H', 5.27}, {'I', 7.24}, {'J', 0.14},
    {'K', 0.63}, {'L', 4.04}, {'M', 2.60}, {'N', 7.38}, {'O', 7.47},
    {'P', 1.91}, {'Q', 0.09}, {'R', 6.42}, {'S', 6.59}, {'T', 9.15},
    {'U', 2.79}, {'V', 1.00}, {'W', 1.89}, {'X', 0.21}, {'Y', 1.65},
    {'Z', 0.07}
};

map<char, double> calculateFrequencies(const string& message) {
    map<char, int> count;
    int total = 0;
    for (char c : message) {
        if (isalpha(c)) {
            count[toupper(c)]++;
            total++;
        }
    }

    map<char, double> frequencies;
    for (char c = 'A'; c <= 'Z'; c++) {
        frequencies[c] = (count[c] * 100.0) / total;
    }
    return frequencies;
}

int findShift(const map<char, double>& messageFreq) {
    int bestShift = 0;
    double bestDiff = 1e9;

    for (int shift = 0; shift < 26; shift++) {
        double totalDiff = 0;
        for (const auto& pair : englishFreq) {
            char shiftedChar = ((pair.first - 'A' + shift) % 26) + 'A';
            double messageFreqValue = messageFreq.find(shiftedChar) != messageFreq.end() ? messageFreq.at(shiftedChar) : 0.0;
            double diff = abs(pair.second - messageFreqValue);
            totalDiff += diff;
        }
        if (totalDiff < bestDiff) {
            bestDiff = totalDiff;
            bestShift = shift;
        }
    }

    return (26 - bestShift) % 26;  // Convert to left shift
}

string decrypt(const string& message, int shift) {
    string decrypted = "";
    for (char c : message) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            decrypted += static_cast<char>((c - base + shift) % 26 + base);
        }
        else {
            decrypted += c;
        }
    }
    return decrypted;
}

int main() {
    string message;
    getline(cin, message);

    // Check constraints
    if (message.length() < 67 || message.length() >= 1000) {
        cerr << "Error: Message length must be between 67 and 999 characters." << endl;
        return 1;
    }

    try {
        map<char, double> frequencies = calculateFrequencies(message);
        int shift = findShift(frequencies);
        string decrypted = decrypt(message, shift);

        cout << decrypted << endl;
    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}