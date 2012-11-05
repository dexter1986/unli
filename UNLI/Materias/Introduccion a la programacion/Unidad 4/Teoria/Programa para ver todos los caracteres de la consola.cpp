#include <constream>
#include <iomanip>
#include<cstdlib>

using namespace conio;
using namespace std;

int main() {
	cout<<clrscr;
	for(int n=128;n<256;++n)
	{
		cout<<n<<":"<<(char)n<<"   ";
	}
	cout<<endl;
	system("PAUSE");
    return 0;
}

