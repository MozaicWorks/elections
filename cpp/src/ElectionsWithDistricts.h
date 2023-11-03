#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

class ElectionsWithDistricts
{
private:
    vector<string> candidates;
    vector<string> officialCandidates;
    map<string, vector<int>> votesWithDistricts;
    map<string, vector<string>> list;

public:
    ElectionsWithDistricts(map<string, vector<string>> list) : candidates{}, officialCandidates{}, votesWithDistricts{}, list{list} {};

    void addCandidate(const string &);
    void recordVote(const string &, const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &, vector<int> &) const;
    void recordVoteForNewCandidate(const string &, vector<int> &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;

    string computeAndFormatVotesPercentageOfCategory(const int blankVotes, const int nbVotes) const;
    string computeAndFormatAbstentionData(const int nbVotes) const;

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