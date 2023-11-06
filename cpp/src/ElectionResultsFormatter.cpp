#include <vector>
#include <numeric>
#include <algorithm>

#include "Percent.h"
#include "ElectionResultsFormatter.h"

string ElectionResultsFormatter::formatResult(const int votesOfACategory, const int totalNumberOfVotes) const
{
    return Percent(votesOfACategory, totalNumberOfVotes).format();
}

string ElectionResultsFormatter::formatAbstentions(const map<string, vector<string>> &electorsByDistrict, const int nbVotes) const
{
    vector<vector<string>> values;
    transform(electorsByDistrict.begin(), electorsByDistrict.end(), back_inserter(values), [](const auto &val)
              { return val.second; });

    vector<int> sizes;
    transform(values.begin(), values.end(), back_inserter(sizes), [](const auto &v)
              { return v.size(); });
    int nbElectors = accumulate(sizes.begin(), sizes.end(), 0);
    return Percent(nbVotes, nbElectors).rest().format();
}
