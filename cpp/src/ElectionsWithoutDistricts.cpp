#include "ElectionsWithoutDistricts.h"

void ElectionsWithoutDistricts::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
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

map<string, string> ElectionsWithoutDistricts::resultsWithoutDistricts() const
{
    map<string, string> results;
    int nbVotes = 0;
    int nullVotes = 0;
    int blankVotes = 0;
    int nbValidVotes = 0;

    nbVotes = totalNumberOfVotesForElectionsWithoutDistricts();
    nbValidVotes = numberOfValidVotesForElectionsWithoutDistricts();

    for (int i = 0; i < votesWithoutDistricts.size(); i++)
    {
        float candidatResult = ((float)votesWithoutDistricts[i] * 100) / nbValidVotes;
        string candidate = candidates[i];
        if (count(officialCandidates.begin(), officialCandidates.end(), candidate) > 0)
        {
            results[candidate] = format(candidatResult);
        }
        else
        {
            if (candidates[i].size() == 0)
            {
                blankVotes += votesWithoutDistricts[i];
            }
            else
            {
                nullVotes += votesWithoutDistricts[i];
            }
        }
    }
    results["Blank"] = computeAndFormatVotesPercentageOfCategory(blankVotes, nbVotes);
    results["Null"] = computeAndFormatVotesPercentageOfCategory(nullVotes, nbVotes);
    results["Abstention"] = computeAndFormatAbstentionData(nbVotes);
    return results;
}

int ElectionsWithoutDistricts::totalNumberOfVotesForElectionsWithoutDistricts() const
{
    return accumulate(votesWithoutDistricts.begin(), votesWithoutDistricts.end(), 0);
}

int ElectionsWithoutDistricts::numberOfValidVotesForElectionsWithoutDistricts() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
        nbValidVotes += votesWithoutDistricts[index];
    }

    return nbValidVotes;
}

