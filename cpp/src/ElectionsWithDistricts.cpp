#include <numeric>
#include <algorithm>

#include "Electors.h"
#include "ElectionsWithDistricts.h"

void ElectionsWithDistricts::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
    candidates.push_back(candidate);
    votes["District 1"].push_back(0);
    votes["District 2"].push_back(0);
    votes["District 3"].push_back(0);
}

void ElectionsWithDistricts::recordVoteForExistingCandidate(const string &candidate, vector<int> &districtVotes) const
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    districtVotes[index] = districtVotes[index] + 1;
}

void ElectionsWithDistricts::recordVoteForNewCandidate(const string &candidate, vector<int> &districtVotes)
{
    candidates.push_back(candidate);
    for (auto &[district, votes] : votes)
    {
        votes.push_back(0);
    }
    districtVotes[candidates.size() - 1] = districtVotes[candidates.size() - 1] + 1;
}

void ElectionsWithDistricts::recordVote(const string &candidate, const string &electorDistrict)
{
    vector<int> &districtVotes = votes[electorDistrict];
    const bool candidateFoundInCandidates = (count(candidates.begin(), candidates.end(), candidate) > 0);

    if (candidateFoundInCandidates)
    {
        recordVoteForExistingCandidate(candidate, districtVotes);
    }
    else
    {
        recordVoteForNewCandidate(candidate, districtVotes);
    }
}

int ElectionsWithDistricts::totalNumberOfVotes() const
{
    int nbVotes = 0;
    for (auto entry : votes)
    {
        vector<int> districtVotes = entry.second;
        int nbVotesPerDistrict = accumulate(districtVotes.begin(), districtVotes.end(), 0);
        nbVotes += nbVotesPerDistrict;
    }

    return nbVotes;
}

int ElectionsWithDistricts::numberOfValidVotes() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
        for (auto entry : votes)
        {
            vector<int> districtVotes = entry.second;
            nbValidVotes += districtVotes[index];
        }
    }
    return nbValidVotes;
}

map<string, string> ElectionsWithDistricts::results() const
{
    map<string, string> results;
    int nbVotes = 0;
    int nullVotes = 0;
    int blankVotes = 0;
    int nbValidVotes = 0;

    nbVotes = totalNumberOfVotes();
    nbValidVotes = numberOfValidVotes();

    map<string, int> officialCandidatesResult;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        officialCandidatesResult[candidates[i]] = 0;
    }
    for (auto entry : votes)
    {
        vector<float> districtResult;
        vector<int> districtVotes = entry.second;
        for (int i = 0; i < districtVotes.size(); i++)
        {
            float candidateResult = 0;
            if (nbValidVotes != 0)
                candidateResult = ((float)districtVotes[i] * 100) / nbValidVotes;
            string candidate = candidates[i];
            if (count(officialCandidates.begin(), officialCandidates.end(), candidate) > 0)
            {
                districtResult.push_back(candidateResult);
            }
            else
            {
                if (candidates[i].size() == 0)
                {
                    blankVotes += districtVotes[i];
                }
                else
                {
                    nullVotes += districtVotes[i];
                }
            }
        }
        int districtWinnerIndex = 0;
        for (int i = 1; i < districtResult.size(); i++)
        {
            if (districtResult[districtWinnerIndex] < districtResult[i])
                districtWinnerIndex = i;
        }
        officialCandidatesResult[candidates[districtWinnerIndex]] = officialCandidatesResult[candidates[districtWinnerIndex]] + 1;
    }
    for (int i = 0; i < officialCandidatesResult.size(); i++)
    {
        results[candidates[i]] = electionResultsFormatter.formatResult(officialCandidatesResult[candidates[i]], officialCandidatesResult.size());
    }
    results["Blank"] = electionResultsFormatter.formatResult(blankVotes, nbVotes);
    results["Null"] = electionResultsFormatter.formatResult(nullVotes, nbVotes);

    results["Abstention"] = electionResultsFormatter.formatAbstentions(nbVotes, electors.count());
    return results;
}