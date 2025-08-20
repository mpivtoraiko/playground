// g++ -g -O0 -std=c++20 int_to_roman.cpp -o int_to_roman

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class IntToRomanConverer {
public:
    IntToRomanConverer() {
        // init the lookup map
        _lookup_map[0][1] = 'I';
        _lookup_map[0][5] = 'V';
        _lookup_map[1][1] = 'X';
        _lookup_map[1][5] = 'L';
        _lookup_map[2][1] = 'C';
        _lookup_map[2][5] = 'D';
        _lookup_map[3][1] = 'M';
    }


    string convert(int number) {
        string roman_digits[4]; // max number of digits
        unsigned int decimal_place = 1;
        while(true) {
            if (decimal_place > 4) {
                cout << "We don't support more than 4 decimal places" << endl;
                return string();
            }
            int ratio = number / 10;
            int remainder = number - ratio * 10;
            roman_digits[decimal_place - 1] = _digit_to_roman(remainder, decimal_place);
            //cout << format("next digit: {}\n", roman_digits[decimal_place - 1]);
            if (ratio == 0) {
                break;
            }
            number = ratio;
            ++decimal_place;
        }

        string output;
        for (int idx = 3; idx >= 0; --idx) {
            output += roman_digits[idx];
        }
        return output;
    }

private:
    string _digit_to_roman(unsigned int digit, unsigned int decimal_place) {
        string output;

        if (decimal_place < 1 || decimal_place > 4) {
            cout << format("ERROR: decimal place {} not supported", decimal_place);
            return output;
        }

        --decimal_place;  // _lookup_map is 0-based
        if (digit < 4) {
            for (unsigned int repeat_idx = 0; repeat_idx < digit; ++repeat_idx) {
                output += _lookup_map[decimal_place][1];
            }
        }
        else if (digit == 4) {
            output += _lookup_map[decimal_place][1];
            output += _lookup_map[decimal_place][5];
        }
        else if (digit > 4 && digit < 9) {
            output += _lookup_map[decimal_place][5];
            for (unsigned int repeat_idx = 0; repeat_idx < (digit - 5); ++repeat_idx) {
                output += _lookup_map[decimal_place][1];
            }
        }
        else if (digit == 9) {
            output += _lookup_map[decimal_place][1];
            output += _lookup_map[decimal_place+1][1];
        }
        else {
            output = _lookup_map[decimal_place][digit];
        }
        return output;
    }

    unordered_map<int, char> _lookup_map[4];
};


int main(int argc, char **argv) {
    if (argc != 2) {
        cout << format("Usage: {} decimal_number\n", argv[0]);
        return -1;
    }

    IntToRomanConverer converter;
    cout << converter.convert(atoi(argv[1])) << endl;
}