#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

class ElectionResultsFormatter
{
public:
    string computeAndFormatVotesPercentageOfCategory(const int blankVotes, const int nbVotes) const;
    string computeAndFormatAbstentionData(const map<string, vector<string>> &list, const int nbVotes) const;
};