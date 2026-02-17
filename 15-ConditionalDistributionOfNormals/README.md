# 15. Conditional Distribution of Normals

### Problem Statement

Given two independent and identically distributed (i.i.d.) standard normal random variables, $X, Y \sim \mathcal{N}(0, 1)$, find the distribution of $X$ given that $X + Y > 0$.

## Mathematical Derivation

Let $X, Y \sim \mathcal{N}(0, 1)$ be i.i.d. standard normals. We want the distribution of $X$ given $X + Y > 0$.

Using Bayes' theorem for densities:
$$f_{X|X+Y>0}(x) = \frac{P(X+Y>0|X=x) \cdot f_X(x)}{P(X+Y>0)}$$

Since $Y$ is independent of $X$:
- $P(X+Y>0|X=x) = P(Y > -x) = \Phi(x)$ (where $\Phi$ is the standard normal CDF)
- $P(X+Y>0) = \frac{1}{2}$ (by symmetry of the sum of two i.i.d. random variables)
- $f_X(x) = \phi(x)$ (the standard normal PDF)

Therefore, substituting these into the formula:
$$\boxed{f_{X|X+Y>0}(x) = 2\phi(x)\Phi(x)}$$

This resulting distribution is a well-known one: the **skew-normal distribution** with shape parameter $\alpha = 1$.

## Intuitive Explanation and Key Properties

The conditional distribution exhibits three key characteristics:

### 1. **Positive Skew (Asymmetry)**
The condition $X + Y > 0$ acts as a **selection filter** that favors positive values of $X$. When $X$ is negative, $Y$ must be sufficiently positive to compensate ($Y > -X$), which becomes exponentially unlikely as $X 	o -\infty$. This explains why the left tail of the conditional distribution is suppressed compared to the right tail.

### 2. **The Weighting Mechanism**
For any value $X = x$, the probability that the condition $X + Y > 0$ is satisfied equals $\Phi(x)$—the area under the standard normal curve to the left of $x$. Thus, the new density is proportional to the original density weighted by this selection probability:
$$f_{X|X+Y>0}(x) \propto \underbrace{\phi(x)}_{	ext{Original density}} 	imes \underbrace{\Phi(x)}_{	ext{Selection probability}}$$

The factor of 2 in the final formula, $2\phi(x)\Phi(x)$, is the normalization constant that ensures the total probability integrates to 1.

### 3. **Geometric Interpretation**
In the joint $(X,Y)$ plane, the distribution of `(X, Y)` is a bivariate normal "bell curve" centered at the origin. Conditioning on $X+Y > 0$ restricts us to the upper-right half-plane (the region where $Y > -X$). The conditional density of $X$ is the marginal distribution obtained by integrating out $Y$ from this half-plane:
$$f_{X|X+Y>0}(x) = \int_{-x}^{\infty} f_{X,Y}(x,y) \, dy \Big/ P(X+Y>0)$$

This process is like "slicing" the bivariate normal bell curve along the line $Y = -X$ and accumulating the probability mass above that line for each value of $X$.

### Key Properties
- **Distribution Family**: This is the **skew-normal distribution** with shape parameter $\alpha = 1$.
- **Mean Shift**: The mean shifts from its original value of $0$ to a positive value, $\mathbb{E}[X|X+Y>0] = \frac{1}{\sqrt{\pi}} \approx 0.564$. The condition biases our expectation for $X$ upward.
- **Variance Reduction**: The variance is reduced from $1$ to $1 - \frac{1}{\pi} \approx 0.682$. Conditioning on an event reduces our uncertainty about the variable.

### Practical Interpretation
If you observe that the sum of two independent, standard normal variables is positive, your posterior belief about either individual variable should shift rightward. However, you remain uncertain—it doesn't guarantee that $X$ was positive, only that it has become more likely (the probability is now greater than 0.5).
