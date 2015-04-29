#include<iostream>
#include <fstream>
#include<queue>
//implementation of genetic algorithm for 8 samples and given conditions
using namespace std;

char word[50];
char genO[8][50], tmp[8][50], cross_over[8][50],new_gen[8][50];
int l;
int fit_val[8], tfit_val[8];
ofstream myfile;


struct Node
{
	char p;
	int cost;
};

struct CompareNode
{
	bool operator()(Node& n1, Node& n2)
	{
		if (n1.cost > n2.cost)
			return true;
		return false;
	}
};

void compute_genO()
{
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			genO[i][j] = (rand() % 26) + 97;
		}
	}
}

void fitness(char gen[8][50])
{
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			fit_val[i] = fit_val[i] + ((word[j] - gen[i][j])*(word[j] - gen[i][j]));
		}
	}
}

void sampling()
{
	priority_queue<Node, vector<Node>, CompareNode> pqueue;
	Node n[8];
	for (int i = 0; i<8; i++)
	{
		n[i].p = i;
		n[i].cost = fit_val[i];
		pqueue.push(n[i]);
	}
	int i = 0;
	while (!pqueue.empty())
	{
		int s = pqueue.top().p;
		for (int j = 0; j<l; j++)
		{
			tmp[i][j] = genO[s][j];
		}
		pqueue.pop();
		i++;
	}

}



void crossover()
{
	for (int i = 0; i<4; i++)
	{
		int c = rand() % l;
		for (int j = 0; j<l; j++)
		{
			if (j>c)
			{
				int t = tmp[i][j];
				cross_over[i][j] = tmp[8 - (i + 1)][j];
				cross_over[i + 4][j] = t;
			}
			else
			{
				cross_over[i][j] = tmp[i][j];
				cross_over[i + 4][j] = tmp[i+4][j];
			}
		}
	}
}

void mutation()
{
	for (int i = 0; i<8; i++)
	{
		int m = (l / 2);
		int c = rand() % l;
		new_gen[i][m] = c+97;
		for (int j = 0; j<l; j++)
		{
			if (j==m)
			{
				new_gen[i][j] = c + 97;
			}
			else
			{
				new_gen[i][j]=cross_over[i][j];
			}
		}
	}
}

void show_genO()
{
	freopen("out.txt", "w", stdout);
	cout << "Gen 1:" << endl<<endl;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			cout << genO[i][j];
		}
		cout << "\n";
	}

	cout << endl << "Sampling:" << endl<<endl;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			cout << tmp[i][j];
		}
		cout << "\n";
	}

	cout << endl << "CrossOver:" << endl<<endl;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			cout << cross_over[i][j];
		}
		cout << "\n";
	}

	cout << endl << "Mutatated New Gen:" << endl<<endl;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<l; j++)
		{
			cout << new_gen[i][j];
		}
		cout << "\n";
	}
	myfile.close();
}

int main()
{

	cout << "Enter your input lenght: " << endl;
	cin >> l;
	cout << "Enter your word: ";
	for (int i = 0; i<l; i++)
	{
		cin >> word[i];
	}
	
	compute_genO();
	fitness(genO);
	sampling();
	crossover();
	mutation();
	show_genO();
	return 0;
}