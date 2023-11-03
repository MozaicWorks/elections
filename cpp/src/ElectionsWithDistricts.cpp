#include "ElectionsWithDistricts.h"

void ElectionsWithDistricts::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
    candidates.push_back(candidate);
    votesWithDistricts["District 1"].push_back(0);
    votesWithDistricts["District 2"].push_back(0);
    votesWithDistricts["District 3"].push_back(0);
}

void ElectionsWithDistricts::recordVoteForExistingCandidateInElectionWithDistrict(const string &candidate, vector<int> &districtVotes) const
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    districtVotes[index] = districtVotes[index] + 1;
}

void ElectionsWithDistricts::recordVoteForNewCandidateInElectionWithDistrict(const string &candidate, vector<int> &districtVotes)
{
    candidates.push_back(candidate);
    for (auto &[district, votes] : votesWithDistricts)
    {
        votes.push_back(0);
    }
    districtVotes[candidates.size() - 1] = districtVotes[candidates.size() - 1] + 1;
}

void ElectionsWithDistricts::recordVoteForElectionWithDistricts(const string &candidate, const string &electorDistrict)
{
    vector<int> &districtVotes = votesWithDistricts[electorDistrict];
    const bool candidateFoundInCandidates = (count(candidates.begin(), candidates.end(), candidate) > 0);

    if (candidateFoundInCandidates)
    {
        recordVoteForExistingCandidateInElectionWithDistrict(candidate, districtVotes);
    }
    else
    {
        recordVoteForNewCandidateInElectionWithDistrict(candidate, districtVotes);
    }
}

