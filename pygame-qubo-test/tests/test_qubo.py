import unittest
from qubo import qubo

class TestQubo(unittest.TestCase):
    def test_qubo(self):
        Q = [
                [1, 0, 0],
                [0, 1, 0],
                [0, 0, 1]
            ]
        P = 10
        self.assertEqual(qubo(Q, P), '001')
    
    def test_qubo_different_dir(self):
        Q = [
                [1, 0, 0],
                [0, 0, 0],
                [0, 0, 1]
            ]
        P = 10
        self.assertEqual(qubo(Q, P), '010')

    def test_qubo_last_dir(self):
        Q = [
                [0, 0, 0],
                [0, 1, 0],
                [0, 0, 1]
            ]
        P = 10
        self.assertEqual(qubo(Q, P), '100')

if __name__ == '__main__':
    unittest.main()
