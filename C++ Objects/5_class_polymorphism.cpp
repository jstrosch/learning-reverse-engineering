#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Ex2
{
	private:
		int var1;

	public:
		virtual int sum(int x, int y){
			return x+y;
		}

		virtual void virtual_func1(){
			cout << "Ex2->virtual_func1" << endl;
		}
};


class Ex3: public Ex2
{
	private:
		int var1;

	public:
		int subtract(int x, int y){
			return x - y;
		}

		void virtual_func1(){
			cout << "Ex3->virtual_func1" << endl;
		}
};

int main(int argc, char ** argv, char **envp) {

	Ex3 *e = new Ex3();
	e->virtual_func1();
	delete(e);
}
