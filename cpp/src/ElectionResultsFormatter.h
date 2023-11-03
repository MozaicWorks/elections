#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

class ElectionResultsFormatter
{
public:
    string computeAndFormatVotesPercentageOfCategory(const int blankVotes, const int nbVotes) const;
    string computeAndFormatAbstentionData(const map<string, vector<string>> &list, const int nbVotes) const;

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