#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#define PRIMEMAX 65536

vector<int> all_factor_vector;
vector<int> n_vector, k_vector;

int non_prime[PRIMEMAX+2]={0};
vector<int> prime_vector;

void generate_prime ();
void find_all_factor (int factor, int factor_count, vector<int> factor_list, vector<int> dimension_list);
int factoring (int initial_height, int worker_cat_number);

int main() {
	int i;
	
	generate_prime ();
	
	int n, k, tmp;
	int initial_height, worker_cat_number;
	int non_worker_cat_number, total_height;
	while (scanf ("%d%d", &initial_height, &worker_cat_number) != EOF) {
		if (initial_height == 0 && worker_cat_number == 0)
			break;
		
		n_vector.clear();
		k_vector.clear();
		all_factor_vector.clear();
		
		if (worker_cat_number != 1)
			n = factoring(initial_height, worker_cat_number);
		else 
			n = 1;
		
		if (n == 1) {
			tmp = initial_height;
			non_worker_cat_number = 0;
			while (tmp%2 == 0) {
				tmp = tmp/2;
				non_worker_cat_number++;
			}
		} 
		else 
			non_worker_cat_number = (worker_cat_number-1)/ (n-1);
		total_height = initial_height*(n+1) - worker_cat_number*n;
		
		printf ("%d %d\n", non_worker_cat_number, total_height);
	}

	return 0;
}

/* 預先建立質數表 */
void generate_prime () {
	int i, j;
	
	prime_vector.push_back(2);
	for (i=3; i<=PRIMEMAX; i+=2) {
		if (!non_prime[i]) {
			for (j=i+i; j<=PRIMEMAX; j+=i) {
				non_prime[j]=1;
			}
			prime_vector.push_back(i);
		}
	}
	
	return ;
}

/* 找出一堆數的最大公因數 */
int gcd_all (vector<int> dimension_list) {
	int i;
	
	int m, n, r;
	m = dimension_list[0];
	for (i=1; i<dimension_list.size(); i++) {
		n = dimension_list[i];
		while (n != 0) {
			r = m%n;
			m = n;
			n = r;
		}
	}
	
	return m;
}

/* 找出所有的因數 */
void find_all_factor (int factor, int factor_count, vector<int> factor_list, vector<int> dimension_list) {
	int i;
	
	if (factor_count == factor_list.size()) {
		all_factor_vector.push_back(factor);
		return ;
	}
		
	int tmp=1.0;
	for (i=0; i<=dimension_list[factor_count]; i++) {
		find_all_factor (factor*tmp, factor_count+1, factor_list, dimension_list);
		tmp *= factor_list[factor_count];
	}
	return ;
}

int factoring (int initial_height, int worker_cat_number) {
	int i, j, l;
	
	vector<int> factor_list, dimension_list;
	int factor_count=0;
	
	/* 質因數分解 */
	i = 0;
	while (worker_cat_number != 1) {
		if (worker_cat_number%prime_vector[i] == 0) {
			factor_list.push_back(prime_vector[i]);
			dimension_list.push_back(0);
			do {
				dimension_list[factor_count]++;
				worker_cat_number = worker_cat_number/prime_vector[i]; 
			} while (worker_cat_number%prime_vector[i] == 0);
			factor_count++;
		}
		i++;
	}
	int gcd_m = gcd_all (dimension_list);
	
	vector<int> factor_2_list, dimension_2_list;
	int factor_2_count=0;
	
	/* 對維度的最大公因數進行質因數分解 */
	i = 0;
	while (gcd_m != 1) {
		if (gcd_m%prime_vector[i] == 0) {
			factor_2_list.push_back(prime_vector[i]);
			dimension_2_list.push_back(0);
			do {
				dimension_2_list[factor_2_count]++;
				gcd_m = gcd_m/prime_vector[i]; 
			} while (gcd_m%prime_vector[i] == 0);
			factor_2_count++;
		}
		i++;
	}

	find_all_factor (1, 0, factor_2_list, dimension_2_list);

	sort (all_factor_vector.rbegin(), all_factor_vector.rend());
	
	/* 找出可能的 n */
	int k, n, tmp;
	for (i=0; i<all_factor_vector.size(); i++) {
		k = all_factor_vector[i];
		n = 1;
		for (j=0; j<factor_list.size(); j++) {
			tmp = factor_list[j];
			for (l=1; l<dimension_list[j]/k; l++) {
				tmp = tmp*factor_list[j];
			}
			n = n*tmp;
		}
		
		tmp = 1;
		for (j=0; j<k; j++) {
			tmp *= (n+1);
		}
		if (tmp == initial_height)
			return n;
	}
	
	return 0;
}