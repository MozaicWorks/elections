#include "ElectionsWithoutDistricts.h"

void ElectionsWithoutDistricts::addCandidate(const string &candidate)
{
    candidates.push_back(candidate);
    votesWithoutDistricts.push_back(0);
}

void ElectionsWithoutDistricts::recordVoteForElectionWithoutDistrict(const string &candidate)
{
    const bool candidateFoundInCandidates = (count(candidates.begin(), candidates.end(), candidate) > 0);
    if (candidateFoundInCandidates)
    {
        recordVoteForExistingCandidateInNoDistrictElections(candidate);
    }
    else
    {
        recordVoteForNewCandidateInNoDistrictElections(candidate);
    }
}

void ElectionsWithoutDistricts::recordVoteForExistingCandidateInNoDistrictElections(const string &candidate)
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    votesWithoutDistricts[index] = votesWithoutDistricts[index] + 1;
}

void ElectionsWithoutDistricts::recordVoteForNewCandidateInNoDistrictElections(const string &candidate)
{
    candidates.push_back(candidate);
    votesWithoutDistricts.push_back(1);
}