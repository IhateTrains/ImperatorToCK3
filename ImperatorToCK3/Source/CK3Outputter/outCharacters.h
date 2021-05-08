#ifndef CK3_OUT_CHARACTERS_H
#define CK3_OUT_CHARACTERS_H



#include <memory>
#include <string>
#include <unordered_map>


namespace CK3 {

class Character;
void outputCharacters(const std::string& outputModName, const std::unordered_map<std::string, std::shared_ptr<Character>>& characters);

}



#endif // CK3_OUT_CHARACTERS_H