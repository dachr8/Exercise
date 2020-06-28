from sklearn import svm, datasets, model_selection


# 选择两个UCI数据集，分别用线性核和高斯核训练一个SVM，与C4.5决策树进行实验比较

def run_6_3(dataset, kernel='linear'):
    x_train, x_test, y_train, y_test = model_selection.train_test_split(dataset.data,
                                                                        dataset.target,
                                                                        test_size=0.3,
                                                                        random_state=1)  # 70% training and 30% test
    clf = svm.SVC(kernel=kernel, gamma='auto')
    clf.fit(x_train, y_train)
    print(kernel + '-SVM score: ' + str(clf.score(x_test, y_test)))
    print("The number of support vectors is: ", clf.n_support_)


if __name__ == '__main__':
    iris = datasets.load_iris()
    wine = datasets.load_wine()

    print('iris')
    run_6_3(iris)
    run_6_3(iris, 'rbf')
    print('----------------------------------------------------------------')
    print('wine')
    run_6_3(wine)
    run_6_3(wine, 'rbf')
