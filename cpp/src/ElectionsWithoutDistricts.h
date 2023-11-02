#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

using namespace std;

class ElectionsWithoutDistricts
{
private:
    vector<string> candidates;
	vector<string> officialCandidates;
    vector<int> votesWithoutDistricts;
    map<string, vector<string>> list;

public:
    ElectionsWithoutDistricts(const map<string, vector<string>> &list) : list(list), votesWithoutDistricts{}, officialCandidates{} {};

    void addCandidate(const string &);

    void recordVoteForElectionWithoutDistrict(const string &);
    void recordVoteForExistingCandidateInNoDistrictElections(const string &);
    void recordVoteForNewCandidateInNoDistrictElections(const string &);

    int totalNumberOfVotesForElectionsWithoutDistricts() const;
    int numberOfValidVotesForElectionsWithoutDistricts() const;

    map<string, string> resultsWithoutDistricts() const;

    string computeAndFormatVotesPercentageOfCategory(const int votesOfACategory, const int totalNumberOfVotes) const
    {
        float percentageResult = ((float)votesOfACategory * 100) / totalNumberOfVotes;
        return format(percentageResult);
    }

    string computeAndFormatAbstentionData(const int nbVotes) const
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

    string format(const auto &param) const
    {
        // This function is only needed if std::format is not implemented in your standard library
        // or if the locale support doesn't allow usage of fr-FR
        ostringstream s;
        s << std::fixed << std::setprecision(2) << param << "%";
        string result = s.str();
        // HACK: This is a hack to simulate the fr-FR locale
        // We know that only numbers need to be formatted with "," instead of ".", so just replace them
        replace(result.begin(), result.end(), '.', ',');
        return result;
    };
};