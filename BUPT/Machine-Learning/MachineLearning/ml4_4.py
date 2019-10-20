# 机器学习 4.4 试编程实现基于基尼系数进行划分选择的决策树算法，并为表4.2中数据生成预剪枝、后剪枝决策树，并于未剪枝决策树进行比较。

from DecisionTreeNode import DecisionTreeNode
from ml4_3 import ID3_tree

def watermelon2():
    """
    Create a test data set with continuous values in the values
    :return train_set:
    :return test_set:
    :return labels: Feature value list
    """

    train_set = [['青绿', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', '是'],
                 ['乌黑', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', '是'],
                 ['乌黑', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', '是'],
                 ['青绿', '稍蜷', '浊响', '清晰', '稍凹', '软粘', '是'],
                 ['乌黑', '稍蜷', '浊响', '稍糊', '稍凹', '软粘', '是'],
                 ['青绿', '硬挺', '清脆', '清晰', '平坦', '软粘', '否'],
                 ['浅白', '稍蜷', '沉闷', '稍糊', '凹陷', '硬滑', '否'],
                 ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '软粘', '否'],
                 ['浅白', '蜷缩', '浊响', '模糊', '平坦', '硬滑', '否'],
                 ['青绿', '蜷缩', '沉闷', '稍糊', '稍凹', '硬滑', '否']]
    test_set = [['青绿', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', '是'],
                ['浅白', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', '是'],
                ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '硬滑', '是'],
                ['乌黑', '稍蜷', '沉闷', '稍糊', '稍凹', '硬滑', '否'],
                ['浅白', '硬挺', '清脆', '模糊', '平坦', '硬滑', '否'],
                ['浅白', '蜷缩', '浊响', '模糊', '平坦', '软粘', '否'],
                ['青绿', '稍蜷', '浊响', '稍糊', '凹陷', '硬滑', '否']]
    labels = ['色泽', '根蒂', '敲击', '纹理', '脐部', '触感']

    return train_set, test_set, labels


def CART_tree(data, attr, label, test_data=None, test_label=None):
    """
    Generate a CART decision tree
    :param data: Data set, each sample is a dict (property name: attribute value), the entire data is a large list
    :param attr: The name of each attribute, such as color, sugar content, etc.
    :param label: Stored in the category of each sample
    :param test_data: Test data set for pre-pruning
    :param test_label: Test data set label for pre-pruning
    :return root_node:
    """

    DecisionTreeNode.current_index = 0
    root_node = DecisionTreeNode(data_index=range(len(data)), rest_attribute=attr.copy())
    root_node.fit(data, label, partition_attr='gini_index', test_data=test_data, test_label=test_label)

    return root_node


if __name__ == '__main__':
    train_watermelon, test_watermelon, labels = watermelon2()

    # 先处理数据
    train_data = []
    train_label = []
    for melon in train_watermelon:
        a_dict = {}
        dim = len(melon) - 1
        for i in range(dim):
            a_dict[labels[i]] = melon[i]
        train_data.append(a_dict)
        train_label.append(melon[dim])

    test_data = []
    test_label = []
    for melon in test_watermelon:
        a_dict = {}
        dim = len(melon) - 1
        for i in range(dim):
            a_dict[labels[i]] = melon[i]
        test_data.append(a_dict)
        test_label.append(melon[dim])

    decision_tree = CART_tree(train_data, labels, train_label)
    print('未剪枝决策树:')
    decision_tree.print()
    print('未剪枝决策树在测试数据集上的分类正确率为：' + str(decision_tree.accuracy(test_data, test_label) * 100)[:5] + "%")

    print('\n')

    decision_tree.post_pruning(test_data, test_label, train_label)
    print('后剪枝决策树:')
    decision_tree.print()
    print('后剪枝决策树在测试数据集上的分类正确率为：' + str(decision_tree.accuracy(test_data, test_label) * 100)[:5] + "%")

    print('\n')

    pre_pruning_decision_tree = CART_tree(train_data, labels, train_label, test_data, test_label)
    print('预剪枝决策树:')
    pre_pruning_decision_tree.print()
    print('预剪枝决策树在测试数据集上的分类正确率为：' + str(pre_pruning_decision_tree.accuracy(test_data, test_label) * 100)[:5] + "%")
