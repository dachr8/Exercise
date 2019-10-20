# 机器学习 4.3 试编程实现基于信息熵进行划分选择的决策树算法，并为表4.3中数据生成一颗决策树。

from DecisionTreeNode import DecisionTreeNode


def watermelon3():
    """
    Create a test data set with continuous values in the values
    :return data_set:
    :return labels: Feature value list
    """

    data_set = [['青绿', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.697, 0.460, '是'],
                ['乌黑', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', 0.774, 0.376, '是'],
                ['乌黑', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.634, 0.264, '是'],
                ['青绿', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', 0.608, 0.318, '是'],
                ['浅白', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.556, 0.215, '是'],
                ['青绿', '稍蜷', '浊响', '清晰', '稍凹', '软粘', 0.403, 0.237, '是'],
                ['乌黑', '稍蜷', '浊响', '稍糊', '稍凹', '软粘', 0.481, 0.149, '是'],
                ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '硬滑', 0.437, 0.211, '是'],
                ['乌黑', '稍蜷', '沉闷', '稍糊', '稍凹', '硬滑', 0.666, 0.091, '否'],
                ['青绿', '硬挺', '清脆', '清晰', '平坦', '软粘', 0.243, 0.267, '否'],
                ['浅白', '硬挺', '清脆', '模糊', '平坦', '硬滑', 0.245, 0.057, '否'],
                ['浅白', '蜷缩', '浊响', '模糊', '平坦', '软粘', 0.343, 0.099, '否'],
                ['青绿', '稍蜷', '浊响', '稍糊', '凹陷', '硬滑', 0.639, 0.161, '否'],
                ['浅白', '稍蜷', '沉闷', '稍糊', '凹陷', '硬滑', 0.657, 0.198, '否'],
                ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '软粘', 0.360, 0.370, '否'],
                ['浅白', '蜷缩', '浊响', '模糊', '平坦', '硬滑', 0.593, 0.042, '否'],
                ['青绿', '蜷缩', '沉闷', '稍糊', '稍凹', '硬滑', 0.719, 0.103, '否']]
    labels = ['色泽', '根蒂', '敲击', '纹理', '脐部', '触感', '密度', '含糖率']

    return data_set, labels


def ID3_tree(data, name, label, test_data=None, test_label=None):
    """
    The ID3 method constructs a decision tree using the information gain (information entropy)
    :param data: Data set, each sample is a dictionary (property name: attribute value), the entire data is a large list
    :param name: The name of each attribute
    :param label: Stored in the category of each sample
    :return root_node:
    """
    DecisionTreeNode.current_index = 0
    root_node = DecisionTreeNode(data_index=range(len(data)), rest_attribute=name.copy())
    root_node.fit(data, label, partition_attr='gain', test_data=test_data, test_label=test_label)

    return root_node


if __name__ == '__main__':
    watermelon, names = watermelon3()

    # Process data structure first
    data = []  # Store data
    label = []  # Storage label
    for melon in watermelon:
        a_dict = {}
        dim = len(melon) - 1
        for i in range(dim):
            a_dict[names[i]] = melon[i]
        data.append(a_dict)
        label.append(melon[dim])
    decision_tree = ID3_tree(data, names, label)
    decision_tree.print()
