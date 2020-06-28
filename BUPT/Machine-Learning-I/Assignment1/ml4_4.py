# 机器学习 4.4 试编程实现基于基尼系数进行划分选择的决策树算法，并为表4.2中数据生成预剪枝、后剪枝决策树，并于未剪枝决策树进行比较。

from DecisionTreeNode import DecisionTreeNode
from MyDataSet import MyDataSet


def CART_tree(data, feature_names, target, test_data=None, test_target=None):
    """
    Generate a CART decision tree
    :param data: Data set, each sample is a dict (property name: attribute value), the entire data is a large list
    :param feature_names: The name of each attribute, such as color, sugar content, etc.
    :param target: Stored in the category of each sample
    :param test_data: Test data set for pre-pruning
    :param test_target: Test data set label for pre-pruning
    :return root_node:
    """

    DecisionTreeNode.current_index = 0
    root_node = DecisionTreeNode(data_index=range(len(data)), rest_attribute=feature_names.copy())
    root_node.fit(data, target, partition_attr='gini_index', test_data=test_data, test_target=test_target)

    return root_node


if __name__ == '__main__':
    watermelon = MyDataSet()
    watermelon.load_watermelon2()

    # Process data structure first
    watermelon_target = list(watermelon.target_names[watermelon.target])
    watermelon_test_target = list(watermelon.target_names[watermelon.test_target])

    train_data = []
    for melon in watermelon.data:
        a_dict = {}
        for i in range(len(melon)):
            a_dict[watermelon.feature_names[i]] = melon[i]
        train_data.append(a_dict)

    test_data = []
    for melon in watermelon.test:
        a_dict = {}
        for i in range(len(melon)):
            a_dict[watermelon.feature_names[i]] = melon[i]
        test_data.append(a_dict)

    decision_tree = CART_tree(train_data, watermelon.feature_names, watermelon_target)
    print('未剪枝决策树:')
    decision_tree.print()
    print('未剪枝决策树在测试数据集上的分类正确率为：' + str(
        decision_tree.accuracy(test_data, watermelon_test_target) * 100)[:5] + "%\n\n")

    decision_tree.post_pruning(test_data, watermelon_test_target, watermelon_target)
    print('后剪枝决策树:')
    decision_tree.print()
    print('后剪枝决策树在测试数据集上的分类正确率为：' + str(
        decision_tree.accuracy(test_data, watermelon_test_target) * 100)[:5] + "%\n\n")

    pre_pruning_decision_tree = CART_tree(train_data,
                                          watermelon.feature_names,
                                          watermelon_target,
                                          test_data,
                                          watermelon_test_target)
    print('预剪枝决策树:')
    pre_pruning_decision_tree.print()
    print('预剪枝决策树在测试数据集上的分类正确率为：' + str(
        pre_pruning_decision_tree.accuracy(test_data, watermelon_test_target) * 100)[:5] + "%")
