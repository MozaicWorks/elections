#include "ElectionsWithoutDistricts.h"

void ElectionsWithoutDistricts::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
    candidates.push_back(candidate);
    votes.push_back(0);
}

void ElectionsWithoutDistricts::recordVote(const string &candidate)
{
    const bool candidateFoundInCandidates = (count(candidates.begin(), candidates.end(), candidate) > 0);
    if (candidateFoundInCandidates)
    {
        recordVoteForExistingCandidate(candidate);
    }
    else
    {
        recordVoteForNewCandidate(candidate);
    }
}

void ElectionsWithoutDistricts::recordVoteForExistingCandidate(const string &candidate)
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    votes[index] = votes[index] + 1;
}

void ElectionsWithoutDistricts::recordVoteForNewCandidate(const string &candidate)
{
    candidates.push_back(candidate);
    votes.push_back(1);
}

map<string, string> ElectionsWithoutDistricts::results() const
{
    map<string, string> results;
    int nbVotes = 0;
    int nullVotes = 0;
    int blankVotes = 0;
    int nbValidVotes = 0;

    nbVotes = totalNumberOfVotes();
    nbValidVotes = numberOfValidVotes();

    for (int i = 0; i < votes.size(); i++)
    {
        float candidatResult = ((float)votes[i] * 100) / nbValidVotes;
        string candidate = candidates[i];
        if (count(officialCandidates.begin(), officialCandidates.end(), candidate) > 0)
        {
            results[candidate] = electionResultsFormatter.format(candidatResult);
        }
        else
        {
            if (candidates[i].size() == 0)
            {
                blankVotes += votes[i];
            }
            else
            {
                nullVotes += votes[i];
            }
        }
    }
    results["Blank"] = electionResultsFormatter.computeAndFormatVotesPercentageOfCategory(blankVotes, nbVotes);
    results["Null"] = electionResultsFormatter.computeAndFormatVotesPercentageOfCategory(nullVotes, nbVotes);
    results["Abstention"] = electionResultsFormatter.computeAndFormatAbstentionData(list, nbVotes);
    return results;
}

int ElectionsWithoutDistricts::totalNumberOfVotes() const
{
    return accumulate(votes.begin(), votes.end(), 0);
}

int ElectionsWithoutDistricts::numberOfValidVotes() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
        nbValidVotes += votes[index];
    }

    return nbValidVotes;
}
