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

		void printHello() {
			printf("%s\n","Hello");
		}
};

int main(int argc, char ** argv, char **envp) {
	
	Ex2 *e = new Ex2();
	e->get_sum(1,2);
	e->reset_values();
	e->printHello();
	delete(e);
}