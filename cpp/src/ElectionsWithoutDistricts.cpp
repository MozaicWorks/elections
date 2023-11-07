#include "Electors.h"
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
    const int nbVotes = totalNumberOfVotes();
    const int nbValidVotes = numberOfValidVotes();

    map<string, string> results;
    int nullVotes = 0;
    int blankVotes = 0;

    for (int i = 0; i < votes.size(); i++)
    {
        string candidate = candidates[i];
        const bool isValidCandidate = (count(officialCandidates.begin(), officialCandidates.end(), candidate) > 0);
        const bool voteIsBlank = (candidates[i].size() == 0);

        if (isValidCandidate)
            results[candidate] = electionResultsFormatter.formatResult(votes[i], nbValidVotes);

        if (!isValidCandidate && voteIsBlank)
            blankVotes += votes[i];

        if (!isValidCandidate && !voteIsBlank)
            nullVotes += votes[i];
    }
    results["Blank"] = electionResultsFormatter.formatResult(blankVotes, nbVotes);
    results["Null"] = electionResultsFormatter.formatResult(nullVotes, nbVotes);
    results["Abstention"] = electionResultsFormatter.formatAbstentions(nbVotes, electors.count());
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
