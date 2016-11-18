#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <utility>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<int,int> & pr) {
        os << "(" << pr.first << "," << pr.second << ")";
        return os;
    }
}

class solution {
  public:
    int maximumGap(const std::vector<int> & nums) {
        int max = *std::max_element(nums.begin(), nums.end());
        int min = *std::min_element(nums.begin(), nums.end());
        double gap = (max-min)/double(nums.size()-1);
        std::vector<std::pair<int,int>> buckets(nums.size()-1, std::make_pair(0,0));
        // std::copy(buckets.begin(), buckets.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
        // std::cout << std::endl;
        for (auto n : nums) {
            if (n == max)
                buckets.back().second = n;
            else {
                int idx = int((n-min)/gap);
                if (n > buckets[idx].second)
                    buckets[idx].second = n;
                else if (buckets[idx].first == 0 || n < buckets[idx].first)
                    buckets[idx].first = n;
            }
        }
        // std::copy(buckets.begin(), buckets.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
        // std::cout << std::endl;

        int mxGap = 0;
        int prev;
        size_t i = 0;
        while (i < buckets.size() && buckets[i].first == 0 && buckets[i].second == 0)
            i++;
        if (buckets[i].first != 0)
            mxGap = std::max(buckets[i].second-buckets[i].first, mxGap);
        prev = buckets[i].second;
        i++;
        while (i < buckets.size()) {
            while (i < buckets.size() && (buckets[i].first == 0 && buckets[i].second == 0))
                i++;
            if (i < buckets.size()) {
                if (buckets[i].first != 0)
                    mxGap = std::max({buckets[i].second-buckets[i].first, mxGap, buckets[i].first-prev});
                else
                    mxGap = std::max(buckets[i].second-prev, mxGap);
                prev = buckets[i].second;
            }
            i++;
        }
        return mxGap;
    }
};

int main() {
    std::vector<int> nums(10);
    srand(time(0));
    std::generate(nums.begin(), nums.end(),
                  [&](){
                      return rand()%nums.size()+1;
                  });
    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "After sorting:\n";
    auto cpy = nums;
    std::sort(cpy.begin(), cpy.end());
    std::copy(cpy.begin(), cpy.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::vector<int> diff;
    std::transform(cpy.begin()+1, cpy.end(), cpy.begin(), std::inserter(diff, diff.begin()),
                   [](int first, int second){
                       return first-second;
                   });
    std::cout << "The difference between consecutive numbers are:\n";
    std::copy(diff.begin(), diff.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    solution soln;
    int mxGap = soln.maximumGap(nums);
    std::cout << "The maximum gap is:\n"
              << mxGap << std::endl;
}
