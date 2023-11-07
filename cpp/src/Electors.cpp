#include "Electors.h"
#include <numeric>

int Electors::count() const
{
    vector<vector<string>> electors{};
    transform(electorsByDistrict.begin(), electorsByDistrict.end(), back_inserter(electors), [](const auto &val)
              { return val.second; });

    vector<int> electorCountsPerDistrict;
    transform(electors.begin(), electors.end(), back_inserter(electorCountsPerDistrict), [](const auto &v)
              { return v.size(); });
    return accumulate(electorCountsPerDistrict.begin(), electorCountsPerDistrict.end(), 0);
}