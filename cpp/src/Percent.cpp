#include <sstream>
#include <iomanip>

#include "Percent.h"

float Percent::value() const
{
    if(total == 0)
        return 0;

    return ((float)partial * 100) / total;
}

Percent Percent::rest() const
{
    return Percent(total - partial, total);
}

string Percent::format() const
{
    // This function is only needed if std::format is not implemented in your standard library
    // or if the locale support doesn't allow usage of fr-FR
    ostringstream s;
    s << std::fixed << std::setprecision(2) << value() << "%";
    string result = s.str();
    // HACK: This is a hack to simulate the fr-FR locale
    // We know that only numbers need to be formatted with "," instead of ".", so just replace them
    replace(result.begin(), result.end(), '.', ',');
    return result;
}