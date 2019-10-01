#include <stdio.h>
#include <iostream>

using namespace std;

class Ex2
{
	int var1;

public:
		Ex2(){
			var1 = 222;
		}
		virtual int get_sum(int x, int y){
			return x+y;
		}

		virtual void reset_values(){
			var1 = 0;
		}
};

class Ex4
{
	int var1;
	int var2;

public:
	Ex4() {
		var1 = 333;
		var2 = 3332;
	}
	virtual void func1() {
		printf("Ex4 func1");
	}

	virtual void func2() {
		printf("Ex4 func2");
	}
};

class Ex5: public Ex2, public Ex4
{
	int var1;

public:
	Ex5() {
		var1 = 555;
	}
	void func1() {
		printf("EX5 func1");
	}
	virtual void v_ex5() {
		printf("EX5 v_ex5");
	}

	void get_values();
};

int main(int argc, char ** argv, char **envp) {
	
	Ex5 *e = new Ex5();

	e->v_ex5();

	e->func2();

	delete(e);
}