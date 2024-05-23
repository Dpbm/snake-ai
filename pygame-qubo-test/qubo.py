from itertools import product

def qubo(Q, P):
    results = {}

    for comb in product([0,1], repeat=3):    
        linear = 0
        for i in range(3):
            q = Q[i][i]
            linear += q*comb[i]

        penality = 0
        for i in range(3):
            penality += comb[i]
        penality -= 1
        penality = P*(penality**2)

        result = linear + penality

        str_comb = ''.join(map(str, comb))
        results[str_comb] = result
    min_key = min(results, key=results.get)

    print(f'[*] QUBO result: {min_key} {results[min_key]}')
    return min_key
