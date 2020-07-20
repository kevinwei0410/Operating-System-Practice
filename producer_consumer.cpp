#include<stdio.h>
#include <thread>
#include <iostream>
#include <queue>
#include <mutex>

std::mutex mx;
std::condition_variable cv;
std::queue<int> q;

bool finished = false;

void producer(int n) {
	for (int i = 0; i < n; ++i) {
		{
			std::lock_guard<std::mutex> lk(mx);
			q.push(i);
			std::cout << "pushing " << i << std::endl;
		}
		cv.notify_all();
	}
	{
		std::lock_guard<std::mutex> lk(mx);
		finished = true;
	}
	cv.notify_all();
}

void consumer() {
	while (true) {
		std::unique_lock<std::mutex> lk(mx);
		cv.wait(lk, [] { return finished || !q.empty(); });
		while (!q.empty()) {
			std::cout << "consuming " << q.front() << std::endl;
			q.pop();
		}
		if (finished) break;
	}
}

int main() {
	std::thread t1(producer, 1);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	std::cout << "finished!" << std::endl;
}
/*
int mutex = 1, full = 0, empty = 3, x = 0;*/
/*
int main()
{
	int n;
	void producer();
	void consumer();
	int wait(int);
	int signal(int);
	printf("\n1.Producer\n2.Consumer\n3.Exit");
	while (1)
	{
		printf("\nEnter your choice:");
		std::cin >> n;
		switch (n)
		{
		case 1:	if ((mutex == 1) && (empty != 0))
			producer();
			  else
			printf("Buffer is full!!");
			break;
		case 2:	if ((mutex == 1) && (full != 0))
			consumer();
			  else
			printf("Buffer is empty!!");
			break;
		case 3:
			exit(0);
			break;
		}
	}

	return 0;
}

int wait(int s)
{
	return (--s);
}

int signal(int s)
{
	return(++s);
}

void producer()
{
	mutex = wait(mutex);
	full = signal(full);
	empty = wait(empty);
	x++;
	printf("\nProducer produces the item %d", x);
	mutex = signal(mutex);
}

void consumer()
{
	mutex = wait(mutex);
	full = wait(full);
	empty = signal(empty);
	printf("\nConsumer consumes item %d", x);
	x--;
	mutex = signal(mutex);
}*/