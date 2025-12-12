import numpy as np
from vec_typing import Matrix, Vector

def relu(x: Matrix) -> Matrix:
    return 1/(1 + np.exp(-x))
    return np.maximum(0, x)

def relu_prime(x: Matrix) -> Matrix:
    return np.exp(-x)/np.pow((1 + np.exp(-x)), 2)
    return (x > 0).astype(np.float64)



class Layer:
    def __init__(self, in_dim: int, out_dim: int, batch_size: int) -> None:
        # print(f"Initialized Layer ({in_dim}, {out_dim})")
        self.in_dim = in_dim
        self.out_dim = out_dim
        self.batch_size = batch_size

        self.W = np.random.rand(self.in_dim, self.out_dim)
        self.B = np.random.rand(self.batch_size, self.out_dim)

        self.Z = None
        self.A = None

    def forward(self, A_prev: Matrix) -> Matrix:
        #print("A size: ", len(A_prev), len(A_prev[0]))
        #print("W size: ", len(self.W), len(self.W[0]))
        self.Z = (A_prev @ self.W) + self.B
        self.A = relu(self.Z)

        # print(f">>>> Forwarding layer ({self.in_dim}, {self.out_dim})")
        # print("A: ", self.Z)
        # print("W: ", self.W)
        # print()

        return self.A

    # def cost_func(self, x: np.ndarray, y: np.ndarray) -> np.ndarray:
    #     y_hat, z_hat = self.forward(x)
    #     J = 0.5 * (np.power((y - y_hat), 2))
    #     return J

    def update_weights(self, W_flattened: Vector) -> None:
        self.W = np.reshape(W_flattened, (self.in_dim, self.out_dim))

    def backward(self, delta_next: Matrix, A_prev: Matrix, Z_prev: Matrix) -> tuple[Matrix, Matrix]:
        # print(f">>>> Currently in layer ({self.in_dim}, {self.out_dim})")
        # print("Z size: ", np.shape(self.Z))
        # print(np.shape(delta_next), np.shape(self.W.T), np.shape(self.Z))
        # print()
        delta = np.multiply(delta_next @ (self.W).T, relu_prime(Z_prev))
        gradient = (A_prev).T @ delta_next
        return gradient, delta