#include <iostream>
#include <list>

using namespace std;
typedef int hito;

list<hito> que;
list<int> ans;
int in, tmp;

inline void findAnswer()
{
	if (que.empty())return;
	int tmp = que.front();
	ans.push_back(tmp);
	que.pop_front();
	auto i = que.begin();
	auto lim = que.end();
	int flag = 0;
	for (; i != lim; ++i)
	{
		++flag;
		if (flag == tmp)
		{
			i = que.erase(i);
			flag = 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 2; i < 50050; ++i)
		que.push_back(i);
	while (ans.size() < 3050)
	{
		findAnswer();
	}
	auto it = ans.begin();
	auto lim = ans.end();
	while (cin >> in)
	{
		it = ans.begin();
		for (int c = 0; c < in; ++c)
		{
			++it;
		}
		ans.push_back(*it);
	}
	it = ans.begin();
	lim--;
	for (; it != lim; ++it)
	{
		cout << *it << endl;
	}
	cout << *lim;
	return 0;
}