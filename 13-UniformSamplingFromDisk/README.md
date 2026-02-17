To solve the challenge of **Uniform Sampling from a Disk** (Medium-Priority Question #13/19), we must ensure that every point within the circle has an equal probability of being selected. As a master explorer, I will show you the two paths to the summit: the **Polar Coordinate Path** (using math to warp space) and the **Rejection Sampling Path** (the "guess and check" method).

---

## Method 1: The Polar Coordinate Path (Inverse Transform)

This path uses trigonometry and calculus to transform simple random numbers into coordinates on a disk.

### Step 1: The Recursive/Naive Approach

Imagine we try a simple recursive approach where we pick a distance  and an angle .

* **Base Case:** If  and  are valid, return the point.
* **Recursive Step:** , .

**The Problem:** If you do this, you'll find your points are "clumped" in the center. This is because there is much less area near the center of a circle than near the edge. A uniform distribution in  does **not** result in a uniform distribution in area.

### Step 2: The Solution (Square Root Transformation)

To fix the clumping, we must account for the fact that area grows with . We take the **square root** of our random variable to "push" more points toward the outer edge.

```python
import math
import random

def sample_disk_polar(R):
    # 1. Generate uniform random variables between 0 and 1
    u = random.random()
    theta = random.random() * 2 * math.pi
    
    # 2. Apply the 'Square Root' transformation to the radius
    # This ensures the density is uniform across the area
    r = R * math.sqrt(u)
    
    # 3. Convert Polar to Cartesian coordinates
    x = r * math.cos(theta)
    y = r * math.sin(theta)
    
    return (x, y)

```

---

## Method 2: Rejection Sampling (The "No-Math" Way)

The PDF highlights a specific variant: **Uniform Sampling of a Disk Without Square Root**. This is the "Rejection Sampling" method.

### Step 1: The Logic

1. **Define a Box:** Imagine a square that encloses the circle. If the circle's radius is , the square goes from  to  on both axes.
2. **Generate a Point:** Pick a random  and  within that square.
3. **The Inequality:** Check if the point is inside the circle using the Pythagorean theorem: .

### Step 2: The Iterative (DP-like) Solution

Instead of recursion, we use a simple `while` loop to "reject" points that fall in the corners of the square.

```python
def sample_disk_rejection(R):
    while True:
        # 1. Pick a random point in the bounding square [-R, R]
        x = random.uniform(-R, R)
        y = random.uniform(-R, R)
        
        # 2. Check the 'Inside' condition: x^2 + y^2 <= R^2
        # This is the core subproblem check
        if x**2 + y**2 <= R**2:
            return (x, y) # Success!
        
        # 3. If it failed (in the corners), the loop iterates again

```

---

## Comparison of the Two Paths

| Feature | Polar (Square Root) | Rejection (No Square Root) |
| --- | --- | --- |
| **Time Complexity** |  constant time |  average case (fails  of the time) |
| **Space Complexity** |  |  |
| **Computations** | Needs `sqrt`, `cos`, `sin` 

 | Needs simple multiplication/addition 

 |

**Master's Insight:** In high-frequency trading (HFT) environments, `sqrt` and trigonometric functions can be "expensive" for a CPU. This is why the **Rejection Method** is often preferred by Quants—it's computationally "cheaper" even though it occasionally has to try twice!.
