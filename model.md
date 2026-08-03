# Model

Let $y = X\beta + \varepsilon$ represent a linear model. We express the $n \times p$ matrix $X$ as a row vector such that

$$
\begin{bmatrix}
y_1 \\
y_2 \\ 
\vdots \\
y_n
\end{bmatrix} =
\begin{bmatrix}
1 & x_1 & x_2 & \cdots & x_p
\end{bmatrix}
\begin{bmatrix}
\beta_0 \\
\beta_1 \\
\vdots \\
\beta_p
\end{bmatrix}
+
\begin{bmatrix}
\varepsilon_1 \\
\varepsilon_2 \\
\vdots \\
\varepsilon_n
\end{bmatrix}
$$

We compute the sequential sum of squares for $\beta_0,\beta_1,\dots,\beta_p$ using QR decomposition by Householder transformation.
The following logic is implemented by the $\mathtt{effects()}$ helper function in $\mathtt{model.cpp}$.

Let the $n \times p$ matrix $J$ be defined as

$$
J_{ij} =
\begin{cases}
0, & i \ne j \\
1, & i = j
\end{cases}
$$

```cpp
Eigen::MatrixXd j = Eigen::MatrixXd::Identity(m.n, m.k + 1);    // p = m.k + 1
```

**Householder Transformation**

Let $H_k$ be the symmetrical Householder reflection matrix for $x_k$ defined as

$$H_k = I - 2\frac{x_kx_k^{\text{T}}}{x_k^{\text{T}}x_k} = I - \frac{2}{\lVert x_k\rVert}x_kx_k^{\text{T}} = H_k^{\text{T}}$$

We efficiently compute the QR decomposition of $X$ from the representation $Q = H_1H_2\cdots H_p$

```cpp
Eigen::HouseholderQR<Eigen::MatrixXd> qr(m.x);
```

We multiply $H_1H_2\cdots H_p$ by $J$ to build an $n \times p$ partial $Q$ matrix

```cpp
Eigen::MatrixXd q = qr.householderQ() * j;
```

**Orthogonal Effects**

We multiply the transposed partial $Q$ matrix by $y$ to build the orthogonal effects vector $V$

$$V = (H_1H_2\cdots H_pJ)^{\text{T}}y = (J^{\text{T}}H_pH_{p-1}\cdots H_1)y$$

```cpp
Eigen::VectorXd proj = q.transpose() * m.y;
```
