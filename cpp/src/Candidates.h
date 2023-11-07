#include <string>
#include <vector>

using namespace std;

class Candidates
{
private:
    vector<string> candidates;
    vector<string> officialCandidates;

public:
    Candidates() : officialCandidates{}, candidates{} {}

    vector<string> getOfficialCandidates() const
    {
        return officialCandidates;
    }

    void add(const string &candidateName)
    {
        officialCandidates.push_back(candidateName);
        candidates.push_back(candidateName);
    }

    void addUnofficialCandidate(const string &candidateName)
    {
        candidates.push_back(candidateName);
    }

    bool exists(const string &candidateName)
    {
        return (count(candidates.begin(), candidates.end(), candidateName) > 0);
    }

    int indexOf(const string &candidateName)
    {
        return find(candidates.begin(), candidates.end(), candidateName) - candidates.begin();
    }

    string get(const int index) const
    {
        return candidates[index];
    }

    bool isValidCandidate(const string &candidateName) const
    {
        return (count(officialCandidates.begin(), officialCandidates.end(), candidateName) > 0);
    }

    int indexOfOfficialCandidateInCandidates(const int indexOfOfficialCandidate) const
    {
        const string officialCandidateName = officialCandidates[indexOfOfficialCandidate];
        return find(candidates.begin(), candidates.end(), officialCandidateName) - candidates.begin();
    }

    bool isBlank(const int candidateIndex) const
    {
        return (candidates[candidateIndex].size() == 0);
    }
};