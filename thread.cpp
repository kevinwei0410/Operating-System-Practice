#include <iostream>
#include <thread>
#include <vector>
#pragma comment(lib, "Winmm.lib")
#include <windows.h>
#include <mutex>
#include <exception>
using namespace std;
void part_sum(long long int, long long int);
void part_sum1_2(long long int, long long int);
void part_sum2(long long int, long long int);

long long int sum_version1 = 0;
long long int sum_version1_2 = 0;
long long int sum_version2 = 0;
/*truct Sum {
	int sum = 0, temp, start, end;
	mutex mu;
	void locking_sum() {
		mu.lock();
		try 
		{
			temp = part_sum(start, end);
			sum += temp;
			cout << "sum:" << temp << endl;
		}
		catch (exception & cException) 
		{
			mu.unlock();
			throw cException;
		}
		mu.unlock();
	}
	int part_sum(int start, int end)
	{
		int sum = 0;
		for (int i = start; i < end; i++)
			sum += i;
		return sum;
	}
};
void func(Sum& s)
{
	s.locking_sum();
}*/
int main()
{
	//Version 1---------------------------------------------------------------------------------------
	//multithread計算，存在個別變數後，相加
	long long int x, n;
	cout << "輸入thread:";
	cin >> x;
	cout << "輸入n:";
	cin >> n;
	vector <thread> threads;
	DWORD start_time, end_time, start_time2, end_time2;
	start_time = timeGetTime();
	for (long long int i = 1; i <= x; i++)
	{
		threads.push_back(thread(part_sum, (i - 1) * (n / x) + 1, i * (n / x)));
		cout << "thread" << i << "開始" << endl;
	}
	for (long long int i = 0; i < x; i++)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
			cout << "thread" << i + 1 << "結束" << endl;
		}
	}
	cout << "multithread計算，最後結果:" << sum_version1 << endl;
	end_time = timeGetTime();
	cout << "multithread計算，使用時間:" << end_time - start_time << endl;
	
	//傳統single thread
	
	start_time2 = timeGetTime();
	thread single(part_sum1_2, 1, n);
	if (single.joinable())
		single.join();
	end_time2 = timeGetTime();
	cout << "傳統single thread計算，最終結果:" << sum_version1_2 << endl;
	cout << "傳統single thread計算，使用時間:" << end_time2 - start_time2 << endl;
	
	double radio = ((double)end_time2 - (double)start_time2) / ((double)end_time - (double)start_time);
	cout << "single thread與multithread時間比:" << radio << endl;
 	
	cout << "----------------------------------------------------------------------------------------" << endl;
	//Version 2 ---------------------------------------------------------------------------------------
	//multithread計算，存在一個thread共用變數
	
	vector <thread> threads2;
	//Sum s;
	for (long long int i = 1; i <= x; i++)
	{
		//s.start = (i - 1) * (n / x) + 1;
		//s.end = i * (n / x);
		//threads2.push_back(thread(func, ref(s)));
		threads2.push_back(thread(part_sum2, (i - 1) * (n / x) + 1, i * (n / x)));
	}
	for (long long int i = 0; i < x; i++)
	{
		if (threads2[i].joinable())
		{
			threads2[i].join();
		}
	}
	cout << "version2 - 最後總和:" <<sum_version2 << endl;
	


}
void part_sum(long long int start, long long int end)
{
	for (long long int i = start; i <= end; i++)
		sum_version1 += i;
}
void part_sum1_2(long long int start, long long int end)
{
	for (long long int i = start; i <= end; i++)
		sum_version1_2 += i;
}
void part_sum2(long long int start, long long int end)
{
	for (long long int i = start; i <= end; i++)
		sum_version2 += i;
}


/*
這次的作業讓我受益良多，學到如何使用thread 的來進行平行運算。使計算上可以更加快速，未來在計算許多複雜的東西時可以更加方便
。未來的趨勢是利用平行方式進行計算，所以multithread 也能更加有利用的地方。希望下次可以有類似的程式練習可以讓我做練習。
另外這次的練習也讓我了解到如何使用時間的函式庫，這在外來也會有使用到的地方。
*/