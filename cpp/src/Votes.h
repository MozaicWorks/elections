#pragma once

#include <vector>
#include <numeric>

using namespace std;

class Votes
{
private:
    vector<int> votes;

public:
    Votes() : votes{} {};

    void initializeVotesForCandidate()
    {
        votes.push_back(0);
    }

    void recordVoteForExistingCandidate(const int candidateIndex)
    {
        votes[candidateIndex] = votes[candidateIndex] + 1;
    }

    void recordVoteForNewCandidate()
    {
        votes.push_back(1);
    }

    int totalNumberOfVotes() const
    {
        return accumulate(votes.begin(), votes.end(), 0);
    }

    int get(const int index) const
    {
        return votes[index];
    }

    int size() const
    {
        return votes.size();
    }
};