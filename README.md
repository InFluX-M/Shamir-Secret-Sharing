# Shamir's Secret Sharing Scheme

## Overview

This project implements Shamir's Secret Sharing scheme in C++. Shamir's Secret Sharing is a cryptographic algorithm used to divide a secret into multiple shares. The secret can only be reconstructed when a sufficient number of shares are combined. This implementation allows the creation of shares and the recovery of the secret using modular arithmetic.

## Files

- `main.cpp`: The main implementation file containing the code for the Shamir's Secret Sharing scheme.

## Structs and Functions

### `struct mint`

The `mint` struct handles modular arithmetic operations, which are fundamental to the Shamir's Secret Sharing scheme. It includes:

- **Constructors:**
  - `mint()`: Default constructor, sets value to 0 and modulus to 1.
  - `mint(ll _v, int _MOD)`: Constructor that initializes the value and modulus.
  
- **Operators:**
  - Arithmetic operators: `+`, `-`, `*`, `/`
  - Increment and decrement operators: `++`, `--`
  - Comparison operators: `==`, `!=`, `<`, `>`, `<=`, `>=`

- **Methods:**
  - `pow(mint a, ll b)`: Computes \(a^b\) under modulo.
  - `inv(const mint &a)`: Computes the modular inverse of `a`.

### `vector<mint> poly`
A global vector to store the polynomial coefficients used to generate the shares.

### `vector<mint> shares`
A global vector to store the generated shares.

### `vector<mint> make_poly(int t, mint s, int MOD)`
Generates a random polynomial of degree `t-1` with a constant term `s` and a specified modulus `MOD`.

### `vector<mint> share_production(int n, int t, int MOD)`
Generates `n` shares using the polynomial of degree `t-1`. Ensures no share is zero.

### `mint secret_discovery(set<int> idxs, int t, int MOD)`
Recovers the secret using `t` shares specified by their indices `idxs`.

## Usage

### Compilation

To compile the code, use a C++ compiler such as `g++`:
```bash
g++ -o secret_sharing main.cpp
```

### Execution

Run the executable and provide the required inputs:
```bash
./secret_sharing
```

### Input

The program expects the following inputs:
1. `s_t`: The secret to be shared.
2. `t`: The threshold number of shares required to reconstruct the secret.
3. `n`: The total number of shares to be generated.
4. `MOD`: The modulus to be used for modular arithmetic operations.

### Example

```
Input:
12345
3
5
10007

Output:
12345
```

This example demonstrates creating 5 shares of the secret `12345` with a threshold of 3 using the modulus `10007`.

## Algorithm

1. **Polynomial Generation**:
   - A random polynomial of degree `t-1` is generated with the constant term equal to the secret.
2. **Share Production**:
   - Shares are produced by evaluating the polynomial at different points.
3. **Secret Recovery**:
   - The secret is recovered by combining `t` shares using Lagrange interpolation.

## Contributions

Contributions are welcome! Feel free to submit a pull request or open an issue for any bugs or feature requests.

## Acknowledgements

This project is based on the principles of Shamir's Secret Sharing as described by Adi Shamir in 1979. 

---

By following this guide, you should be able to understand, compile, and run the Shamir's Secret Sharing scheme implemented in this project. Feel free to explore and modify the code for your needs.
