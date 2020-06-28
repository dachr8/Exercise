# coding: utf-8
import os

import cv2
import joblib
import numpy as np
from scipy.cluster.vq import vq
from sklearn import preprocessing


def search(img_name, limit=10):
    # Load classifier, class name, scaler, cluster number and vocabulary
    im_features, image_paths, idf, k, voc = joblib.load("features.pkl")

    # Create feature extraction and key point detector objects
    detector = cv2.xfeatures2d.SURF_create()

    # A list storing all descriptors
    descriptors_list = []

    img_path = os.path.join(os.path.dirname(__file__), 'static/images/' + img_name)
    im = cv2.imread(img_path)
    if im is not None:
        gray1 = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

        descriptor = detector.detectAndCompute(gray1, None)[1]

        descriptors_list.append((img_path, descriptor))

        # Stack all descriptors vertically in a NUMPY array
        descriptors = descriptors_list[0][1]

        # TF-IDF vectorization and L2 normalization
        test_features = np.zeros((1, k), "float32")
        for word in vq(descriptors, voc)[0]:
            test_features[0][word] += 1
        test_features = test_features * idf
        test_features = preprocessing.normalize(test_features, norm='l2')

        score = np.dot(test_features, im_features.T).T[:, 0]
        if limit:
            rank = np.argsort(-score)[:limit]
            score = np.sort(score)[::-1][:limit]
        else:
            rank = np.argsort(-score)
            score = np.sort(score)[::-1]

        rank_list = []
        for i, name in enumerate(rank):
            rank_list.append({"image": image_paths[name].split('\\')[1], "score": str(score[i])})

        return rank_list
    else:
        print("[ERROR] Img Path: ", img_path)
        return
