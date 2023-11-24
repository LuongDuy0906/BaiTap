#include <iostream>

using namespace std;

class Cong{
	public:
		int cong(int a, int b){
			return a + b;
	}
};

int main(){
	int a, b;
	cin >> a >> b;
	Cong plus;
	int sum = plus.cong(a, b);
	cout << sum;
	return 0;
}
