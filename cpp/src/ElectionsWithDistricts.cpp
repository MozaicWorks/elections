#include <numeric>
#include <algorithm>

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

int ElectionsWithDistricts::totalNumberOfVotesForElectionsWithDistricts() const
{
    int nbVotes = 0;
    for (auto entry : votesWithDistricts)
    {
        vector<int> districtVotes = entry.second;
        int nbVotesPerDistrict = accumulate(districtVotes.begin(), districtVotes.end(), 0);
        nbVotes += nbVotesPerDistrict;
    }

    return nbVotes;
}

int ElectionsWithDistricts::numberOfValidVotesForElectionsWithDistricts() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
        for (auto entry : votesWithDistricts)
        {
            vector<int> districtVotes = entry.second;
            nbValidVotes += districtVotes[index];
        }
    }
    return nbValidVotes;
}

map<string, string> ElectionsWithDistricts::resultsWithDistricts() const
{
    map<string, string> results;
    int nbVotes = 0;
    int nullVotes = 0;
    int blankVotes = 0;
    int nbValidVotes = 0;

    nbVotes = totalNumberOfVotesForElectionsWithDistricts();
    nbValidVotes = numberOfValidVotesForElectionsWithDistricts();

    map<string, int> officialCandidatesResult;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        officialCandidatesResult[candidates[i]] = 0;
    }
    for (auto entry : votesWithDistricts)
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
        float ratioCandidate = ((float)officialCandidatesResult[candidates[i]]) / officialCandidatesResult.size() * 100;
        results[candidates[i]] = format(ratioCandidate);
    }
    results["Blank"] = computeAndFormatVotesPercentageOfCategory(blankVotes, nbVotes);
    results["Null"] = computeAndFormatVotesPercentageOfCategory(nullVotes, nbVotes);
    results["Abstention"] = computeAndFormatAbstentionData(nbVotes);
    return results;
}

string ElectionsWithDistricts::computeAndFormatVotesPercentageOfCategory(const int votesOfACategory, const int totalNumberOfVotes) const
{
    float percentageResult = ((float)votesOfACategory * 100) / totalNumberOfVotes;
    return format(percentageResult);
}

string ElectionsWithDistricts::computeAndFormatAbstentionData(const int nbVotes) const
{
    vector<vector<string>> values;
    transform(list.begin(), list.end(), back_inserter(values), [](const auto &val)
              { return val.second; });

    vector<int> sizes;
    transform(values.begin(), values.end(), back_inserter(sizes), [](const auto &v)
              { return v.size(); });
    int nbElectors = accumulate(sizes.begin(), sizes.end(), 0);
    float abstentionResult = 100 - ((float)nbVotes * 100 / nbElectors);
    return format(abstentionResult);
}