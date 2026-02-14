#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Calculates the time until all ants fall off the stick.
 * 
 * @param length The length of the stick (L).
 * @param positions A vector of positions of the ants.
 * @param directions A vector of directions (+1 for Right, -1 for Left).
 * @param speed The speed of the ants (v).
 * @return The maximum time until the last ant falls off.
 */
double solveAntsMaxTime(double length, const vector<double>& positions, const vector<int>& directions, double speed) {
    double max_time = 0.0;

    for (size_t i = 0; i < positions.size(); ++i) {
        double pos = positions[i];
        int dir = directions[i];
        double time_to_exit = 0.0;

        // Key Insight: Treats collisions as "pass-through".
        // We just calculate the time for this specific "particle" to exit 
        // in its current direction.
        
        if (dir == 1) { // Moving Right
            time_to_exit = (length - pos) / speed;
        } else { // Moving Left (-1)
            time_to_exit = pos / speed;
        }

        max_time = max(max_time, time_to_exit);
    }

    return max_time;
}

/**
 * Calculates the worst-case time (Maximum possible time) if we could CHOOSE directions.
 * This is often the form of the question: "What is the max possible time?" implies worst-case arrangement.
 */
double solveWorstCaseMaxTime(double length, const vector<double>& positions, double speed) {
    double max_time = 0.0;
    for (double pos : positions) {
        // Worst case: walk the longer distance to an end
        double dist = max(pos, length - pos);
        max_time = max(max_time, dist / speed);
    }
    return max_time;
}

/**
 * Calculates the best-case time (Minimum possible time) if we could CHOOSE directions.
 */
double solveBestCaseMinTime(double length, const vector<double>& positions, double speed) {
    double max_time = 0.0; // The time for the system is the max of individual times
    for (double pos : positions) {
        // Best case: walk the shorter distance to an end
        double dist = min(pos, length - pos);
        max_time = max(max_time, dist / speed); // We still need the LAST ant to finish
    }
    return max_time;
}

int main() {
    double length = 100.0;
    double speed = 1.0;
    
    // Example: 3 Ants
    vector<double> positions = {20.0, 50.0, 80.0};
    vector<int> directions = {1, -1, 1}; // Right, Left, Right

    cout << "Stick Length: " << length << ", Speed: " << speed << endl;
    cout << "Ants at: {20, 50, 80} with directions {R, L, R}" << endl;
    
    // 1. Specific Scenario
    double time = solveAntsMaxTime(length, positions, directions, speed);
    cout << "Time to clear (Specific Scenario): " << time << " seconds" << endl;

    // 2. Worst Case (The usual riddle answer)
    // "What is the maximum time?" often implies we don't know directions and want the bound.
    double worst_case = solveWorstCaseMaxTime(length, positions, speed);
    cout << "Worst Case Time (Max possible): " << worst_case << " seconds" << endl;

    // 3. Best Case
    double best_case = solveBestCaseMinTime(length, positions, speed);
    cout << "Best Case Time (Min possible): " << best_case << " seconds" << endl;
    
    // Verification
    // Ant A (20, R) -> Dist 80 -> Time 80
    // Ant B (50, L) -> Dist 50 -> Time 50
    // Ant C (80, R) -> Dist 20 -> Time 20
    // Max is 80.
    
    if (abs(time - 80.0) < 1e-9) {
        cout << "\nVerification Successful: Matches analytic result (80.0)." << endl;
    } else {
        cout << "\nVerification Failed." << endl;
    }

    return 0;
}
