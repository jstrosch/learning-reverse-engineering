#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Ex1
{
	int var1;

public:
	int var2 = 2;
	int var3 = 3;

	Ex1() {
		var1 = 1;
		cout << "In Constructor" << endl;
	}
	int get_var1() {
		return var1;
	}
};

int main(int argc, char ** argv, char **envp) {
	
	int a = 0;
	Ex1 *e = new Ex1();
	a = e->get_var1();
	e->var2 = 99;
	e->var3 = 98;
	delete(e);
}