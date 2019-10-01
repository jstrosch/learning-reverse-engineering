#include <stdio.h>
#include <iostream>

using namespace std;

class Ex2
{
	int var1;

public:
		virtual int get_sum(int x, int y){
			return x+y;
		}

		virtual void reset_values(){
			var1 = 0;
		}
};


class Ex3: public Ex2
{
	int var1;

public:

	virtual void reset_values() {
		var1 = 99;
	}

};

int main(int argc, char ** argv, char **envp) {

	Ex3 *e = new Ex3();
	delete(e);
}
