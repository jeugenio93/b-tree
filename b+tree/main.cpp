#include "b+tree.h"

int main()
{

	int arr[4] = { 1,2,3,4 };
	std::cout << arr[(4 / 2)-1] << std::endl;
	BPTree* myTree = new BPTree(16);
	system("pause");
	return 0;
}