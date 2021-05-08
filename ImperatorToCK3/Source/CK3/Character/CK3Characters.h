#ifndef CK3_CHARACTERS_H
#define CK3_CHARACTERS_H



#include "CK3CharacterFactory.h"
#include "Parser.h"



namespace CK3 {

class Character;
class Characters: commonItems::parser {
  public:
	Characters() = default;
	explicit Characters(const std::string& charactersPath);

	[[nodiscard]] const auto& getCharacters() const { return characters; }

	void addCharacter(const std::shared_ptr<Character>& characterPtr) { characters.emplace(characterPtr->ID, characterPtr); }
	void erase(const std::string& id);
	void linkSpouses();
	void linkMothersAndFathers();

  private:
	void registerKeys();

	Character::Factory characterFactory;

	std::unordered_map<std::string, std::shared_ptr<Character>> characters;
};	// class Characters

}  // namespace CK3



#endif	// CK3_CHARACTERS_H
