#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 */



class Merger 
{
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            // error check
            if (intervals.size() < 2) {
                return intervals;
            }

            size_t interval_idx = 0;
            for (const auto & cur_interval : intervals) {
                if (cur_interval.size() != 2) {
                    cerr << "Interval #" << interval_idx << " is invalid" << endl;
                    return vector<vector<int>>();
                }
            }
            
            // sort intervals by start time
            sort(intervals.begin(), intervals.end(), [](const vector<int> & interval_a, const vector<int> & interval_b) {return interval_a[0] < interval_b[0];});

            vector<vector<int>> out_vector;
            out_vector.reserve(intervals.size());
            out_vector.emplace_back(intervals[0]);
            for (size_t idx = 1; idx < intervals.size(); ++idx) {
                if (out_vector[idx - 1][1] >= intervals[idx][0]) {
                    if (out_vector[idx - 1][1] < intervals[idx][1]) {
                        out_vector[idx - 1][1] = intervals[idx][1];
                    }
                }
                else {
                    out_vector.emplace_back(intervals[idx]);
                }
            }

            return out_vector;
        }


        void print_intervals(const vector<vector<int>>& intervals) 
        {
            bool first_one = true;
            for (const auto &cur_interval : intervals) {
                if (not first_one) {
                    cout << ", ";
                }
                else {
                    first_one = not first_one;
                } 
                cout << "[" << cur_interval[0] << ", " << cur_interval[1] << "]";
            }
            cout << endl;
        }
};



int main(int argc, char **argv)
{
    vector<vector<int>> intervals;
    intervals.emplace_back(vector<int>({1, 4}));
    intervals.emplace_back(vector<int>({4, 5}));

    Merger merger;
    merger.print_intervals(intervals);
    merger.merge(intervals);
    merger.print_intervals(intervals);

}