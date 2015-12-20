#include <iostream>
//using namespace std;
using std::cin;
using std::cout;
const int primer=999983;

class HashTable
{
public:
	int snow_t[6];
	HashTable *next;
	HashTable()
	{
		next=0;
	}
};
HashTable *hash[primer+1];

bool compare( int a[6],int b[6] )
{
	int k=0;int num=0;
	while( k<6 ){						//首先顺时针比较，L为i+k超过5后，回到从数组0开始的计量数
		for( int i=0;i<6;++i ){
			int l=k+i-6;
			if( i+k<=5 ){
				if( a[i]==b[i+k] )
					++num;
				else break;
			}
			else{
				if( a[i]==b[l] )
					++num;
				else break;
			}
		}
		++k;
	}
	if( num==6 )
		return true;
	num=0;k=5;
	while( k>=0 ){
		for( int i=0;i<6;++i ){
			int l=k-i+6;
			if( k-i>=0 ){
				if( a[i]==b[k-i] )
					++num;
				else break;
			}
			else{
				if( a[i]==b[l] )
					++num;
				else break;
			}
		}
		--k;
	}
	if( num==6 )
		return true;
	else
		return false;
}
int main()
{
	//HashTable *hash[primer+1];
	
	int n=0;
	while( cin>>n ){
		memset( &hash,0,sizeof( hash ) );//对hash表实现初始化
		int (*snow )[6]=new int [n][6];//申请二维数组， 实现动态输入
		int *sum=new int [n]();//计算叶的总和，以便求解key值
		for( int i=0;i<n;++i ){
			for( int j=0;j<6;++j ){
				cin>>snow[i][j];
				sum[i]+=snow[i][j];
			}
		}
		for( int i=0;i<n;++i){	//对hash表插入数据
			int key=sum[i]%primer;
			if( !hash[key] ){
				HashTable *temp=new HashTable;
				for( int j=0;j<6;++j ){
					temp->snow_t[j]=snow[i][j];
				}
				hash[key]=temp;
			}
			else{
				HashTable *temp=hash[key];
				while( temp->next )	//查找hash表的下一项，直到hash->next!=0
					temp=hash[key]->next;
				temp->next=new HashTable;
				for( int j=0;j<6;++j ){
					temp->next->snow_t[j]=snow[i][j];
				}
			}
		}
		int find=0;//控制标志位，表示是否找到相同的雪花
		for( int key=0;key<primer;++key ){//对hash表进行查找，并实现对其叶子数顺序的比较
			if( find==1 )
				break;
			if( hash[key] ){
				HashTable *temp=hash[key];
				while( temp->next ){
					if( compare( temp->snow_t,temp->next->snow_t ) ){
						find=1;
						cout<<"Twin snowflakes found.";
						break;
					}
					else temp=temp->next;
				}
			}
			else	continue;	
		}
		if( find==0 )
			cout<<"No two snowflakes are alike.";
	}
	system( "PAUSE" );
	return 0;
}
