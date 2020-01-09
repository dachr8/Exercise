# 机器学习 4.3 试编程实现基于信息熵进行划分选择的决策树算法，并为表4.3中数据生成一颗决策树。

from DecisionTreeNode import DecisionTreeNode
from MyDataSet import MyDataSet


def ID3_tree(data, feature_names, target, test_data=None, test_target=None):
    """
    The ID3 method constructs a decision tree using the information gain (information entropy)
    :param data: Data set, each sample is a dictionary (property name: attribute value), the entire data is a large list
    :param feature_names: The name of each attribute
    :param target: Stored in the category of each sample
    :param test_data: Test data set for pre-pruning
    :param test_target: Test data set label for pre-pruning
    :return root_node:
    """

    DecisionTreeNode.current_index = 0
    root_node = DecisionTreeNode(data_index=range(len(data)), rest_attribute=feature_names.copy())
    root_node.fit(data, target, partition_attr='gain', test_data=test_data, test_target=test_target)

    return root_node


if __name__ == '__main__':
    watermelon = MyDataSet()
    watermelon.load_watermelon3()

    # Process data structure first
    watermelon_target = watermelon.target_names[watermelon.target]

    data = []  # Store data
    for melon in watermelon.data:
        a_dict = {}
        for i in range(len(melon)):
            a_dict[watermelon.feature_names[i]] = melon[i]
        data.append(a_dict)
    decision_tree = ID3_tree(data, watermelon.feature_names, watermelon_target)
    decision_tree.print()
