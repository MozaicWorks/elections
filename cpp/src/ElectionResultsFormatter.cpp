#include <vector>
#include <numeric>
#include <algorithm>

#include "Percent.h"
#include "ElectionResultsFormatter.h"

string ElectionResultsFormatter::formatResult(const int votesOfACategory, const int totalNumberOfVotes) const
{
    return Percent(votesOfACategory, totalNumberOfVotes).format();
}

string ElectionResultsFormatter::formatAbstentions(const int nbVotes, const int electorsCount) const
{
    return Percent(nbVotes, electorsCount).rest().format();
}