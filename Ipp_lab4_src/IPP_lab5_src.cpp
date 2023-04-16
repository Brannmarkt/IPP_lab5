#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>
#include <functional>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using namespace chrono;

using test_vector_func = void(vector<int> vector);

milliseconds test_time(function<test_vector_func> func, vector<int> vector)
{
	auto start_time = steady_clock::now();
	func(vector);
	auto end_time = steady_clock::now();

	return duration_cast<milliseconds>(end_time - start_time);
}

int factorial(int x)
{
	long factorial = 1;

	for (int i = 1; i <= x; ++i)
	{
		factorial *= i;
	}
	return factorial;
}

void count_factorials(vector<int> vector)
{
	for (int i = 0; i < vector.size(); i++) 
	{
		int fact = factorial(vector[i]);
	}
}

void count_factorials_openmp(vector<int> vector)
{
#pragma omp parallel for
	for (int i = 0; i < vector.size(); i++) 
	{
		int fact = factorial(vector[i]);
	}
}

void find_min(vector<int> vector)
{
	int minElement = *min_element(vector.begin(), vector.end()), number_of_min = 0;
	cout << "Minimum element = " << minElement << endl;
	for (int i = 0; i <= vector.size(); i++)
	{
		if (vector[i] == minElement)
		{
			number_of_min = i;
			break;
		}
	}
	cout << "Number of min element: " << number_of_min << endl;
}

void find_min_openmp(vector<int> vector)
{
	int minElement = *min_element(vector.begin(), vector.end()), number_of_min = 0;
	cout << "Minimum element = " << minElement << endl;
	for (int i = 0; i <= vector.size(); i++)
	{
		if (vector[i] == minElement)
		{
			number_of_min = i;
			break;
		}
	}
	cout << "Number of min element: " << number_of_min << endl;
}

void find_max(vector<int> vector)
{
	int maxElement = *max_element(vector.begin(), vector.end()), number_of_max = 0;
	cout << "\nMaximum element = " << maxElement << endl;
	for (int i = 0; i <= vector.size(); i++)
	{
		if (vector[i] == maxElement)
		{
			number_of_max = i;
			break;
		}
	}
	cout << "Number of max element: " << number_of_max << endl;
}

void find_max_openmp(vector<int> vector)
{
	int maxElement = *max_element(vector.begin(), vector.end()), number_of_max = 0;
	cout << "\nMaximum element = " << maxElement << endl;
	for (int i = 0; i <= vector.size(); i++)
	{
		if (vector[i] == maxElement)
		{
			number_of_max = i;
			break;
		}
	}
	cout << "Number of max element: " << number_of_max << endl;
}

int main()
{
	// ------ generate vector ------
	int size = 50000;
	vector<int> vector(size);
	random_device rd;
	mt19937 gen(rd());
	for (int i = 0; i < size; i++) 
	{
		vector[i] = i + 1;
	}
	shuffle(vector.begin(), vector.end(), gen);
	
	// ------ count time ------
	milliseconds default_time, openmp_time, default_time_min, openmp_time_min, default_time_max, openmp_time_max;

	default_time = test_time(count_factorials, vector);
	openmp_time = test_time(count_factorials_openmp, vector);

	cout << "\n------- Count factorials -------\n";
	cout << "Default time = " << default_time.count() << "ms\n";
	cout << "OpenMP time = " << openmp_time.count() << "ms\n";
	cout << "Default - OpenMP: " << default_time.count() - openmp_time.count() << "ms\n";
	cout << "Default / OpenMP: " << (double)default_time.count() / openmp_time.count();
	cout << "\n\n";
	
	// ------ max and min element ------
	cout << "\n------- Find max/min element by default -------\n";
	default_time_min = test_time(find_min, vector);
	default_time_max = test_time(find_max, vector);
	cout << "\nDefault time (finding min) = " << default_time_min.count() << "ms\n";
	cout << "Default time (finding max) = " << default_time_max.count() << "ms\n";
	cout << "\n\n";

	cout << "------- Find max/min element with OpenMP -------\n";
	openmp_time_min = test_time(find_min_openmp, vector);
	openmp_time_max = test_time(find_max_openmp, vector);
	cout << "\nOpenMP time (finding min) = " << openmp_time_min.count() << "ms\n";
	cout << "OpenMP time (finding max) = " << openmp_time_max.count() << "ms\n";
}
