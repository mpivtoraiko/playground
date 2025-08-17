// buid: g++ -g -O0 -std=c++20 sudoku.cpp -o sudoku

#include <vector>
#include <cstdlib>
#include <format>
#include <iostream>

using namespace std;

typedef vector<vector<char>> Board;

#define EMPTY_SPACE ' '

#define INPUT_SAMPLE "\
53  7   2\
6  195   \
 98    6 \
8   6   3\
4  8 3  1\
7   2   6\
 6    28 \
   419  5\
    8  79"

class Solution {
public:


    bool isValidSudoku(Board& board) {        
        // check rows
        for (size_t row_idx = 0; row_idx < 9; ++row_idx) {
            bool checker_cache[9] = {false};
            const vector<char> & cur_row = board[row_idx];
            for (size_t col_idx = 0; col_idx < 9; ++col_idx) {
                if (not check_character(cur_row[col_idx], checker_cache)) {
                    return false;
                }
            }
        }

        // check columns
        for (size_t col_idx = 0; col_idx < 9; ++col_idx) {
            bool checker_cache[9] = {false};
            for (size_t row_idx = 0; row_idx < 9; ++row_idx) {
                if (not check_character(board[row_idx][col_idx], checker_cache)) {
                    return false;
                }
            }
        }

        // check blocks
        for (size_t row_block = 0; row_block < 3; ++row_block) {
            for (size_t col_block = 0; col_block < 3; ++col_block) {
                // run through rows and columns within each block
                bool checker_cache[9] = {false};
                for (size_t row_idx = 3 * row_block; row_idx < 3 * (row_block + 1); ++row_idx) {
                    for (size_t col_idx = 3 * col_block; col_idx < 3 * (col_block + 1); ++col_idx) {
                        if (not check_character(board[row_idx][col_idx], checker_cache)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

private:

    bool check_character(char character, bool *checker) {
        if (character != EMPTY_SPACE) {
            size_t cur_number_idx = static_cast<size_t>(character) - 49;
            if (checker[cur_number_idx] == true) {
                // a violation: we already have this integer in this row
                return false;
            }
            checker[cur_number_idx] = true;
        }
        return true;
    }

};


void process_input(const char* input_str, Board &board)
{
    board.resize(9, std::vector<char>(9));
    size_t input_idx = 0;
    for (size_t row_idx = 0; row_idx < 9; ++row_idx) {
        vector<char> & cur_row = board[row_idx];
        for (size_t col_idx = 0; col_idx < 9; ++col_idx) {
            cur_row[col_idx] = input_str[input_idx++];
        }
    }
    cout << format("Read {} chars\n", input_idx);
}

int main(int argc, char **argv) {
    Board board;
    process_input(INPUT_SAMPLE, board);

    Solution solution;
    bool status = solution.isValidSudoku(board);
    if (status) {
        cout << "Valid" << endl;
    }
    else {
        cout << "Invalid" << endl;
    }

    return 0;
}