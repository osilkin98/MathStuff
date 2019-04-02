from math import sqrt

def sieve(n: int) -> list:
    numbers = [0, 0] + [1 for i in range(2, n + 1)]
    primes = []
    prime = 2
    while prime < n:
        primes.append(prime)
        for multiple in range(prime**2, n+1, prime):
            numbers[multiple] = 0
        prime += 1
        while numbers[prime] == 0 and prime + 1 <= n:
            prime += 1
    return primes

def sieve_with_sets(n: int) -> set:
    thresh = int(sqrt(n))
    first_primes = sieve(thresh + 1)
    numbers = {i for i in range(2, n + 1)}
    for p in first_primes:
        numbers -= {p*k for k in range(2, n+1)}
    return numbers
