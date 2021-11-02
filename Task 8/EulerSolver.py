import numpy as np
import matplotlib.pyplot as plt

from numba import jit
from numpy.linalg import inv

class EulerSolver:
    
    @staticmethod
    @jit(nopython=True)
    def solve_implicit(t: np.ndarray, mat: np.ndarray, init_cond: np.ndarray) -> np.ndarray:
        assert t.ndim == 1, "time array must be 1 dimention!"
        assert init_cond.size == mat.shape[1]
        
        n = len(init_cond)
        y: np.ndarray = np.zeros((t.size, n))
        y[0] = init_cond
        
        for i in range(t.size - 1):
            h: float = t[i + 1] - t[i]
            f: np.ndarray = np.dot(mat, y[i])
            d_y: np.ndarray = h * np.dot(inv(np.identity(n) - h * mat), f)
            y[i + 1] = y[i] + d_y
            
        return y.transpose()
    
    @staticmethod
    @jit(nopython=True)
    def solve_explicit(t: np.ndarray, mat: np.ndarray, init_cond: np.ndarray) -> np.ndarray:
        assert t.ndim == 1, "time array must be 1 dimention!"
        assert init_cond.size == mat.shape[1]
        
        n = len(init_cond)
        y: np.ndarray = np.zeros((t.size, n))
        y[0] = init_cond
        
        for i in range(t.size - 1):
            h: float = t[i + 1] - t[i]
            f: np.ndarray= np.dot(mat, y[i])
            y[i + 1] = y[i] + h * f
        
        return y.transpose()

    