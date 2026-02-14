#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>
#include <map>
#include <iomanip>

using namespace std;

// Random number generator
random_device rd;
mt19937 gen(rd());

/**
 * 1. Standard Prefix Sum Approach
 * Good for: Static weights, few queries.
 * Complexity: O(N) setup, O(log N) query.
 */
class WeightedRandomPrefix {
    vector<double> prefix_sums;
    double total_weight;

public:
    WeightedRandomPrefix(const vector<double>& weights) {
        double sum = 0;
        for (double w : weights) {
            sum += w;
            prefix_sums.push_back(sum);
        }
        total_weight = sum;
    }

    int pickIndex() {
        uniform_real_distribution<> dis(0, total_weight);
        double target = dis(gen);
        
        // Binary search (std::upper_bound returns first element > value)
        auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), target);
        return distance(prefix_sums.begin(), it);
    }
};

/**
 * 2. Alias Method
 * Good for: High frequency sampling, static weights.
 * Complexity: O(N) setup, O(1) query.
 */
class WeightedRandomAlias {
    vector<int> alias;
    vector<double> prob;
    int n;

public:
    WeightedRandomAlias(vector<double> weights) {
        n = weights.size();
        alias.resize(n);
        prob.resize(n);
        
        double sum = accumulate(weights.begin(), weights.end(), 0.0);
        vector<double> scaled_weights(n);
        vector<int> small, large;
        
        for (int i = 0; i < n; ++i) {
            scaled_weights[i] = weights[i] * n / sum;
            if (scaled_weights[i] < 1.0)
                small.push_back(i);
            else
                large.push_back(i);
        }
        
        while (!small.empty() && !large.empty()) {
            int l = small.back(); small.pop_back();
            int g = large.back(); large.pop_back();
            
            prob[l] = scaled_weights[l];
            alias[l] = g;
            
            scaled_weights[g] = (scaled_weights[g] + scaled_weights[l]) - 1.0;
            if (scaled_weights[g] < 1.0)
                small.push_back(g);
            else
                large.push_back(g);
        }
        
        while (!large.empty()) {
            prob[large.back()] = 1.0;
            large.pop_back();
        }
        while (!small.empty()) {
            prob[small.back()] = 1.0;
            small.pop_back();
        }
    }

    int pickIndex() {
        uniform_int_distribution<> int_dis(0, n - 1);
        uniform_real_distribution<> real_dis(0.0, 1.0);
        
        int i = int_dis(gen);
        if (real_dis(gen) < prob[i])
            return i;
        else
            return alias[i];
    }
};

/**
 * 3. Weighted Reservoir Sampling (A-Res) / Efraimidis-Spirakis
 * Good for: Streams, One-pass, Weighted Without Replacement.
 * Key idea: k_i = u_i ^ (1/w_i). Largest keys win.
 */
int weightedReservoirOnePass(const vector<double>& stream_weights) {
    int max_index = -1;
    double max_key = -1.0;
    
    uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < stream_weights.size(); ++i) {
        double u = dis(gen);
        // Key formula: k = u^(1/w)
        double key = pow(u, 1.0 / stream_weights[i]);
        
        if (key > max_key) {
            max_key = key;
            max_index = i;
        }
    }
    return max_index;
}


/**
 * 4. Segment Tree Approach (Functional / No Class)
 * Good for: Dynamic weights (updates in O(log N)).
 */
 
// Global or passed vector for the tree
// Tree size should be 4*N.
// tree[node] stores the sum of weights in the range covered by 'node'.

void buildTree(vector<double>& tree, const vector<double>& weights, int node, int start, int end) {
    if (start == end) {
        tree[node] = weights[start];
    } else {
        int mid = (start + end) / 2;
        buildTree(tree, weights, 2 * node, start, mid);
        buildTree(tree, weights, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void updateTree(vector<double>& tree, int node, int start, int end, int idx, double val) {
    if (start == end) {
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            updateTree(tree, 2 * node, start, mid, idx, val);
        } else {
            updateTree(tree, 2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Returns the index of the sampled item
int queryTree(const vector<double>& tree, int node, int start, int end, double target) {
    if (start == end) {
        return start;
    }
    
    int mid = (start + end) / 2;
    // Check left child sum
    if (target < tree[2 * node]) {
        return queryTree(tree, 2 * node, start, mid, target);
    } else {
        // Go right, subtract left child's sum from target
        return queryTree(tree, 2 * node + 1, mid + 1, end, target - tree[2 * node]);
    }
}

// Helper to print distribution results
void verifyDistribution(const map<int, int>& counts, int total_trials, const vector<double>& weights) {
    double total_weight = accumulate(weights.begin(), weights.end(), 0.0);
    cout << setw(5) << "Item" << setw(10) << "Expected" << setw(10) << "Actual" << endl;
    for (size_t i = 0; i < weights.size(); ++i) {
        double expected = weights[i] / total_weight;
        // Handle case where item might not be picked at all in small trials
        double actual = 0.0;
        if (counts.find(i) != counts.end()) {
             actual = (double)counts.at(i) / total_trials;
        }
        cout << setw(5) << i << setw(10) << fixed << setprecision(4) << expected << setw(10) << actual << endl;
    }
}

int main() {
    vector<double> weights = {10.0, 50.0, 30.0, 10.0}; // weights for items 0, 1, 2, 3
    int trials = 100000;
    
    cout << "Weights: {10, 50, 30, 10}" << endl;
    cout << "---------------------------------" << endl;

    // 1. Prefix Sum
    cout << "\n1. Prefix Sum Approach (" << trials << " trials):" << endl;
    WeightedRandomPrefix prefixSolver(weights);
    map<int, int> countsPrefix;
    for(int i=0; i<trials; ++i) countsPrefix[prefixSolver.pickIndex()]++;
    verifyDistribution(countsPrefix, trials, weights);
    
    // 2. Alias Method
    cout << "\n2. Alias Method Approach (" << trials << " trials):" << endl;
    WeightedRandomAlias aliasSolver(weights);
    map<int, int> countsAlias;
    for(int i=0; i<trials; ++i) countsAlias[aliasSolver.pickIndex()]++;
    verifyDistribution(countsAlias, trials, weights);
    
    // 3. Reservoir Sampling (Stream)
    cout << "\n3. Reservoir Sampling (A-Res) Approach (" << trials << " trials):" << endl;
    map<int, int> countsRes;
    for(int i=0; i<trials; ++i) countsRes[weightedReservoirOnePass(weights)]++;
    verifyDistribution(countsRes, trials, weights);
    
    // 4. Segment Tree (Functional)
    cout << "\n4. Segment Tree Approach (" << trials << " trials):" << endl;
    int n = weights.size();
    vector<double> tree(4 * n, 0.0);
    buildTree(tree, weights, 1, 0, n - 1); // 1-based indexing for tree nodes
    
    map<int, int> countsSegTree;
    uniform_real_distribution<> dis(0, tree[1]); // tree[1] is total sum
    
    for(int i=0; i<trials; ++i) {
        double target = dis(gen);
        countsSegTree[queryTree(tree, 1, 0, n - 1, target)]++;
    }
    verifyDistribution(countsSegTree, trials, weights);

    // Optional: Demonstrate update
    cout << "\n[Demo] Updating weight of item 1 from 50.0 to 90.0..." << endl;
    // New weights: {10, 90, 30, 10} => Total 140. Item 1 is now 90/140 (~0.64).
    updateTree(tree, 1, 0, n - 1, 1, 90.0);
    // Update local weights vector for verification
    vector<double> new_weights = {10.0, 90.0, 30.0, 10.0};
    
    map<int, int> countsSegTreeUpdate;
    uniform_real_distribution<> dis_new(0, tree[1]);
    for(int i=0; i<trials; ++i) {
        double target = dis_new(gen);
        countsSegTreeUpdate[queryTree(tree, 1, 0, n - 1, target)]++;
    }
    verifyDistribution(countsSegTreeUpdate, trials, new_weights);
    
    return 0;
}
