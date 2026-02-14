import random

def expected_draws_simulation(n_simulations=1000000):
    """
    Monte Carlo simulation: expected draws to first Ace
    """
    total_draws = 0
    
    # Create deck: 4 Aces (1) and 48 non-Aces (0)
    base_deck = [1] * 4 + [0] * 48
    
    for _ in range(n_simulations):
        deck = base_deck[:]
        random.shuffle(deck)
        
        # Count draws until first Ace
        for i, card in enumerate(deck):
            if card == 1:  # Drew an Ace
                total_draws += (i + 1)
                break
                
    return total_draws / n_simulations


def expected_draws_formula(N=52, K=4):
    """
    Exact formula: E[X] = (N+1)/(K+1)
    """
    return (N + 1) / (K + 1)


def expected_draws_recursive(n_non_aces=48, k_aces=4):
    """
    Recursive calculation: E_n = 1 + (n / (n + k)) * E_{n-1}
    """
    E = 1.0 # Base case: E_0 = 1 (only Aces left)
    for i in range(1, n_non_aces + 1):
        E = 1 + (i / (i + k_aces)) * E
    return E


if __name__ == "__main__":
    print("Expected Draws to Get an Ace (N=52, K=4)")
    print("-" * 40)
    
    formula_result = expected_draws_formula()
    recursive_result = expected_draws_recursive()
    
    print(f"Formula Result:   {formula_result:.4f}")
    print(f"Recursive Result: {recursive_result:.4f}")
    
    print("\nRunning Monte Carlo Simulation (1,000,000 trials)...")
    sim_result = expected_draws_simulation()
    print(f"Simulation Result: {sim_result:.4f}")
    
    print("-" * 40)
    print("Verification Successful!" if abs(sim_result - formula_result) < 0.01 else "Verification Failed.")
