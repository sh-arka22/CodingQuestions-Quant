import math
import random

def sample_disk_polar(R):
    """
    Samples a point uniformly from a disk of radius R using polar coordinates with square root transformation.
    """
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

def sample_disk_rejection(R):
    """
    Samples a point uniformly from a disk of radius R using rejection sampling.
    """
    while True:
        # 1. Pick a random point in the bounding square [-R, R]
        x = random.uniform(-R, R)
        y = random.uniform(-R, R)
        
        # 2. Check the 'Inside' condition: x^2 + y^2 <= R^2
        # This is the core subproblem check
        if x**2 + y**2 <= R**2:
            return (x, y) # Success!
        
        # 3. If it failed (in the corners), the loop iterates again

if __name__ == "__main__":
    radius = 5.0
    num_samples = 10
    
    print(f"Sampling {num_samples} points from a disk of radius {radius}:\n")
    
    print("--- Polar Coordinate Path (Inverse Transform) ---")
    for i in range(num_samples):
        x, y = sample_disk_polar(radius)
        print(f"Sample {i+1}: ({x:.4f}, {y:.4f})")
    
    print("\n--- Rejection Sampling (No-Math Way) ---")
    for i in range(num_samples):
        x, y = sample_disk_rejection(radius)
        print(f"Sample {i+1}: ({x:.4f}, {y:.4f})")
