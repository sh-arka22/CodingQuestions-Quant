# 9. Ants Walking on a Stick

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Statement

You have a **stick of length L** (say, 1 meter).
There are **N ants** placed at random positions on the stick.
Each ant starts moving either **left** or **right** with constant speed **v** (say, 1 m/s).

**Key Rules:**
1. When an ant reaches the **end of the stick**, it falls off.
2. When two ants **collide**, they both **instantly reverse direction** and continue moving with the same speed.

**Question:** What is the **maximum time** until all ants have fallen off the stick?

---

### The Key Insight: "Pass-Through" Trick

At first glance, this problem seems to require complex simulation of collisions. However, consider what happens when two identical ants collide:
- Ant A (moving Right) hits Ant B (moving Left).
- They both reverse direction.
- **Physically indistinguishable:** This looks exactly the same as if Ant A and Ant B just **passed through each other** without stopping.

Since the ants are identical, we can pretend that they simply pass through each other. The identity of the ant doesn't matter for the *time* calculation, only the position of the "particle".

### The Solution

Because of the pass-through trick, each ant acts independently.
- An ant at position $x$ moving **Right** takes $(L - x) / v$ time to fall off.
- An ant at position $x$ moving **Left** takes $x / v$ time to fall off.

To find the **maximum time** until *all* ants fall off, we simply calculate the time remaining for every single ant (assuming no collisions) and take the maximum.

$$T_{max} = \max_{i} (\text{time to exit for ant } i)$$

If we can choose directions to maximize time (worst case), we choose the direction that maximizes the distance for each ant: $\max(x, L-x)$.

### Minimum Time

If we want the **minimum time** to clear the stick (best case), each ant should move towards the nearest end.
$$T_{min} = \max_{i} (\min(x_i, L - x_i)) / v$$

---

### Interview Questions - Answered

**Q1: The Identity Problem - If I asked "Which specific ant falls off last?", does the trick still work?**
No, the pass-through trick loses the identity of the ants. To find *which* specific ant falls off last, you would need to track the collisions (or use a more advanced sorting trick where you realize the order of ants on the stick is preserved, so if $k$ ants fall off the left, they must be the $k$ leftmost ants).

**Q2: Variable Speeds - What if ants have different speeds?**
The trick breaks. If a fast ant hits a slow ant, swapping velocities changes the state of the system (a fast particle becomes a slow particle). You would need a full simulation.

**Q3: Circular Track - What if they are on a ring?**
They never fall off! But if asked about return times, you can still use pass-through to think about "particles" moving around the ring.

**Q4: Ants on a Log - What if the log grows?**
This becomes a related rates / calculus problem. The "distance remaining" changes dynamically.

[View Solution Code](./main.cpp)
