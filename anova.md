# ANOVA

Let the $n \times p$ matrix $X$ be a row vector of $x_k$ terms

$$
X =
\begin{bmatrix}
x_1 & x_2 & \cdots & x_p
\end{bmatrix}
, \quad y = 
\begin{bmatrix}
y_1 \\
y_2 \\
\vdots \\
y_n
\end{bmatrix}
$$

Let the $n \times p$ matrix $J$ be defined as

$$
J_{ij} =
\begin{cases}
0, & i \ne j \\
1, & i = j
\end{cases}
$$

```cpp
Eigen::MatrixXd i = Eigen::MatrixXd::Identity(m.n, m.k + 1);    // p = m.k + 1
```

Let $P_k$ be the partial Householder reflection matrix for $x_k$ defined as

$$P_k = J - 2\frac{x_k(x_k^{\text{T}}J)}{x_k^{\text{T}}x_k}$$

Hence $P_k$ is not necessarily symmetrical.

**QR Factorisation**

The product of Householder matrices $H_1$ to $H_p$ is equal to the orthogonal $Q$ matrix

$$
Q = H_1H_2\cdots H_p, \quad Q^{\text{T}} = (H_1H_2\cdots H_p)^{\text{T}} = H_1^{\text{T}}H_2^{\text{T}}\cdots H_p^{\text{T}} = H_pH_{p-1}\cdots H_1
$$

**Sequential Sum of Squares**

```cpp
Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
Eigen::MatrixXd q = qr.householderQ() * i;
Eigen::VectorXd proj = q.transpose() * m.y;
```

The 

