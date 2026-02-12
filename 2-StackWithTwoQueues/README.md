# 2. Stack with Two Queues

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Explanation

Let me explain this data structure design problem as an interviewer would present it.

### Problem Statement

**Design a stack data structure using only queue operations.**

You need to implement a **Last-In-First-Out (LIFO)** stack using **two queues** which are **First-In-First-Out (FIFO)** data structures.

### Stack Operations to Implement
1. **push(x)** - Add element x to the top of stack
2. **pop()** - Remove and return the top element
3. **top()** - Return the top element without removing it
4. **empty()** - Check if stack is empty

### Queue Operations Available
You can only use standard queue operations:
- `enqueue(x)` - Add element to the back of queue
- `dequeue()` - Remove and return element from front of queue
- `front()` - View front element
- `size()` - Get number of elements
- `is_empty()` - Check if empty

---

### The Challenge

**Key insight:** Queues and stacks have **opposite ordering**:
- **Queue:** First in, first out (FIFO) - like a line at a store
- **Stack:** Last in, first out (LIFO) - like a stack of plates

**Example:**
```
Add elements: 1, 2, 3

Queue removes: 1, 2, 3  (same order as added)
Stack removes: 3, 2, 1  (reverse order)
```

**Your task:** Make a queue behave like a stack!

---

### Visualization

```
Stack operations we want:
push(1) -> [1]
push(2) -> [2, 1]
push(3) -> [3, 2, 1]
pop()   -> returns 3, stack becomes [2, 1]
pop()   -> returns 2, stack becomes [1]

Using queues (FIFO):
Queue normally: front [1, 2, 3] back
We need to get 3 first, but queue gives us 1!
```

---

### Solutions & Complexity Analysis

We can achieve stack behavior using two queues (`q1`, `q2`) with two different trade-offs.

#### Approach 1: Make `push` Operation Costly
In this approach, we ensure that the **newly added element is always at the front of `q1`**. This way, `pop()` simply involves dequeuing from `q1`.

**Algorithm:**
1.  **Push(x):**
    - Enqueue `x` to `q2`.
    - Dequeue everything from `q1` and enqueue to `q2`.
    - Swap the names of `q1` and `q2`.
2.  **Pop():**
    - Dequeue from `q1`.

**Complexity:**
-   **Push:** $O(n)$ - We move all $n$ elements.
-   **Pop:** $O(1)$ - Direct removal.
-   **Space:** $O(n)$ - Use of two queues.

#### Approach 2: Make `pop` Operation Costly
In this approach, we simply enqueue new elements to `q1`. For `pop`, we have to traverse the entire queue to get the last element.

**Algorithm:**
1.  **Push(x):**
    - Enqueue `x` to `q1`.
2.  **Pop():**
    - Move all elements except the last one from `q1` to `q2`.
    - Return and remove the last remaining element of `q1`.
    - Swap the names of `q1` and `q2`.

**Complexity:**
-   **Push:** $O(1)$ - Simple enqueue.
-   **Pop:** $O(n)$ - We traverse all $n$ elements.
-   **Space:** $O(n)$ - Use of two queues.

---

### Interview Questions for You

Before we code, let me ask:

**Q1:** If you have two queues `q1` and `q2`, and you want to add element `5` to your stack, how would you do it such that `5` becomes accessible first (like a stack top)?

**Q2:** When you need to pop from the stack, how can you use the two queues to get the most recently added element?

**Q3:** Which approach would you prefer?
- Push in O(1), Pop in O(n)?
- Push in O(n), Pop in O(1)?

Consider: What's more common in real applications - pushing or popping?

**Q4:** Can you do this with just **one queue** instead of two? (Bonus challenge!)

---

### Hint for Approach 1 (Push is O(n))

Think about it this way:
```
Current stack (in q1): [1, 2, 3]  (3 is at front, ready to pop)
Now push(4):
  - How do you make 4 go to the front of the queue?
  - What if you use q2 as temporary storage?
```

### Hint for Approach 2 (Pop is O(n))

```
Current stack (in q1): [3, 2, 1]  (1 was added last, at back)
Now pop():
  - You need to get to 1, but it's at the back
  - How can you move elements around using q2?
  - How many elements do you need to transfer?
```

---

**Take a moment to think through one approach.** 

Which strategy makes more sense to you? Can you sketch out the algorithm in pseudocode before we implement it?

This is exactly how I'd guide you - I want to see your thought process before jumping to code!
