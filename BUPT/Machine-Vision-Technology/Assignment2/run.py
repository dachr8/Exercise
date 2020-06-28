from Assignment2.SceneClassifier import SceneClassifier
from Assignment2.SceneDataset import SceneDataset

if __name__ == "__main__":
    dataset = SceneDataset()
    files, labels, categories = dataset.load_dataset()
    train_files, test_files, train_labels, test_labels = dataset.train_test_split()

    classifier = SceneClassifier()
    classifier.train(train_files, train_labels, k=400)
    # classifier.evaluate(train_files, train_labels)
    classifier.evaluate(test_files, test_labels)

    """
    for i, cat in enumerate(categories):
        print("{0}: {1}".format(i, cat))
    """
