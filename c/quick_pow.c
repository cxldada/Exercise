#include <stdio.h>

#define modnum 999999997

long mypow(long a,long b) {
	a %= modnum;
	long res = 1;
	for(int i = 0;i < b; ++i) {
		res *= a;
		res %= modnum;
	}
	return res;
}

long superpow(long a,int *arr,int size) {
	if(size == 0)
		return 1;

	long para1,para2,k;
	k = arr[size - 1];
	para1 = mypow(a,k);
	para2 = mypow(superpow(a,arr,size-1),10);

	return (para1 * para2) % modnum;
}

int main(int args,char *argv[]) {
	int base,size,i;
	int arr[20];
	long ans;
	printf("基数: ");
	scanf("%d",&base);

	printf("指数:");
	size = 0;
	scanf("%d",&i);
	while(size < 20 && i >=0 && i < 10) {
		arr[size++] = i;
		scanf("%d",&i);
	}

	ans = superpow(base,arr,size);
	printf("res = %d",ans);

	return 0;
}
