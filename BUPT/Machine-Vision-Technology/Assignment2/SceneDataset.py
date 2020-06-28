from os import listdir
from os.path import isdir, join

import numpy as np


class SceneDataset:
    def __init__(self, path='scene_categories'):
        self.path = path
        self.filenames = None
        self.labels = None
        self.categories = None

    def load_dataset(self, path=None):
        """
        Loads the scene_categories dataset from the path.
        The scene_categories dataset contains 15 categories (folder name is the category name).
        :param path: path of scene_categories dataset for loading the data
        :return:
        """
        if path:
            self.path = path
        self.categories = [f for f in listdir(self.path) if isdir(join(self.path, f))]
        self.filenames = []
        self.labels = []

        for i, cat in enumerate(self.categories):
            c_files = [join(join(self.path, cat), f) for f in listdir(join(self.path, cat))]
            self.filenames.extend(c_files)
            self.labels.extend([i for _ in c_files])
        self.filenames = np.asarray(self.filenames)
        self.labels = np.asarray(self.labels)
        self.categories = np.asarray(self.categories)
        return self.filenames, self.labels, self.categories

    def train_test_split(self, n_train=150):
        """
        The first 150 samples in each class are used as training samples.
        There are a total of 2250 training samples in 15 classes, and the remaining samples constitute the test set.
        :param n_train: number of train data per class (default 150)
        :return:
        """

        # Get splits
        train_files = []
        train_labels = []
        test_files = []
        test_labels = []

        for i in range(self.labels.max() + 1):
            train_files.extend(self.filenames[self.labels == i][:n_train])
            train_labels.extend(self.labels[self.labels == i][:n_train])
            test_files.extend(self.filenames[self.labels == i][n_train:-1])  # Without Thumbs.db
            test_labels.extend(self.labels[self.labels == i][n_train:-1])  # Without Thumbs.db

        return np.asarray(train_files), np.asarray(test_files), np.asarray(train_labels), np.asarray(test_labels)
