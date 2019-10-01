#include <stdio.h>
#include <iostream>

using namespace std;

class Ex1
{
	int var1;
	int var2;
	int var3;

public:
	Ex1() {
		var1 = 1;
		cout << "In Constructor" << endl;
	}
	int get_var1() {
		return var1;
	}
};

int main(int argc, char ** argv, char **envp) {
	
	Ex1 *e = new Ex1();
	printf("%d\n",e->get_var1());
	delete(e);

}