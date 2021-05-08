#ifndef CK3_CHARACTER_FACTORY_H
#define CK3_CHARACTER_FACTORY_H



#include "Parser.h"
#include "CK3Character.h"
#include <memory>



namespace CK3 {

class Character::Factory: commonItems::parser {
  public:
	explicit Factory();
	std::unique_ptr<Character> getCharacter(std::istream& theStream, const std::string& idString);

  private:
	std::unique_ptr<Character> character;
};

} // namespace Imperator



#endif	// CK3_CHARACTER_FACTORY_H