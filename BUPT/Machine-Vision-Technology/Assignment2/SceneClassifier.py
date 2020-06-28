import cv2
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from progressbar import *
from sklearn.metrics import confusion_matrix, f1_score, accuracy_score


class SceneClassifier:
    def __init__(self):
        # Create two SIFT instances, one to extract key points and one to extract features
        self.detector = cv2.xfeatures2d.SURF_create()  # SURF is better than SIFT
        self.extractor = cv2.xfeatures2d.SURF_create()  # SURF is better than SIFT
        # Define SIFT feature matching algorithm, use FLANN matcher or BF matcher
        matcher = cv2.BFMatcher()  # or matcher = cv2.FlannBasedMatcher(dict(algorithm=1, trees=5), {})
        # Initialize the BOW extractor
        self.bow_extractor = cv2.BOWImgDescriptorExtractor(self.extractor, matcher)
        # Create SVM
        self.svm = cv2.ml.SVM_create()  # cv2.ml svm
        self.svm.setC(100)
        # self.svm = svm.SVC(decision_function_shape='ovo')  # sklearn svm
        return

    def sift_descriptor(self, filename):
        """
        Get descriptor
        :param filename:
        :return: Descriptor
        """
        im = cv2.imread(filename, 0)
        return self.detector.detectAndCompute(im, None)[1]

    def bow_descriptor(self, filename):
        """
        Get descriptor
        :param filename:
        :return: The descriptor calculated by the BOW-based descriptor extractor
        """
        im = cv2.imread(filename, 0)
        return self.bow_extractor.compute(im, self.detector.detect(im))

    def train(self, train_files, train_labels, k=33):
        """
        Train
        :param train_files:
        :param train_labels:
        :param k: 33 or 34 or bigger? (better)
        """
        # Create a BOW trainer
        print("Training with", len(train_files), "files")

        # criteria indicates the mode of iteration stop
        # eps --- precision 0.1
        # max_iter --- meet more than the maximum number of iterations 20
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 20, 0.1)
        # argument k for k-means
        bow_trainer = cv2.BOWKMeansTrainer(clusterCount=k)

        bar_widgets = ['SIFT Progress: ', Percentage(), '\t', Bar('#'), '\t', Timer(), '\t', ETA()]
        bar = ProgressBar(widgets=bar_widgets, maxval=len(train_files)).start()
        for i in range(len(train_files)):
            bow_trainer.add(self.sift_descriptor(train_files[i]))
            bar.update(i)
        bar.finish()

        print("K-means cluster descriptors to vocabulary...")
        vocab = bow_trainer.cluster()
        print("K-means Done!")
        self.bow_extractor.setVocabulary(vocab)

        bar_widgets = ['BOW Progress: ', Percentage(), '\t', Bar('#'), '\t', Timer(), '\t', ETA()]
        bar = ProgressBar(widgets=bar_widgets, maxval=len(train_files)).start()
        train_bow = []
        for i, img in enumerate(train_files):
            train_bow.extend(self.bow_descriptor(img))
            bar.update(i)
        bar.finish()

        # Use SVM for training
        print("Training SVM...")
        self.svm.train(np.asarray(train_bow), cv2.ml.ROW_SAMPLE, train_labels)  # cv2.ml svm
        # self.svm.fit(np.asarray(train_bow), train_labels)  # sklearn svm

        print("Scene Classifier Training Done!")

    def predict(self, test_files):
        """
        Prediction function
        :param test_files:
        :return:
        """
        print("Predicting with", len(test_files), "files")
        bar_widgets = ['Predict Progress: ', Percentage(), '\t', Bar('#'), '\t', Timer(), '\t', ETA()]
        bar = ProgressBar(widgets=bar_widgets, maxval=len(test_files)).start()
        predicts = []
        for i, img in enumerate(test_files):
            predicts.append(int(self.svm.predict(self.bow_descriptor(img))[1][0][0]))  # cv2.ml svm
            # predicts.append(self.svm.predict(self.bow_descriptor(img)))  # sklearn svm
            bar.update(i)
        bar.finish()
        return np.asarray(predicts)

    def evaluate(self, test_files, test_labels):
        """
        Prediction function
        :param test_files:
        :param test_labels:
        :return: Confusion matrix
        """
        y_true = test_labels
        y_pred = self.predict(test_files)
        matrix = confusion_matrix(y_true, y_pred)
        matrix_normalized = matrix.astype('float') / matrix.sum(axis=1)[:, np.newaxis]

        f, ax = plt.subplots(figsize=(9, 9))
        sns.heatmap(matrix_normalized, annot=True, fmt='.2f', ax=ax)
        plt.ylabel('True label')
        plt.xlabel('Predicted label')
        plt.show()

        # F1-Score: macro or weighted or micro or samples
        print('Accuracy Score: %.9f' % accuracy_score(y_true=y_true, y_pred=y_pred))
        print('F1-Score(macro): %.9f' % f1_score(y_true=y_true, y_pred=y_pred, average="macro"))
        print('F1-Score(weighted): %.9f' % f1_score(y_true=y_true, y_pred=y_pred, average="weighted"))
        print('F1-Score(micro): %.9f' % f1_score(y_true=y_true, y_pred=y_pred, average="micro"))

        return matrix
