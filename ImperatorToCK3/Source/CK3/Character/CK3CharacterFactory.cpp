#include "CK3CharacterFactory.h"
#include "ParserHelpers.h"
#include "CommonRegexes.h"



CK3::Character::Factory::Factory() {
	registerKeyword("name", [this](std::istream& theStream) {
		character->name = commonItems::getString(theStream);
	});
	registerKeyword("female", [this](std::istream& theStream) {
		character->female = commonItems::getString(theStream) == "yes";
	});
	registerKeyword("dynasty", [this](std::istream& theStream) {
		character->dynastyID = commonItems::getString(theStream);
	});
	registerKeyword("martial", [this](std::istream& theStream) {
		character->martial = commonItems::stringToInteger<unsigned>(commonItems::getString(theStream));
	});
	registerKeyword("diplomacy", [this](std::istream& theStream) {
		character->diplomacy = commonItems::stringToInteger<unsigned>(commonItems::getString(theStream));
	});
	registerKeyword("intrigue", [this](std::istream& theStream) {
		character->intrigue = commonItems::stringToInteger<unsigned>(commonItems::getString(theStream));
	});
	registerKeyword("stewardship", [this](std::istream& theStream) {
		character->stewardship = commonItems::stringToInteger<unsigned>(commonItems::getString(theStream));
	});
	registerKeyword("culture", [this](std::istream& theStream) {
		character->culture = commonItems::getString(theStream);
	});
	registerKeyword("religion", [this](std::istream& theStream) {
		character->religion = commonItems::getString(theStream);
	});
	registerKeyword("trait", [this](std::istream& theStream) {
		character->traits.emplace(commonItems::getString(theStream));
	});
	registerKeyword("dna", [this](std::istream& theStream) {
		character->dnaKey = commonItems::getString(theStream);
	});
	registerKeyword("mother", [this](std::istream& theStream) {
		character->mother = std::pair(commonItems::getString(theStream), nullptr);
	});
	registerKeyword("father", [this](std::istream& theStream) {
		character->father = std::pair(commonItems::getString(theStream), nullptr);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreAndLogItem);
}


std::unique_ptr<CK3::Character> CK3::Character::Factory::getCharacter(std::istream& theStream, const std::string& idString) {
	character = std::make_unique<Character>();
	character->ID = idString;

	parseStream(theStream);

	return std::move(character);
}