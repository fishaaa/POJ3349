#include <iostream>
//using namespace std;
using std::cin;
using std::cout;
const int primer = 14997;

class HashTable
{
public:
	int snow_t[6];
	HashTable *next;
	HashTable()
	{
		next = 0;
	}
};
HashTable *hash [primer+1];
bool compare(int a[6] , int b[6])
{
	for(int i = 0; i < 6; ++i){
		bool flag1 = true;
		for(int j = 0; j < 6; ++j){
			if(a[j] != b[(i+j)%6]){
				flag1 = false;
				break;
			}
		}
		if(flag1)
			return true;
	}
	for(int i = 0; i < 6; ++i){
		bool flag = true;
		for(int j = 0; j < 6; ++j){
			if(a[j] != b[(5-i-j+6) % 6] ){
				flag = false;
				break;
			}
		}
		if(flag)
			return true;
	}
	return false;
}
int main()
{	memset(&hash, 0, sizeof(hash));//对hash表实现初始化
	int n = 0;
	cin>>n;
	while(n--){
		//int snow[6];
		int find = 0;
		int key=0;
		HashTable *temp = new HashTable;
		for(int j = 0; j < 6; ++j){
			scanf("%d",&temp->snow_t[j]); 
			//cin >> temp->snow_t[j];
			key =(key+temp->snow_t[j])% primer;
		}
		if(!hash[key]){
			hash[key] = temp;
			continue;
		}
		else{
			HashTable *temp1 = hash[key];
			while(temp1 -> next){	//查找hash表的下一项，直到hash->next!=0
				if(compare(temp1 -> snow_t, temp -> snow_t)){
					find = 1;
					break;
				}
				else temp1 = hash[key] -> next;	
			}
			if(compare(temp1 -> snow_t,temp -> snow_t))
					find = 1;
			if(find == 1){
				cout << "Twin snowflakes found.";
				break;
			}	
			temp1 -> next = new HashTable;
			temp1 -> next =temp;
		}
		if(find == 0)
			cout<<"No two snowflakes are alike.";
	}	
	system("PAUSE");
	return 0;
}
