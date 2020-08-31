import numpy as np
import matplotlib.pyplot as plt
import heapq
import time
from scipy.spatial.distance import norm


class Node:
    def __init__(self, data, sp=0, left=None, right=None):
        self.data = data
        self.sp = sp  # 用来确定分割数据的是第几维
        self.left = left
        self.right = right


class Temp:
    def __init__(self, key, index):
        self.key = key
        self.index = index

    def __lt__(self, other):
        return self.key < other.key


class KDTree:
    def __init__(self, data):
        assert isinstance(data, np.ndarray)
        self.data = data
        self.k = data.shape[1]
        self.n = data.shape[0]
        self.root = self.create(np.arange(self.n), sp=0)

    def create(self, data_index, sp):
        if (len(data_index) == 0):
            return None
        if (sp == self.k):
            sp = 0
        index = sorted(data_index, key=lambda x: self.data[x, sp])
        mid = len(index) // 2  # 取中位数，分布均匀
        left = self.create(index[:mid], sp + 1)
        right = self.create(index[mid + 1:], sp + 1)
        return Node(data=index[mid], left=left, right=right, sp=sp)

    def k_neighbers(self, x, k=1):
        self.neighbors = [Temp(-np.inf, None)] * k
        # 默认是小顶堆，需要大顶堆，所以给key取负号，顶部是距离最远的点
        self.visit(self.root, x)
        return np.array([self.data[e.index] for e in heapq.nlargest(k, self.neighbors)])

    def visit(self, node, x):
        if (node is None):
            return
        dis = x[node.sp] - self.data[node.data, node.sp]
        if (dis > 0):
            self.visit(node.right, x)
        else:
            self.visit(node.left, x)

        if (dis > -self.neighbors[0].key):  # 剪枝
            return

        # 如果node上的数据点能进knn，就进knn
        dis0 = -norm(self.data[node.data] - x)

        if (dis0 > self.neighbors[0].key):  # 大家都是负数 大说明绝对值小，即更近，有资格进knn
            heapq.heappushpop(self.neighbors, Temp(dis0, node.data))

        # visit node的另一边区域
        if (dis > 0):
            self.visit(node.left, x)
        else:
            self.visit(node.right, x)


if __name__ == '__main__':
    start = time.time()
    X = np.array(np.loadtxt('CA/real.txt', usecols=(6, 7)))
    plt.scatter(X[:, 0], X[:, 1], marker='*')
    n_features = 2
    k = 10
    x = X[0]
    kdtree = KDTree(data=X)
    ans = kdtree.k_neighbers(x, k=k)
    print(ans)
    plt.scatter(ans[:, 0], ans[:, 1], marker='*', color='red')
    plt.scatter(x[0], x[1], marker='*', color='palegreen')
    # ans2 = np.array(sorted(X, key=lambda y: norm(x - y))[:k])
    # print((ans1 == ans2).all())
    end = time.time()
    print("程序运行时间：", end-start, "s")
    plt.show()
