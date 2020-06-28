import math


class DecisionTreeNode:
    """
    Decision tree node class
    """

    current_index = 0

    def __init__(self,
                 parent=None,
                 attr_name=None,
                 attr_value=None,
                 children=None,
                 judge=None,
                 split=None,
                 data_index=None,
                 rest_attribute=None):
        """
        Decision tree node class initialization method
        :param parent: Parent node, the parent node of the root node is None
        :param attr_name: The attribute name to be divided on this node
        :param attr_value: The value of the attribute attributed on this node is corresponding to the division attribute name of the parent node.
        :param children: Child node list
        :param judge: If it is a leaf node, you need to give a judgment
        :param split: If you use continuous attributes for partitioning, you need to give a split point.
        :param data_index: Training index number corresponding to the training data set
        :param rest_attribute: List of attributes not yet used
        """
        self.parent = parent
        self.attribute_name = attr_name
        self.attribute_value = attr_value
        self.children = children
        self.judge = judge
        self.split = split
        self.data_index = data_index
        self.index = DecisionTreeNode.current_index
        self.rest_attribute = rest_attribute
        DecisionTreeNode.current_index += 1

    @property
    def to_string(self):
        """
        Use a string to describe the current node information
        :return:
        """

        this_string = ''
        if self.parent:
            parent_node = self.parent
            parent_nodes = []
            while parent_node:
                parent_nodes.append(parent_node.index)
                parent_node = parent_node.parent
            parent_nodes.reverse()
            for i in parent_nodes:
                this_string += '结点' + str(i) + ' -> '
        this_string += '结点' + str(self.index)
        if self.parent:
            this_string += '\t' + self.parent.attribute_name + '：' + self.attribute_value

        if self.judge:
            this_string += '\n类： ' + str(self.judge)
        if self.children:
            child_list = []
            for child in self.children:
                child_list.append(child.index)
            this_string += '\n划分属性: ' + str(self.attribute_name) + ' -> 结点' + str(child_list)

        return this_string

    def print(self):
        """
        Print out a tree
        :return:
        """
        node_list = [self]
        while len(node_list) > 0:
            current_node = node_list[0]
            print(current_node.to_string)
            print('--------------------------------')
            children_list = current_node.children
            if children_list:
                for child in children_list:
                    node_list.append(child)
            node_list.remove(current_node)

    def fit(self, data, target, partition_attr='gain', test_data=None, test_target=None):
        """
        Complete subsequent calculations of the current node, including selecting attributes, dividing child nodes, etc.
        :param data: Data set
        :param target: Label of the data set
        :param partition_attr: gain or gini_index
        :param test_data: Test data set for pre-pruning
        :param test_target: Test data set label for pre-pruning
        :return:
        """

        # Determine whether the data of the current node belongs to the same class,
        # and if so, directly mark it as a leaf node and return
        one_class = True
        this_data_index = self.data_index
        for i in this_data_index:
            for j in this_data_index:
                if target[i] != target[j]:
                    one_class = False
        if one_class:
            self.judge = target[this_data_index[0]]
            return

        rest_attr = self.rest_attribute  # Candidate attribute
        if len(rest_attr) == 0:
            # If the candidate attribute is empty, it is a leaf node.
            # The class that needs to select the most as the class of the node.
            label_count = {}
            for index in self.data_index:
                if label_count.__contains__(target[index]):
                    label_count[target[index]] += 1
                else:
                    label_count[target[index]] = 1
            final_label = max(label_count)
            self.judge = final_label
            return

        if test_data and test_target:
            # First add a temporary judgment for the current node. If you need to add a child node, then restore it to None.
            data_count = {}
            for index in self.data_index:
                if data_count.__contains__(target[index]):
                    data_count[target[index]] += 1
                else:
                    data_count[target[index]] = 1
            before_judge = max(data_count, key=data_count.get)
            self.judge = before_judge
            before_accuracy = self.accuracy(test_data, test_target)

        attr_value = {}  # Record the information gain or Gini index for each attribute
        attr_split_value = {}  # Record the separation value of each attribute,
        # if it is a continuous attribute, it is a separator value, if it is a discrete attribute, it is None.
        for attr in rest_attr:
            attr_values = []
            current_label = []
            for index in self.data_index:
                attr_values.append(data[index][attr])
                current_label.append(target[index])
            # If the attribute value is a number, it is considered continuous
            if partition_attr == 'gain':
                attr_value[attr], attr_split_value[attr] = gain(attr_values, current_label, is_number(data[0][attr]))
            else:
                attr_value[attr], attr_split_value[attr] = gini_index(attr_values, current_label,
                                                                      is_number(data[0][attr]))

        if partition_attr == 'gain':
            best_attr = max(attr_value, key=attr_value.get)  # The attribute name with the largest information gain
        else:
            best_attr = min(attr_value, key=attr_value.get)  # The smallest property name of the Gini index
        self.attribute_name = best_attr
        self.split = attr_split_value[best_attr]
        rest_attr.remove(best_attr)

        a_data = data[0]
        if is_number(a_data[best_attr]):  # If the value of this attribute is a continuous value
            split_value = attr_split_value[best_attr]
            small_data = []
            large_data = []
            for index in self.data_index:
                this_data = data[index]
                if this_data[best_attr] <= split_value:
                    small_data.append(index)
                else:
                    large_data.append(index)

            small_child = DecisionTreeNode(parent=self,
                                           data_index=small_data,
                                           attr_value='<= ' + str(split_value),
                                           rest_attribute=rest_attr.copy())
            large_child = DecisionTreeNode(parent=self,
                                           data_index=large_data,
                                           attr_value='> ' + str(split_value),
                                           rest_attribute=rest_attr.copy())

            if test_data and test_target:
                small_data_count = {}
                for index in small_child.data_index:
                    if small_data_count.__contains__(target[index]):
                        small_data_count[target[index]] += 1
                    else:
                        small_data_count[target[index]] = 1
                small_child.judge = max(small_data_count, key=small_data_count.get)  # a judgment added temporarily

                large_data_count = {}
                for index in large_child.data_index:
                    if large_data_count.__contains__(target[index]):
                        large_data_count[target[index]] += 1
                    else:
                        large_data_count[target[index]] = 1
                large_child.judge = max(large_data_count, key=large_data_count.get)  # a judgment added temporarily

            self.children = [small_child, large_child]
        else:  # If the value of this attribute is a discrete value
            best_attr_value_dict = {}  # Key is the value of the attribute value,
            # and value is the sample number contained in the list record.
            for index in self.data_index:
                this_data = data[index]
                if best_attr_value_dict.__contains__(this_data[best_attr]):
                    tmp_list = best_attr_value_dict[this_data[best_attr]]
                    tmp_list.append(index)
                else:
                    tmp_list = [index]
                    best_attr_value_dict[this_data[best_attr]] = tmp_list

            children_list = []
            for key, index_list in best_attr_value_dict.items():
                a_child = DecisionTreeNode(parent=self,
                                           data_index=index_list,
                                           attr_value=key,
                                           rest_attribute=rest_attr.copy())

                if test_data and test_target:
                    # Also need to give the child node a judgment first
                    tmp_data_count = {}
                    for index in index_list:
                        if tmp_data_count.__contains__(target[index]):
                            tmp_data_count[target[index]] += 1
                        else:
                            tmp_data_count[target[index]] = 1
                        a_child.judge = max(tmp_data_count, key=tmp_data_count.get)  # a judgment added temporarily

                children_list.append(a_child)
            self.children = children_list

        if test_data and test_target:
            self.judge = None
            if before_accuracy >= self.accuracy(test_data, test_target):
                self.children = None
                self.judge = before_judge
                return

        for child in self.children:  # Recursive
            child.fit(data, target, partition_attr, test_data, test_target)

    def predict(self, sample):
        """
        Use a decision tree to determine the category label of a data sample
        :param sample: Sample to be judged
        :return:
        """

        current_node = self
        while current_node.judge is None:
            if current_node.split is None:  # Discrete attribute
                can_judge = False  # If the training data set is not large enough,
                # there may be attribute values in the test data set that have not appeared in the training data set.
                for child in current_node.children:
                    if child.attribute_value == sample[current_node.attribute_name]:
                        current_node = child
                        can_judge = True
                        break
                if not can_judge:
                    return None
            else:
                child_list = current_node.children
                if sample[current_node.attribute_name] <= current_node.split:
                    current_node = child_list[0]
                else:
                    current_node = child_list[1]

        return current_node.judge

    def accuracy(self, test_data, test_target):
        """
        Calculate the correct rate of the current decision tree on the training data set
        :param test_data: Test data set
        :param test_target: Test data set label
        :return:
        """
        root_node = self
        while root_node.parent:
            root_node = root_node.parent

        accuracy = 0
        for i in range(len(test_target)):
            if root_node.predict(test_data[i]) == test_target[i]:
                accuracy += 1

        return accuracy / len(test_target)

    def post_pruning(self, test_data, test_target, train_target):
        """
        Post-prune operation on the decision tree
        :param test_data: Test data set
        :param test_target: Test data set label
        :param train_target: Train data set label
        :return:
        """
        leaf_father = []  # All children are collections of nodes of leaf nodes

        traversing_list = [self]
        while len(traversing_list) > 0:
            current_node = traversing_list[0]
            children = current_node.children
            wanted = True  # Determine whether the current node meets all the child nodes are leaf nodes
            if children:
                for child in children:
                    traversing_list.append(child)
                    wanted = wanted and (child.children is None)
            else:
                wanted = False

            if wanted:
                leaf_father.append(current_node)
            traversing_list.remove(current_node)

        while len(leaf_father) > 0:
            # If the leaf parent node is empty, the pruning is complete.
            # For the leaf parent node that does not need to be pruned, we also remove it from the leaf_father
            current_node = leaf_father.pop()
            # The correct rate of not pruning on the test set
            before_accuracy = self.accuracy(test_data, test_target)

            label_count = {}
            for index in current_node.data_index:
                if label_count.__contains__(index):
                    label_count[train_target[index]] += 1
                else:
                    label_count[train_target[index]] = 1
            current_node.judge = max(label_count,
                                     key=label_count.get)  # The judgment that should be made if pruning the current node

            if before_accuracy >= self.accuracy(test_data, test_target):  # No pruning
                current_node.judge = None
            else:  # Pruning
                current_node.children = None
                # It is also necessary to check whether it is necessary to judge its parent node.
                parent_node = current_node.parent
                if parent_node:
                    tmp_bool = True
                    for child in parent_node.children:
                        if child.children:
                            tmp_bool = False
                            break
                    if tmp_bool:
                        leaf_father.append(parent_node)


def is_number(s):
    """
    Determine if a string is a number
    :param s:
    :return:
    """

    try:
        float(s)
        return True
    except ValueError:
        pass
    return False


def ent(labels):
    """
    :param labels: Category label for data in the sample collection
    :return entropy: Information entropy of sample sets
    """

    label_name = []
    label_count = []

    for item in labels:
        if item in label_name:
            index = label_name.index(item)
            label_count[index] = label_count[index] + 1
        else:
            label_name.append(item)
            label_count.append(1)

    n = sum(label_count)
    entropy = 0.0
    for item in label_count:
        entropy -= item / n * math.log(item / n, 2)

    return entropy


def gain(attribute, labels, is_value=False):
    """
    Calculate information gain
    :param attribute: List of values for this property in the collection
    :param labels: The data label of the sample in the collection
    :param is_value: Whether the current attribute is a discrete adjective or a continuous value
    :return info_gain: Information gain
    :return split_value: If it is a continuous value, you also need to return the value of the separation limit.
    """

    info_gain = ent(labels)
    n = len(labels)

    if is_value:
        # The attribute value is a continuous value. First, you should use the dichotomy to find the best split point.
        sorted_attribute = attribute.copy()
        sorted_attribute.sort()
        split = []  # Candidate separation point
        for i in range(n - 1):
            split.append((sorted_attribute[i] + sorted_attribute[i + 1]) / 2)
        info_gain_list = []
        for tmp_split in split:
            low_labels = []
            high_labels = []
            for i in range(0, n):
                if attribute[i] <= tmp_split:
                    low_labels.append(labels[i])
                else:
                    high_labels.append(labels[i])
            info_gain_list.append(info_gain
                                  - len(low_labels) / n * ent(low_labels)
                                  - len(high_labels) / n * ent(high_labels))

        info_gain = max(info_gain_list)
        split_value = split[info_gain_list.index(info_gain)]
    else:
        # Attribute values are discrete values
        attribute_dict = {}
        label_dict = {}
        index = 0
        for item in attribute:
            if attribute_dict.__contains__(item):
                attribute_dict[item] = attribute_dict[item] + 1
                label_dict[item].append(labels[index])
            else:
                attribute_dict[item] = 1
                label_dict[item] = [labels[index]]
            index += 1

        for key, value in attribute_dict.items():
            info_gain -= value / n * ent(label_dict[key])
        split_value = None

    return info_gain, split_value


def gini(labels):
    """
    Calculate the Gini value of the data set
    :param labels: Category label for the dataset
    :return gini_value: The Gini value of the data set
    """

    data_count = {}
    for label in labels:
        if data_count.__contains__(label):
            data_count[label] += 1
        else:
            data_count[label] = 1

    n = len(labels)
    if n == 0:
        return 0

    gini_value = 1
    for key, value in data_count.items():
        gini_value -= (value / n) ** 2

    return gini_value


def gini_index_basic(n, attr_labels):
    """
    :param n:
    :param attr_labels:
    :return gini_value:
    """

    gini_value = 0
    for attribute, labels in attr_labels.items():
        gini_value += len(labels) / n * gini(labels)

    return gini_value


def gini_index(attributes, labels, is_value=False):
    """
    Calculate the Gini index of an attribute
    :param attributes: List of attribute values for current data on this attribute
    :param labels:
    :param is_value:
    :return gini_value:
    :return split:
    """

    n = len(labels)
    attr_labels = {}

    if is_value:  # Attribute value is a continuous value
        sorted_attributes = attributes.copy()
        sorted_attributes.sort()
        split_points = []
        for i in range(n - 1):
            split_points.append((sorted_attributes[i + 1] + sorted_attributes[i]) / 2)

        split_evaluation = []
        for current_split in split_points:
            low_labels = []
            up_labels = []
            for i in range(n):
                if attributes[i] <= current_split:
                    low_labels.append(labels[i])
                else:
                    up_labels.append(labels[i])
            attr_labels = {'small': low_labels, 'large': up_labels}
            split_evaluation.append(gini_index_basic(n, attr_labels))

        gini_value = min(split_evaluation)
        split = split_points[split_evaluation.index(gini_value)]

    else:  # Attribute values are discrete words
        for i in range(n):
            if attr_labels.__contains__(attributes[i]):
                tmp_list = attr_labels[attributes[i]]
                tmp_list.append(labels[i])
            else:
                tmp_list = [labels[i]]
                attr_labels[attributes[i]] = tmp_list

        gini_value = gini_index_basic(n, attr_labels)
        split = None

    return gini_value, split
