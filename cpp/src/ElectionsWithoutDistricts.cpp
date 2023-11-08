#include "Electors.h"
#include "ElectionsWithoutDistricts.h"

void ElectionsWithoutDistricts::addCandidate(const string &candidate)
{
    candidates.add(candidate);

    votes.initializeVotesForCandidate();
}

void ElectionsWithoutDistricts::recordVote(const string &candidate)
{
    if (candidates.exists(candidate))
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
    int index = candidates.indexOf(candidate);
    votes.recordVoteForExistingCandidate(index);
}

void ElectionsWithoutDistricts::recordVoteForNewCandidate(const string &candidate)
{
    candidates.addUnofficialCandidate(candidate);
    votes.recordVoteForNewCandidate();
}

map<string, string> ElectionsWithoutDistricts::results() const
{
    const int nbVotes = votes.totalNumberOfVotes();
    const int nbValidVotes = numberOfValidVotes();

    map<string, string> results;
    int nullVotes = 0;
    int blankVotes = 0;

    for (int i = 0; i < votes.size(); i++)
    {
        string candidate = candidates.get(i);
        const bool isValidCandidate = candidates.isValidCandidate(candidate);
        const bool voteIsBlank = candidates.isBlank(i);
        const int votesAtIndex = votes.get(i);

        if (isValidCandidate)
            results[candidate] = electionResultsFormatter.formatResult(votesAtIndex, nbValidVotes);

        if (!isValidCandidate && voteIsBlank)
            blankVotes += votesAtIndex;

        if (!isValidCandidate && !voteIsBlank)
            nullVotes += votesAtIndex;
    }
    results["Blank"] = electionResultsFormatter.formatResult(blankVotes, nbVotes);
    results["Null"] = electionResultsFormatter.formatResult(nullVotes, nbVotes);
    results["Abstention"] = electionResultsFormatter.formatAbstentions(nbVotes, electors.count());
    return results;
}

int ElectionsWithoutDistricts::numberOfValidVotes() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < candidates.howManyOfficialCandidates(); i++)
    {
        int index = candidates.indexOfOfficialCandidateInCandidates(i);
        nbValidVotes += votes.get(index);
    }

    return nbValidVotes;
}