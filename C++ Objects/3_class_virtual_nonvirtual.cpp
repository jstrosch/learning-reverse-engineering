#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Ex3
{
	int var1;

public:
		virtual int sum(int x, int y){
			return x+y;
		}

		virtual void reset_values(){
			var1 = 0;
		}

		void printHello() {
			cout << "hello world" << endl;
		}
};

int main(int argc, char ** argv, char **envp) {
	
	Ex3 *e = new Ex3();
	e->sum(1,2);
	e->reset_values();
	e->printHello();
	delete(e);
}