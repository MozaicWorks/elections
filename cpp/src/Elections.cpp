#include "Elections.h"
#include <algorithm>
#include <numeric>

void Elections::addCandidate(const string &candidate)
{
    electionsWithoutDistricts.addCandidate(candidate);
    electionsWithDistricts.addCandidate(candidate);
}

void Elections::voteFor(const string &elector, const string &candidate, const string &electorDistrict)
{
    if (withDistrict)
    {
        electionsWithDistricts.recordVote(candidate, electorDistrict);
    }
    else
    {
        electionsWithoutDistricts.recordVoteForElectionWithoutDistrict(candidate);
    }
}

map<string, string> Elections::results() const
{
    return withDistrict ? electionsWithDistricts.results() : electionsWithoutDistricts.resultsWithoutDistricts();
}