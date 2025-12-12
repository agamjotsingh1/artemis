import numpy as np
from scipy import optimize

from vec_typing import Matrix, Vector
from layer import Layer, relu_prime

class NeuralNet:
    def __init__(self, in_dim: int, out_dim: int, batch_size: int, depth_dim: list[int]):
        self.in_dim = in_dim
        self.out_dim = out_dim
        self.batch_size = batch_size
        self.depth_dim = depth_dim
        self.depth = len(depth_dim)

        self.layers = [Layer(in_dim, depth_dim[0] if self.depth > 0 else out_dim, self.batch_size)] \
            + [Layer(depth_dim[i], depth_dim[i + 1], self.batch_size) for i in range(self.depth - 1)] \
            + [Layer(depth_dim[self.depth - 1] if self.depth > 0 else in_dim, out_dim, self.batch_size)];

        self.depth = len(self.layers)

    def forward(self, X: Matrix) -> Matrix:
        A = self.layers[0].forward(X)
        for i in range(1, self.depth):
            # print(i)
            # layer = self.layers[i]
            # print("Forwarding in layer ", layer.in_dim, layer.out_dim)
            A = self.layers[i].forward(A)

        return A

    # TODO: edit to support out_dim != 1
    def cost(self, X: Matrix, Y: Matrix) -> np.float64:
        Y_hat = self.forward(X)
        J = 0.5 * np.sum(np.pow((Y - Y_hat), 2))
        return J

    def update_all_weights(self, weights: Vector):
        layer_index = 0
        iterator = 0

        while iterator < len(weights):
            layer = self.layers[layer_index]
            stride = layer.in_dim * layer.out_dim
            self.layers[layer_index].update_weights(weights[iterator:(iterator + stride)])

            iterator += stride
            layer_index += 1

    # TODO: edit to support out_dim != 1
    # NOTE: cost() has to be called before this for proper functioning
    def cost_prime(self, X: Matrix, Y: Matrix, Y_hat: Matrix) -> np.float64:
        delta = -np.multiply((Y - Y_hat), relu_prime(self.layers[-1].Z))

        A = self.layers[-2].A 
        Z = self.layers[-2].Z
        ind_prev = self.depth - 2

        gradient, delta = self.layers[-1].backward(delta, A, Z)
        augmented_gradient = gradient.ravel()

        for i in range(self.depth - 2, -1, -1):
            ind_prev -= 1
            A = self.layers[ind_prev].A if ind_prev > 0 else X
            Z = self.layers[ind_prev].Z

            gradient, delta = self.layers[i].backward(delta, A, Z)
            augmented_gradient = np.concatenate((gradient.ravel(), augmented_gradient))

        return augmented_gradient

    def minimize_cost_wrapper(self, params: Vector, X: Matrix, Y: Matrix):
        self.update_all_weights(params)
        cost = self.cost(X, Y)

        Y_hat = self.layers[-1].A
        cost_prime = self.cost_prime(X, Y, Y_hat)
        print(cost, len(cost_prime))

        return cost, cost_prime

    def train(self, X: Matrix, Y: Matrix):
        initial_weights = np.concatenate([layer.W.ravel() for layer in self.layers])

        opts = {'maxiter': 200, 'disp' : True}
        optimize.minimize(self.minimize_cost_wrapper, initial_weights, \
                                    jac=True, method='BFGS', args=(X, Y), options=opts)

if __name__ == "__main__":
    in_dim = 2
    out_dim = 1
    depth_dim = [3]
    batch_size = 3

    X = np.array([
        [1.0, 2.0],   # 1 + 2 = 3
        [3.0, 4.0],   # 3 + 4 = 7
        [5.0, 6.0]    # 5 + 6 = 11
    ])

    Y = np.array([
        [4],
        [144],
        [900]
    ])

    nn = NeuralNet(in_dim, out_dim, batch_size, depth_dim)
    # print(nn.depth)
    nn.train(X, Y)
    print(nn.forward(X))
    print(Y)