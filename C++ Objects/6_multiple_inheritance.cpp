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

class Ex4
{
	public:		
		virtual void virtual_func2() {
			cout << "Ex4->virtual_func2" << endl;
		}
};

class Ex5: public Ex2, public Ex4
{
	private:
		int var1;
		int var2;

	public:
		Ex5() {
			var1 = 1;
			var2 = 2;
		}
		virtual void virtual_func3() {
			cout << "Ex5->virtual_func3" << endl;
		}
		virtual void virtual_func2(){
			cout << "Ex5->virtual_func2" << endl;
		}
};

int main(int argc, char ** argv, char **envp) {
	
	Ex5 *e = new Ex5();
	e->virtual_func1();
	e->virtual_func2();
	e->virtual_func3();
	delete(e);
}