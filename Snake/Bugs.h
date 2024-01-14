#pragma once
#include <list>

struct Bug {
	int x;
	int y;
};

class Bugs{
private:
	std::list<Bug> bugsList;
public:
	void addBug(int xLoc, int yLoc) { bugsList.push_back(Bug{ xLoc, yLoc }); }
	
	bool removeBug(int xLoc, int yLoc) {
		for (auto it = bugsList.begin(); it != bugsList.end(); it++) {
			if (it->x == xLoc && it->y == yLoc) {
				bugsList.erase(it);
				return true;
			}
		}
		return false;
	}

	int size() const {
		return bugsList.size();
	}

	bool spotTaken(int xLoc, int yLoc) {
		for (auto it = bugsList.begin(); it != bugsList.end(); it++) {
			if (it->x == xLoc && it->y == yLoc) {
				return true;
			}
		}
		return false;
	}

	std::list<Bug>& getBugs() {
		return bugsList;
	}
};

