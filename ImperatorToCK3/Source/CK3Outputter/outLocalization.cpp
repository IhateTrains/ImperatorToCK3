#include "outLocalization.h"
#include <filesystem>
#include <fstream>
#include "../commonItems/OSCompatibilityLayer.h"
#include "../commonItems/CommonFunctions.h"

void CK3::outputLocalization(const std::string& imperatorPath, const std::string& outputName, const World& CK3World)
{
	// copy character/family names localization
	commonItems::TryCopyFile(imperatorPath + "/game/localization/english/character_names_l_english.yml",
		"output/" + outputName + "/localization/replace/IMPERATOR_character_names_l_english.yml");
	commonItems::TryCopyFile(imperatorPath + "/game/localization/french/character_names_l_french.yml",
		"output/" + outputName + "/localization/replace/IMPERATOR_character_names_l_french.yml");
	commonItems::TryCopyFile(imperatorPath + "/game/localization/german/character_names_l_german.yml",
		"output/" + outputName + "/localization/replace/IMPERATOR_character_names_l_german.yml");
	commonItems::TryCopyFile(imperatorPath + "/game/localization/russian/character_names_l_russian.yml",
		"output/" + outputName + "/localization/replace/IMPERATOR_character_names_l_russian.yml");
	commonItems::TryCopyFile(imperatorPath + "/game/localization/spanish/character_names_l_spanish.yml",
		"output/" + outputName + "/localization/replace/IMPERATOR_character_names_l_spanish.yml");

	
	std::ofstream english("output/" + outputName + "/localization/replace/converter_l_english.yml");
	std::ofstream french("output/" + outputName + "/localization/replace/converter_l_french.yml");
	std::ofstream german("output/" + outputName + "/localization/replace/converter_l_german.yml");
	std::ofstream russian("output/" + outputName + "/localization/replace/converter_l_russian.yml");
	std::ofstream spanish("output/" + outputName + "/localization/replace/converter_l_spanish.yml");
	if (!english.is_open())
		throw std::runtime_error("Error writing english localization file! Is the output folder writable?");
	if (!french.is_open())
		throw std::runtime_error("Error writing french localization file! Is the output folder writable?");
	if (!german.is_open())
		throw std::runtime_error("Error writing german localization file! Is the output folder writable?");
	if (!russian.is_open())
		throw std::runtime_error("Error writing russian localization file! Is the output folder writable?");
	if (!spanish.is_open())
		throw std::runtime_error("Error writing spanish localization file! Is the output folder writable?");
	english << commonItems::utf8BOM << "l_english:\n";
	french << commonItems::utf8BOM << "l_french:\n";
	german << commonItems::utf8BOM << "l_german:\n";
	russian << commonItems::utf8BOM << "l_russian:\n";
	spanish << commonItems::utf8BOM << "l_spanish:\n";

	// title localization
	for (const auto& [unused, title] : CK3World.getTitles())
	{
		for (const auto& [key, loc] : title->localizations)
		{
			english << " " << key << ": \"" << loc.english << "\"\n";
			french << " " << key << ": \"" << loc.french << "\"\n";
			german << " " << key << ": \"" << loc.german << "\"\n";
			russian << " " << key << ": \"" << loc.russian << "\"\n";
			spanish << " " << key << ": \"" << loc.spanish << "\"\n";
		}
	}
	// character name localization
	std::set<std::string> uniqueKeys;
	for (const auto& [unused, character] : CK3World.getCharacters())
	{
		for (const auto& [key, loc] : character->localizations)
		{
			if (!uniqueKeys.contains(key))
			{
				english << " " << key << ": \"" << loc.english << "\"\n";
				french << " " << key << ": \"" << loc.french << "\"\n";
				german << " " << key << ": \"" << loc.german << "\"\n";
				russian << " " << key << ": \"" << loc.russian << "\"\n";
				spanish << " " << key << ": \"" << loc.spanish << "\"\n";

				uniqueKeys.insert(key);
			}
		}
	}
	english.close();
	french.close();
	german.close();
	russian.close();
	spanish.close();
}
