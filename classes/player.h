#if !defined(__PLAYER_H)
#define __PLAYER_H
#include <string>

class Player {
private:
	std::string username;
public:
	void setName(std::string);
	std::string getName();
};

#endif
