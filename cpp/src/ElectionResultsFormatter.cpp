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
    return Percent(nbVotes, countElectors(electorsByDistrict)).rest().format();
}

string ElectionResultsFormatter::formatAbstentions(const int nbVotes, const int electorsCount) const
{
    return Percent(nbVotes, electorsCount).rest().format();
}

int ElectionResultsFormatter::countElectors(const map<string, vector<string>> &electorsByDistrict) const
{
    vector<vector<string>> electors;
    transform(electorsByDistrict.begin(), electorsByDistrict.end(), back_inserter(electors), [](const auto &val)
              { return val.second; });

    vector<int> electorCountsPerDistrict;
    transform(electors.begin(), electors.end(), back_inserter(electorCountsPerDistrict), [](const auto &v)
              { return v.size(); });
    return accumulate(electorCountsPerDistrict.begin(), electorCountsPerDistrict.end(), 0);
}