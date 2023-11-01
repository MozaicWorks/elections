#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

class Elections
{

private:
	vector<string> candidates;
	vector<string> officialCandidates;
	vector<int> votesWithoutDistricts;
	map<string, vector<int>> votesWithDistricts;
	map<string, vector<string>> list;
	bool withDistrict;

public:
	Elections(const map<string, vector<string>> &list, bool withDistrict) : list(list), withDistrict(withDistrict), votesWithDistricts(){};

	void addCandidate(const string &candidate);

	void voteFor(const string &elector, const string &candidate, const string &electorDistrict);

	map<string, string> results() const;

private:
	void recordVoteForElectionWithoutDistrict(const string &);
	void recordVoteForExistingCandidateInNoDistrictElections(const string &);
	void recordVoteForNewCandidateInNoDistrictElections(const string &);

	void recordVoteForElectionWithDistricts(const string &, const string &);
	void recordVoteForExistingCandidateInElectionWithDistrict(const string &, vector<int> &) const;
	void recordVoteForNewCandidateInElectionWithDistrict(const string &, vector<int> &);

	string computeAndFormatVotesPercentageOfCategory(const int blankVotes, const int nbVotes) const;
	string computeAndFormatAbstentionData(const int nbVotes) const;

	int totalNumberOfVotesForElectionsWithoutDistricts() const;

	int totalNumberOfVotesForElectionsWithDistricts() const;

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
