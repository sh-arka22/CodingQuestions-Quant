#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

/**
 * Approach 1: Push is Costly O(N)
 * In this approach, we make sure that the newly added element is always at the front of q1.
 * To achieve this, we need to move all elements from q1 to q2, add the new element to q1, 
 * and then move everything back.
 */
class StackPushOn {
private:
    queue<int> q1, q2;

public:
    // Push element x onto stack
    // Time Complexity: O(N)
    void push(int x) {
        // 1. Enqueue x to q2
        q2.push(x);

        // 2. Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // 3. Swap the names of q1 and q2
        swap(q1, q2);
    }

    // Removes the element on top of the stack and returns that element
    // Time Complexity: O(1)
    int pop() {
        if (q1.empty()) {
            throw runtime_error("Stack is empty");
        }
        int topElement = q1.front();
        q1.pop();
        return topElement;
    }

    // Get the top element
    // Time Complexity: O(1)
    int top() {
        if (q1.empty()) {
            throw runtime_error("Stack is empty");
        }
        return q1.front();
    }

    // Returns whether the stack is empty
    // Time Complexity: O(1)
    bool empty() {
        return q1.empty();
    }
};

/**
 * Approach 2: Pop is Costly O(N)
 * In this approach, push is simple (O(1)).
 * For pop, we have to move all elements except the last one from q1 to q2. 
 * The last element of q1 is the top of the stack.
 */
class StackPopOn {
private:
    queue<int> q1, q2;

public:
    // Push element x onto stack
    // Time Complexity: O(1)
    void push(int x) {
        q1.push(x);
    }

    // Removes the element on top of the stack and returns that element
    // Time Complexity: O(N)
    int pop() {
        if (q1.empty()) {
            throw runtime_error("Stack is empty");
        }

        // Move all elements except the last one from q1 to q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        // The last element left in q1 is the one to be popped
        int topElement = q1.front();
        q1.pop();

        // Swap the names of q1 and q2 so q1 is ready for next push
        swap(q1, q2);

        return topElement;
    }

    // Get the top element
    // Time Complexity: O(N) - Similar logic to pop to reach the back
    int top() {
        if (q1.empty()) {
            throw runtime_error("Stack is empty");
        }

        // Move all elements except the last one from q1 to q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        int topElement = q1.front();
        
        // Move the last element too
        q2.push(topElement);
        q1.pop();

        // Swap back to restore state
        swap(q1, q2);
        
        return topElement;
    }

    // Returns whether the stack is empty
    // Time Complexity: O(1)
    bool empty() {
        return q1.empty();
    }
};

void testPushOn() {
    cout << "Testing Approach 1: Push O(N)..." << endl;
    StackPushOn s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Top: " << s.top() << " (Expected: 3)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 3)" << endl;
    cout << "Top: " << s.top() << " (Expected: 2)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 2)" << endl;
    
    s.push(4);
    cout << "Top: " << s.top() << " (Expected: 4)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 4)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 1)" << endl;
    
    if(s.empty()) cout << "Stack is empty (Expected: Yes)" << endl;
    else cout << "Stack is NOT empty (Expected: No)" << endl;
    cout << "-----------------------------------" << endl;
}

void testPopOn() {
    cout << "Testing Approach 2: Pop O(N)..." << endl;
    StackPopOn s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Top: " << s.top() << " (Expected: 3)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 3)" << endl;
    cout << "Top: " << s.top() << " (Expected: 2)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 2)" << endl;
    
    s.push(4);
    cout << "Top: " << s.top() << " (Expected: 4)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 4)" << endl;
    cout << "Pop: " << s.pop() << " (Expected: 1)" << endl;
    
    if(s.empty()) cout << "Stack is empty (Expected: Yes)" << endl;
    else cout << "Stack is NOT empty (Expected: No)" << endl;
    cout << "-----------------------------------" << endl;
}

int main() {
    try {
        testPushOn();
        testPopOn();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
