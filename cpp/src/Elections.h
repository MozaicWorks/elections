#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

#include "ElectionsWithoutDistricts.h"
#include "ElectionsWithDistricts.h"

using namespace std;

class Elections
{

private:
	bool withDistrict;

	ElectionsWithoutDistricts electionsWithoutDistricts;
	ElectionsWithDistricts electionsWithDistricts;

public:
	Elections(const map<string, vector<string>> &electorsByDistrict, bool withDistrict) : withDistrict(withDistrict), electionsWithoutDistricts(electorsByDistrict), electionsWithDistricts(electorsByDistrict){};

	void addCandidate(const string &candidate);

	void voteFor(const string &elector, const string &candidate, const string &electorDistrict);

	map<string, string> results() const;
};
