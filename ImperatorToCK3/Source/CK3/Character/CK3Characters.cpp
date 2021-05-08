#include "CK3Characters.h"
#include <ranges>
#include <set>
#include <string>
#include <utility>
#include "CK3Character.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



CK3::Characters::Characters(const std::string& charactersPath) {
	registerKeys();
	for (const auto& fileName : commonItems::GetAllFilesInFolderRecursive(charactersPath)) {
		if (!fileName.ends_with(".txt"))
			continue;
		parseFile(fileName);
	}
	clearRegisteredKeywords();
}


void CK3::Characters::registerKeys() {
	registerRegex(commonItems::stringRegex, [this](const std::string& charID, std::istream& theStream) {
		std::shared_ptr<Character> newCharacter = characterFactory.getCharacter(theStream, charID);
		characters.emplace(newCharacter->ID, newCharacter);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreAndLogItem);
}


void CK3::Characters::erase(const std::string& id) {
	characters[id]->breakAllLinks();
	characters.erase(id);
}


void CK3::Characters::linkSpouses() {
	auto counterSpouse = 0;
	for (const auto& character : characters | std::views::values) {
		if (!character->getSpouses().empty()) {
			std::map<std::string, std::shared_ptr<Character>> newSpouses;
			for (const auto& spouseID : character->getSpouses() | std::views::keys) {
				if (const auto& characterItr = characters.find(spouseID); characterItr != characters.end()) {
					newSpouses.emplace(characterItr->first, characterItr->second);
					++counterSpouse;
				} else {
					Log(LogLevel::Warning) << "Spouse ID: " << spouseID << " has no definition!";
				}
			}
			for (const auto& spousePtr: newSpouses | std::views::values) {
				character->addSpouse(spousePtr);
			}
		}
	}
	Log(LogLevel::Info) << "<> " << counterSpouse << " spouses linked.";
}


void CK3::Characters::linkMothersAndFathers() {
	auto counterMother = 0;
	auto counterFather = 0;
	for (const auto& character : characters) {
		if (character.second->getMother().first != "0") {
			const auto& characterItr = characters.find(character.second->getMother().first);
			if (characterItr != characters.end()) {
				character.second->setMother(characterItr->second);
				characterItr->second->addChild(character.second);
				++counterMother;
			} else {
				Log(LogLevel::Warning) << "Mother ID: " << character.second->getMother().first << " has no definition!";
			}
		}

		if (character.second->getFather().first != "0") {
			const auto& characterItr = characters.find(character.second->getFather().first);
			if (characterItr != characters.end()) {
				character.second->setFather(characterItr->second);
				characterItr->second->addChild(character.second);
				++counterFather;
			} else {
				Log(LogLevel::Warning) << "Father ID: " << character.second->getFather().first << " has no definition!";
			}
		}
	}
	Log(LogLevel::Info) << "<> " << counterMother << " mothers and " << counterFather << " fathers linked.";
}
