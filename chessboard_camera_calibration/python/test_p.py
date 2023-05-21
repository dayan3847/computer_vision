import numpy as np

if __name__ == '__main__':
    # matriz = np.array([
    #     [-0.894427, - 0.447214],
    #     [- 0.447214, 0.894427],
    # ])

    matriz = np.array([
        [0.628145, - 0.610863],
        [0.778097, 0.610282],
        [0.000292938, - 0.000312457],
    ])

    # matriz = np.array([
    #     [-0.628145, 0.778097, - 0.000491345],
    #     [-0.778097, -0.628145, 2.01751e-05],
    #     [-0.000292938, 0.000394987, 1],
    # ])

    v0 = matriz[:, 0]
    v1 = matriz[:, 1]

    r = np.dot(v0, v1)
    # cast to float
    r = float(r)
    # redondeo a 4 decimales
    r = round(r, 4)

    print(r)
