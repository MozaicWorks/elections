#include "Elections.h"
#include <algorithm>
#include <numeric>

void Elections::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
    candidates.push_back(candidate);
    votesWithoutDistricts.push_back(0);
    votesWithDistricts["District 1"].push_back(0);
    votesWithDistricts["District 2"].push_back(0);
    votesWithDistricts["District 3"].push_back(0);
}

void Elections::recordVoteForElectionWithoutDistrict(const string &candidate)
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

void Elections::recordVoteForExistingCandidateInNoDistrictElections(const string &candidate)
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    votesWithoutDistricts[index] = votesWithoutDistricts[index] + 1;
}

void Elections::recordVoteForNewCandidateInNoDistrictElections(const string &candidate)
{
    candidates.push_back(candidate);
    votesWithoutDistricts.push_back(1);
}

void Elections::recordVoteForExistingCandidateInElectionWithDistrict(const string &candidate, vector<int> &districtVotes) const
{
    int index = find(candidates.begin(), candidates.end(), candidate) - candidates.begin();
    districtVotes[index] = districtVotes[index] + 1;
}

void Elections::recordVoteForNewCandidateInElectionWithDistrict(const string &candidate, vector<int> &districtVotes)
{
    candidates.push_back(candidate);
    for (auto &[district, votes] : votesWithDistricts)
    {
        votes.push_back(0);
    }
    districtVotes[candidates.size() - 1] = districtVotes[candidates.size() - 1] + 1;
}

void Elections::recordVoteForElectionWithDistricts(const string &candidate, const string &electorDistrict)
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

void Elections::voteFor(const string &elector, const string &candidate, const string &electorDistrict)
{
    if (withDistrict)
    {
        recordVoteForElectionWithDistricts(candidate, electorDistrict);
    }
    else
    {
        recordVoteForElectionWithoutDistrict(candidate);
    }
}

string Elections::computeAndFormatVotesPercentageOfCategory(const int votesOfACategory, const int totalNumberOfVotes) const
{
    float percentageResult = ((float)votesOfACategory * 100) / totalNumberOfVotes;
    return format(percentageResult);
}

string Elections::computeAndFormatAbstentionData(const int nbVotes) const
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

int Elections::totalNumberOfVotesForElectionsWithoutDistricts() const
{
    return accumulate(votesWithoutDistricts.begin(), votesWithoutDistricts.end(), 0);
}

int Elections::numberOfValidVotesForElectionsWithoutDistricts() const
{
    int nbValidVotes = 0;
    for (int i = 0; i < officialCandidates.size(); i++)
    {
        int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
        nbValidVotes += votesWithoutDistricts[index];
    }

    return nbValidVotes;
}

int Elections::totalNumberOfVotesForElectionsWithDistricts() const
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

map<string, string> Elections::results() const
{
    map<string, string> results;
    int nbVotes = 0;
    int nullVotes = 0;
    int blankVotes = 0;
    int nbValidVotes = 0;

    if (!withDistrict)
    {
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
    }
    else
    {
        nbVotes = totalNumberOfVotesForElectionsWithDistricts();

        for (int i = 0; i < officialCandidates.size(); i++)
        {
            int index = find(candidates.begin(), candidates.end(), officialCandidates[i]) - candidates.begin();
            for (auto entry : votesWithDistricts)
            {
                vector<int> districtVotes = entry.second;
                nbValidVotes += districtVotes[index];
            }
        }

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
    }

    results["Blank"] = computeAndFormatVotesPercentageOfCategory(blankVotes, nbVotes);
    results["Null"] = computeAndFormatVotesPercentageOfCategory(nullVotes, nbVotes);
    results["Abstention"] = computeAndFormatAbstentionData(nbVotes);

    return results;
}