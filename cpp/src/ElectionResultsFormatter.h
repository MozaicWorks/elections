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
    string formatResult(const int blankVotes, const int nbVotes) const;
    string formatAbstentions(const int nbVotes, const int electorsCount) const;
};