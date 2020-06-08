# encoding: utf-8
import logging
import os
import re

import jieba
from gensim.models import KeyedVectors, word2vec


class ChineseWord2Vec:
    def __init__(self,
                 wiki_path="./zhwiki/BB/",
                 corpus_path="./zhwiki/CC/",
                 corpus_name="wiki_corpus",
                 model_path="./model/",
                 model_name="wiki_corpus_binary.bin"):
        self.wiki_path = wiki_path
        self.corpus_path = corpus_path
        self.corpus_name = corpus_name
        self.model_path = model_path
        self.model_name = model_name

    @staticmethod
    def parse_zhwiki(input_path, output_path):
        """
        Use regular expressions to parse text
        :param input_path:
        :param output_path:
        """
        # Filter out <doc>
        regex_str = "[^<doc.*>$]|[^</doc>$]"
        input_stream = open(input_path, "r", encoding="utf-8")
        output_stream = open(output_path, "w+", encoding="utf-8")
        content_line = input_stream.readline()
        article_contents = ""  # Represents the word segmentation result of an article
        cnt = 0
        while content_line:
            content_line = content_line.strip("\n")
            if len(content_line) > 0:
                if re.match(regex_str, content_line):
                    # Use jieba for word segmentation
                    for word in jieba.cut(content_line, cut_all=False):
                        article_contents += word + " "
                else:
                    if len(article_contents) > 0:
                        output_stream.write(article_contents + "\n")
                        article_contents = ""
            cnt += 1
            if cnt % 10000 == 0:
                print("{0} million rows processed".format(cnt / 1000000))
            content_line = input_stream.readline()
        input_stream.close()
        output_stream.close()

    def parse(self):
        """
        parse
        """
        # wiki data processing
        print("Start regularization, jieba processing data")
        for i in range(len(os.listdir(self.wiki_path))):
            print("Start processing the {0}-th file".format(i))
            sub_wiki_file = os.path.join(self.wiki_path, "wiki_0{0}".format(i))
            sub_corpus_file = os.path.join(self.corpus_path, "{0}0{1}".format(self.corpus_name, i))
            self.parse_zhwiki(sub_wiki_file, sub_corpus_file)

        # File merge
        print("Start merging files")
        if not os.path.isdir(self.corpus_path):
            os.mkdir(self.corpus_path)
        corpus_file = os.path.join(self.corpus_path, self.corpus_name)
        output_stream = open(corpus_file, "w", encoding="utf-8")
        for i in range(len(os.listdir(self.wiki_path))):
            print("Start merging the {0}-th file".format(i))
            sub_corpus_file = os.path.join(self.corpus_path, "{0}0{1}".format(self.corpus_name, i))
            input_stream = open(sub_corpus_file, "r", encoding="utf-8")
            line = input_stream.readline()
            while line:
                output_stream.writelines(line)
                line = input_stream.readline()
            input_stream.close()
        output_stream.close()

    def train(self, sg=1):
        """
        Train
        :param sg: use skip-gram.
        """
        logging.basicConfig(format="%(asctime)s:%(levelname)s:%(message)s", level=logging.INFO)
        corpus_file = os.path.join(self.corpus_path, self.corpus_name)

        # The default values of other parameters of Word2Vec are consistent with the requirements of the title
        model = word2vec.Word2Vec(word2vec.LineSentence(corpus_file), sg=sg)

        # Training as a single binary compressed file can be used independently
        if not os.path.isdir(self.model_path):
            os.mkdir(self.model_path)
        model_file = os.path.join(self.model_path, self.model_name)
        model.wv.save_word2vec_format(model_file, binary=True)

    def compute(self, test_file, output_file):
        """
        :param test_file:
        :param output_file:
        """
        # Read the model and the data to be calculated
        model_file = os.path.join(self.model_path, self.model_name)
        model = KeyedVectors.load_word2vec_format(model_file, binary=True)
        input_stream = open(test_file, encoding='utf-8')

        # String split into lists
        word_list = []
        while True:
            line = input_stream.readline()
            if not line:
                break
            word_list.append(re.split(r'[\t\n]', line))
        input_stream.close()

        # Calculate similarity
        for i in range(len(word_list)):
            words = word_list[i]
            try:
                sim = model.similarity(words[0], words[1])
                words[2] = str("%.4f" % sim)
                word_list[i] = words
                print(words)
            except KeyError:
                words[2] = 'OOV'
                word_list[i] = words
                print(words)

        # Save results
        lines = []
        for i in range(len(word_list)):
            line = word_list[i]
            lines.append(line[0] + '\t' + line[1] + '\t' + line[2] + '\n')
        output_stream = open(output_file, 'w', encoding='utf-8')
        output_stream.writelines(lines)
        output_stream.close()


if __name__ == "__main__":
    trainer = ChineseWord2Vec()
    trainer.parse()
    trainer.train()
    trainer.compute(test_file='./pku_sim_test.txt', output_file='2017211416.txt')
