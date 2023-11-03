#include <vector>
#include <numeric>
#include <algorithm>

#include "ElectionResultsFormatter.h"

string ElectionResultsFormatter::computeAndFormatVotesPercentageOfCategory(const int votesOfACategory, const int totalNumberOfVotes) const
{
    float percentageResult = ((float)votesOfACategory * 100) / totalNumberOfVotes;
    return format(percentageResult);
}

string ElectionResultsFormatter::computeAndFormatAbstentionData(const map<string, vector<string>> &list, const int nbVotes) const
{
    vector<vector<string>> values;
    transform(list.begin(), list.end(), back_inserter(values), [](const auto &val)
              { return val.second; });

    vector<int> sizes;
    transform(values.begin(), values.end(), back_inserter(sizes), [](const auto &v)
              { return v.size(); });
    int nbElectors = accumulate(sizes.begin(), sizes.end(), 0);
    float abstentionResult = 100 - ((float)nbVotes * 100 / nbElectors);
    return format(abstentionResult);
}
