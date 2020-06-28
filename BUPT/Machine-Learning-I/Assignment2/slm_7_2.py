import matplotlib.pyplot as plt
import numpy as np
from sklearn import svm

if __name__ == '__main__':
    x = np.array([[1, 2], [2, 3], [3, 3], [2, 1], [3, 2]])
    y = np.array([1, 1, 1, -1, -1])
    clf = svm.SVC(kernel='linear', C=10)
    clf.fit(x, y)

    print('w1: ' + str(clf.coef_[0][0]))
    print('w2: ' + str(clf.coef_[0][1]))
    print('b: ' + str(clf.intercept_[0]))

    x1 = np.linspace(0, 4)
    w = clf.coef_[0]
    a = -w[0] / w[1]
    x2_sep = a * x1 - clf.intercept_[0] / w[1]
    b = clf.support_vectors_[0]
    x2_margin1 = a * x1 + (b[1] - a * b[0])
    b = clf.support_vectors_[-1]
    x2_margin2 = a * x1 + (b[1] - a * b[0])

    plt.figure(figsize=(4, 4))
    plt.plot(x1, x2_sep, label='Separating hyperplane')
    plt.plot(x1, x2_margin1, 'k--', label='Margin boundary')
    plt.plot(x1, x2_margin2, 'k--')
    plt.scatter(x[:, 0], x[:, 1], c=y)
    plt.scatter(clf.support_vectors_[:, 0], clf.support_vectors_[:, 1], s=150, facecolors='none', edgecolors='k',
                label='Support vectors')
    plt.xlim(0, 4)
    plt.ylim(0, 4)
    plt.legend()
    plt.savefig('fig.jpg')
    plt.show()
