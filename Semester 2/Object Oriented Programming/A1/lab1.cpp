

#include <iostream>
using namespace std;
int rel_prime (int nr1,int nr2)
{
	int d;
	for (d = 2; d <= nr2; d++)
		if (nr2 % d == 0)
			if (nr1 % d == 0)
				return 0;
	return 1;
}

void longest_max_sum_seq(int v[], int n, int new_seq[], int &m)
{

	int i, current_sum = v[0], max = v[0], start = 0, end = 0, temp_start = 0, current_len=1, max_len=1;
	for (i = 1; i < n; i++)
	{
		if (v[i] > v[i] + current_sum)
		{
			current_sum = v[i];
			temp_start = i;
			current_len = 1;
		}
		else
		{
			current_sum += v[i];
			current_len++;
		}
			

		if (current_sum > max)
		{
			max = current_sum;
			start = temp_start;
			end = i;
			max_len = current_len;
		}
		else
			if(current_sum == max && current_len > max_len)
			{
				start = temp_start;
				end = i;
				max_len = current_len;
			}

	}

	m = 0;
	for (i = start; i <= end; i++)
	{
		new_seq[m] = v[i];
		m++;
	}

		

}
void print_menu()
{
	cout << endl;
	cout << "Menu"<< endl;
	cout << "1.Determine all the numbers smaller than a given natural and non-null number n and that are relatively prime to n."<<endl;
	cout << "2.Given a vector of numbers, find the longest contiguous subsequence with the maximum sum."<<endl;
	cout << "3.Exit" << endl;
}
	
int main()
{
	int n, ok = 1, i, v[100], choice;
	while (ok == 1)
	{
		print_menu();
		cout << "enter choice: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "enter n: ";
			cin >> n;
			for (i = 1; i < n; i++)
				if (rel_prime(n, i) == 1)
					cout << i << " ";
			cout << endl;

		}
		else
			if (choice == 2)
			{
				cout << "enter length: ";
				cin >> n;
				cout << "enter " << n << " numbers: ";
				for (i = 0; i < n; i++)
					cin >> v[i];
				int new_seq[100], m;
				longest_max_sum_seq(v, n, new_seq, m);
				for (i = 0; i < m; i++)
					cout << new_seq[i] << " ";
				cout << endl;


			}
			else if (choice == 3)
				ok = 0;
			else
				cout << "Invalid input!";


	}
	

	return 0;
}


