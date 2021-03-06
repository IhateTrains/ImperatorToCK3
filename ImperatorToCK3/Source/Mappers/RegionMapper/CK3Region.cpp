#include "CK3Region.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"
#include "Log.h"

mappers::CK3Region::CK3Region(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::CK3Region::registerKeys()
{
	registerKeyword("regions", [this](std::istream& theStream) {
		for (const auto& name : commonItems::getStrings(theStream))
			regions.emplace(name, nullptr);
	});
	registerKeyword("duchies", [this](std::istream& theStream) {
		for (const auto& name : commonItems::getStrings(theStream))
			duchies.emplace(name, nullptr);
	});
	registerKeyword("counties", [this](std::istream& theStream) {
		for (const auto& name : commonItems::getStrings(theStream))
			counties.emplace(name, nullptr);
	});
	registerKeyword("provinces", [this](std::istream& theStream) {
		for (const auto& id : commonItems::getULlongs(theStream))
			provinces.insert(id);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

bool mappers::CK3Region::regionContainsProvince(const unsigned long long province) const
{
	for (const auto& [regionName, region]: regions)
		if (region && region->regionContainsProvince(province))
			return true;

	for (const auto& [duchyName, duchy] : duchies)
		if (duchy && duchy->duchyContainsProvince(province))
			return true;
		
	for (const auto& [countyName, county] : counties)
		if (county && county->getCountyProvinces().contains(province))
			return true;
	
	if (provinces.contains(province))
		return true;
	
	return false;
}
