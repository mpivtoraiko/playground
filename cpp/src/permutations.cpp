#include <vector>
#include <array>
#include <iostream>



#define MAX_INT 10

typedef std::vector<int> Permutation;
typedef std::array<bool, (MAX_INT) * 2 + 1> CheckHash;

using namespace std;


class Solution {
public:
    vector<vector<int>> permute(Permutation& nums) {
        Permutation perm;
        perm.reserve(nums.size());
        constexpr auto init_array = []() consteval {
                CheckHash bool_array;
                ranges::generate(bool_array, [] () mutable { return false; });
                return bool_array;
            }();
        auto check_hash(init_array);
        evaluate_permutation(perm, check_hash, nums);
        return _output;
    }

private:
    void evaluate_permutation(Permutation permutation, CheckHash check_hash, const Permutation &collection)
    {            
        if (permutation.size() < collection.size()) {
            for (int cur_num : collection) {
                size_t hash_idx = static_cast<size_t>(cur_num + MAX_INT);
                if (check_hash[hash_idx]) {
                    continue; // we have a redundancy, not a valid permutation
                }
                check_hash[hash_idx] = true;
                permutation.push_back(cur_num);

                evaluate_permutation(permutation, check_hash, collection);

                check_hash[hash_idx] = false;
                permutation.pop_back();
            } // end for
        } // end if
        else {
            // we've assembled a full permutation while sifting out the invalid ones, must be a good one
            _output.push_back(permutation);
        }
    }

    vector<Permutation> _output;
};



int main(int argc, char **argv) {
    Solution obj;
    Permutation collection = {1, 2, 3};
    vector<Permutation> permutations = obj.permute(collection);
    for (auto cur_perm : permutations) {
        for (int cur_num : cur_perm) {
            cout << cur_num << ", ";
        }
        cout << endl;
    }
    return 0;
}