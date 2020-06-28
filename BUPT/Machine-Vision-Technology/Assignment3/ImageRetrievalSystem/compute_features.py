# coding: utf-8
import glob

import cv2
import joblib
import numpy as np
from progressbar import *
from scipy.cluster.vq import vq
from sklearn import preprocessing

if __name__ == '__main__':
    image_path = "static/images/*.jpg"

    # The number of words
    k = 200
    bow_trainer = cv2.BOWKMeansTrainer(clusterCount=200)

    # Get the path of all pictures
    image_paths = glob.glob(image_path)

    # Create feature extraction and key point detector objects
    detector = cv2.xfeatures2d.SURF_create()

    # Extract SURF
    bar_widgets = ['Extract SURF Progress: ', Percentage(), '\t', Bar('#'), '\t', Timer(), '\t', ETA()]
    bar = ProgressBar(widgets=bar_widgets, maxval=len(image_paths)).start()
    for i, image_path in enumerate(image_paths):
        im = cv2.imread(image_path)
        gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        bow_trainer.add(detector.detectAndCompute(gray, None)[1])
        bar.update(i)
    bar.finish()

    # Start k-means clustering
    print("K-means cluster descriptors to vocabulary...")
    vocab = bow_trainer.cluster()
    print("K-means Done!")

    # Compute feature histogram
    descriptors_array = np.array(bow_trainer.getDescriptors())
    im_features = np.zeros((len(image_paths), k), "float32")
    bar_widgets = ['Compute Feature Histogram Progress: ', Percentage(), '\t', Bar('#'), '\t', Timer(), '\t', ETA()]
    bar = ProgressBar(widgets=bar_widgets, maxval=len(image_paths)).start()
    for i in range(len(image_paths)):
        for word in vq(descriptors_array[i], vocab)[0]:
            im_features[i][word] += 1
        bar.update(i)
    bar.finish()

    # Tf-Idf Word frequency
    occurrences = np.sum((im_features > 0) * 1, axis=0)
    idf = np.array(np.log((1.0 * len(image_paths) + 1) / (1.0 * occurrences + 1)), 'float32')

    # L2 normalization
    print("L2 Normalize...")
    im_features = im_features * idf
    im_features = preprocessing.normalize(im_features, norm='l2')

    joblib.dump((im_features, image_paths, idf, k, vocab), "features.pkl", compress=3)
    print("Success")
