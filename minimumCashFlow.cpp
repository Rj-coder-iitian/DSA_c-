// C++ program to fin maximum cash flow among a set of persons
#include<bits/stdc++.h>
using namespace std;

// A utility function that returns index of minimum value in vector amount
int getMin(vector<int> amount)
{
    int n = amount.size();
	int minIndex = 0;
	for (int i=1; i<n; i++)
		if (amount[i] < amount[minIndex])
			minIndex = i;
	return minIndex;
}

// A utility function that returns index of maximum value in arr[]
int getMax(vector<int> amount)
{
    int n = amount.size();
	int maxIndex = 0;
	for (int i=1; i<n; i++)
		if (amount[i] > amount[maxIndex])
			maxIndex = i;
	return maxIndex;
}

void minCashFlowRec(vector<int> &amount, int n, vector<vector<int>> &graph)
{
	int receiver = getMax(amount), giver = getMin(amount);

	// If both amounts are 0, then all amounts are settled
	if (amount[receiver] == 0 && amount[giver] == 0)
		return;

	// Find the minimum of two amounts
	int minimum = min(-amount[giver], amount[receiver]);
	amount[receiver] -= minimum;
	amount[giver] += minimum;

	// minimum is the maximum amount to be paid
	graph[giver][receiver] = minimum;
	cout << "Person " << giver << " pays " << minimum << " to " << "Person " << receiver << endl;

	minCashFlowRec(amount, n, graph);
}

// Given a set of persons as graph[] where graph[i][j] indicates the amount that person i needs to pay person j, this function
// we will find and print the minimum cash flow to settle all debts.
void minCashFlow(vector<vector<int>> &graph, int n)
{
	// Create a vector amount , initialize all value in it as 0.
	vector<int> amount(n,0);

	// Calculate the net amount to be paid to person 'p', and stores it in amount[p]. The value of amount[p] can be
	// calculated by subtracting debts of 'p' from credits of 'p'
	for (int p=0; p<n; p++)
	    for (int i=0; i<n; i++)
		    amount[p] += (graph[i][p] - graph[p][i]);
    
    for (int p=0; p<n; p++)
	    for (int i=0; i<n; i++)
	        graph[p][i] = 0;
    
	minCashFlowRec(amount, n, graph);
	
	for (int p=0; p<n; p++){
	    for (int i=0; i<n; i++){
	        cout << graph[p][i] << " ";  
	    }
	    cout << endl;
    }
}

// Driver program to test above function
int main()
{
	// graph[i][j] indicates the amount that person i needs to pay person j
	int n;
	cin >> n;
	vector<vector<int>> graph(n,vector<int>(n,0));
	for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        cin >> graph[i][j];
	    }
	}
	minCashFlow(graph, n);
	return 0;
}
