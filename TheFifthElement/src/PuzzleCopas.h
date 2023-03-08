#pragma once
#include <vector>
class PuzzleCopas{
private:
	vector<int> rellenas;
	bool terminado = false;
public:
	PuzzleCopas() {
	
	}
	void add(int a) {
		if (!terminado) {
			if (rellenas.size() == 0) {
				rellenas.push_back(a);
			}
			else if (rellenas[rellenas.size()-1] == a-1) {
				//es la siguiente copa
				rellenas.push_back(a);
				if (rellenas.size() == 3) terminado = true;
			}
			else {
				rellenas.clear();
				

			}
		}
	
	}
	virtual ~PuzzleCopas() {

	}

};