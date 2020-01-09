# TODO 机器学习 4.6.sp 试选择2个UCI数据集，对上述2种算法所产生的未剪枝、预剪枝、后剪枝决策树进行实验比较。

from ml4_3 import ID3_tree
from ml4_4 import CART_tree
from sklearn.datasets import load_iris, load_wine
from sklearn.model_selection import train_test_split  # Import train_test_split function


def run_4_6(dataset, criterion):
    x_train, x_test, y_train, y_test = train_test_split(dataset.data,
                                                        dataset.target_names[dataset.target],
                                                        test_size=0.3,
                                                        random_state=1)  # 70% training and 30% test

    # Process data first
    train_target = list(y_train)
    test_target = list(y_test)

    train_data = []
    for melon in x_train:
        a_dict = {}
        dim = len(melon)
        for i in range(dim):
            a_dict[dataset.feature_names[i]] = melon[i]
        train_data.append(a_dict)

    test_data = []
    for melon in x_test:
        a_dict = {}
        dim = len(melon)
        for i in range(dim):
            a_dict[dataset.feature_names[i]] = melon[i]
        test_data.append(a_dict)

    if criterion == 'ID3':
        decision_tree = ID3_tree(train_data, dataset.feature_names, train_target)
    else:
        decision_tree = CART_tree(train_data, dataset.feature_names, train_target)

    print('未剪枝' + criterion + '决策树:')
    decision_tree.print()
    print('未剪枝' + criterion + '决策树在测试数据集上的分类正确率为：' + str(
        decision_tree.accuracy(test_data, test_target) * 100)[:5] + "%\n\n")

    decision_tree.post_pruning(test_data, test_target, train_target)
    print('后剪枝' + criterion + '决策树:')
    decision_tree.print()
    print('后剪枝' + criterion + '决策树在测试数据集上的分类正确率为：' + str(
        decision_tree.accuracy(test_data, test_target) * 100)[:5] + "%\n\n")

    if criterion == 'ID3':
        pre_pruning_decision_tree = ID3_tree(train_data, dataset.feature_names, train_target, test_data, test_target)
    else:
        pre_pruning_decision_tree = CART_tree(train_data, dataset.feature_names, train_target, test_data, test_target)
    print('预剪枝' + criterion + '决策树:')
    pre_pruning_decision_tree.print()
    print('预剪枝' + criterion + '决策树在测试数据集上的分类正确率为：' + str(
        pre_pruning_decision_tree.accuracy(test_data, test_target) * 100)[:5] + "%")


if __name__ == '__main__':
    print('--------------------------------IRIS--------------------------------')
    iris = load_iris()
    print(iris.DESCR)
    run_4_6(iris, 'ID3')
    print('\n')
    run_4_6(iris, 'CART')
    print('\n\n--------------------------------WINE--------------------------------')
    wine = load_wine()
    print(wine.DESCR)
    run_4_6(wine, 'ID3')
    print('\n')
    run_4_6(wine, 'CART')
