# 机器学习 8.3
# 从网上下载或自己编程实现AdaBoost，以不减枝决策树为基学习器，在西瓜数据集3.0a上训练一个AdaBoost集成，并于图8.4进行比较。
# 西瓜数据集3.0a中密度、含糖率任选一列数据。

import matplotlib.pyplot as plt
import numpy as np
from numpy import linspace


def calErr(dataset, feature, threshold, unequal, D):
    """
    Calculate the weighted error rate of the data.
    @param dataset: [density, sugar content, good melon]
    @param feature: [density, sugar content]
    @param threshold:
    @param unequal: 'lt' or 'gt. (greater than or less than)
    @param D: The weight of the data. Misclassified data will have a large weight.
    @return: error rate.
    """
    d_flatten = D.flatten()  # Becomes one-dimensional
    err_cnt = 0
    i = 0
    if unequal == 'lt':  # If it is considered to be below the threshold
        for data in dataset:  # Then the wrong judgment = below the threshold and is a bad melon + above the threshold and is a good melon
            if (data[feature] <= threshold and data[-1] == -1) or (data[feature] > threshold and data[-1] == 1):
                err_cnt += d_flatten[i]  # The weight of this sample as the error rate
            i += 1
    else:
        for data in dataset:
            if (data[feature] >= threshold and data[-1] == -1) or (data[feature] < threshold and data[-1] == 1):
                err_cnt += d_flatten[i]
            i += 1
    return err_cnt


def buildStump(dataset, D):
    """
    With weighted data, a decision stump with the lowest error rate is established.
    @param dataset:
    @param D:
    @return: Contains information about established decision stumps, such as feature, threshold, unequal, and err.
    """
    m, n = dataset.shape
    best_err = np.inf
    best_stump = {}
    num_steps = 16.0  # Number of steps per feature iteration
    for i in range(n - 1):  # For the i-th feature
        range_min = dataset[:, i].min()  # Minimum value of each attribute column
        range_max = dataset[:, i].max()  # Maximum value of each attribute column
        step_size = (range_max - range_min) / num_steps  # The length of each step
        for j in range(m):  # For j-th data
            threshold = range_min + float(j) * step_size  # Threshold divided by each step
            for unequal in ['lt', 'gt']:  # For greater than or equal to sign division
                err = calErr(dataset, i, threshold, unequal, D)  # Error rate
                if err < best_err:  # If the error rate is lower, save the partition information
                    best_err = err
                    best_stump["feature"] = i
                    best_stump["threshold"] = threshold
                    best_stump["unequal"] = unequal
                    best_stump["err"] = err
    return best_stump


def predict(data, best_stump):
    """
    Predicting data through decision stumps
    @param data: Data to be predicted
    @param best_stump: Decision stump
    @return:
    """
    if (best_stump["unequal"] == 'lt' and data[best_stump["feature"]] <= best_stump["threshold"]) or (
            best_stump["unequal"] == 'gt' and data[best_stump["feature"]] >= best_stump["threshold"]):
        return 1
    else:
        return -1


def AdaBoost(dataset, T):
    """
    Each time a learner is learned, two things are determined based on its error rate.
    1. Determine the weight of the learner in the total learner. The higher the accuracy, the greater the weight.
    2. Adjust the weight of the training samples. The data misclassified by the learner raises the weight and reduces the weight correctly,
       The goal is to focus on the misclassified data in the next round to get better results.
    @param dataset: data set.
    @param T: Number of iterations, ie how many classifiers are trained.
    @return: A dictionary containing T classifiers.
    """
    m, n = dataset.shape
    D = np.ones((1, m)) / m  # Initialization weight. The initial weight of each sample is the same.
    class_label = dataset[:, -1].reshape(1, -1)  # The class label of the data.
    G = {}  # A dictionary that holds the classifier.

    for t in range(T):
        stump = buildStump(dataset, D)  # Build a decision stump based on sample weight D
        err = stump["err"]
        alpha = np.log((1 - err) / err) / 2  # Weight of the t-th classifier
        # Update the weight distribution of the training dataset
        pre = np.zeros((1, m))
        for i in range(m):
            pre[0][i] = predict(dataset[i], stump)
        a = np.exp(-alpha * class_label * pre)
        D = D * a / np.dot(D, a.T)
        G[t] = {}
        G[t]["alpha"] = alpha
        G[t]["stump"] = stump
    return G


def AdaPredict(data, G):
    """
    Classification is performed by the total classifier obtained by AdaBoost.
    @param data: Data to be classified
    @param G: Dictionary containing multiple decision stumps
    @return: Predictive value
    """
    score = 0
    for key in G.keys():
        score += G[key]["alpha"] * predict(data, G[key]["stump"])  # Weighted combined ensemble prediction results
    if score > 0:
        return 1
    else:
        return -1


def calAcc(dataset, G):
    """
    Calculate the accuracy
    @param dataset: data set
    @param G: Dictionary containing multiple decision stumps
    @return: the accuracy
    """
    right_cnt = 0
    for data in dataset:
        if AdaPredict(data, G) == data[-1]:
            right_cnt += 1
    return right_cnt / float(len(dataset))


def plotData(data, clf):
    """
    Plot the data set
    @param data: data set
    @param clf: the integrated learner obtained
    @return:
    """
    x1, x2 = [], []
    y1, y2 = [], []
    for xy, label in zip(data, data[:, 2]):
        if label > 0:
            x1.append(xy[0])
            y1.append(xy[1])
        else:
            x2.append(xy[0])
            y2.append(xy[1])

    x = linspace(0.2, 0.8, 100)
    y = linspace(0, 0.5, 100)

    for key in clf.keys():
        z = [clf[key]["stump"]["threshold"]] * 100
        if clf[key]["stump"]["feature"] == 0:
            plt.plot(z, y, 'k')
        else:
            plt.plot(x, z, 'k')

    plt.scatter(x1, y1, marker='+', label='好瓜')
    plt.scatter(x2, y2, marker='_', label='坏瓜')
    plt.rcParams['font.sans-serif'] = ['SimHei']  # Used to display Chinese labels normally
    plt.xlabel('密度')
    plt.ylabel('含糖率')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    # Watermelon dataset 3.0 alpha Column: [Density, sugar content, good melon]
    watermelon3a = np.array([[0.697, 0.460, 1],
                             [0.774, 0.376, 1],
                             [0.634, 0.264, 1],
                             [0.608, 0.318, 1],
                             [0.556, 0.215, 1],
                             [0.403, 0.237, 1],
                             [0.481, 0.149, 1],
                             [0.437, 0.211, 1],
                             [0.666, 0.091, -1],
                             [0.243, 0.267, -1],
                             [0.245, 0.057, -1],
                             [0.343, 0.099, -1],
                             [0.639, 0.161, -1],
                             [0.657, 0.198, -1],
                             [0.360, 0.370, -1],
                             [0.593, 0.042, -1],
                             [0.719, 0.103, -1]])
    for t in [3, 5, 11]:  # Number of learners
        G = AdaBoost(watermelon3a, t)
        print(str(t) + "个基学习器集成的准确率 = " + str(calAcc(watermelon3a, G)))
        # Plot the data set
        plotData(watermelon3a, G)
