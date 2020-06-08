# coding:utf-8
import math


class ChineseSegmenter:
    def __init__(self, corpus=None, word_dic=None, bigram=None):
        """
        MP + Bigram
        :param corpus:
        :param word_dic:
        :param bigram:
        """
        self.corpus = corpus
        self.word_dic = word_dic
        self.bigram = bigram

    @staticmethod
    def is_chinese(uchar):
        """
        Determine whether a unicode is a Chinese character
        :param uchar:
        :return: True of False
        """
        return u'\u4e00' <= uchar <= u'\u9fa5'

    @staticmethod
    def is_number(uchar):
        """
        Determine whether a unicode is a number.
        Note that the numbering of the training set and the test set is not the same as the ordinary one.
        Consider using an or
        :param uchar:
        :return: True of False
        """
        return (u'\u0030' <= uchar <= u'\u0039') or ('０' <= uchar <= '９')

    @staticmethod
    def is_alpha(uchar):
        """
        Determine whether a unicode is an English alphabet
        :param uchar:
        :return: True of False
        """
        return (u'\u0041' <= uchar <= u'\u005a') or (u'\u0061' <= uchar <= u'\u007a')

    def is_other(self, uchar):
        """
        Determine whether it is not a Chinese character, number or English alphabet
        :param uchar:
        :return: True of False
        """
        return not (self.is_chinese(uchar) or self.is_number(uchar) or self.is_alpha(uchar))

    def fit(self, filename):
        """
        :param filename:
        """
        self.init_corpus(filename)
        self.init_dic()

    def init_corpus(self, filename):
        """
        Processing the training set to get the corpus
        :param filename:
        :return:
        """
        corpus = []
        f = open(filename)

        # Read each word in corpus_for_ass2train.txt into words
        for line in f.readlines():
            corpus.extend(line.split())

        for i in range(0, len(corpus)):
            # Process punctuation in corpus
            if self.is_other(corpus[i]):
                # If the current character is a punctuation mark, change it to S.
                # In the case of multiple punctuation marks, only one S remains
                if i != 0 and corpus[i - 1] == 'S':
                    corpus[i] = '#'
                else:
                    corpus[i] = 'S'

        self.corpus = []
        for i in range(0, len(corpus)):
            if corpus[i] != '#':
                self.corpus.append(corpus[i])

        f.close()

    def init_dic(self):
        """
        Construct a two-layer dictionary based on corpus, used for n_gram to calculate probability
        """
        self.word_dic = {}
        self.bigram = 0  # count counts the number of bigrams for Laplace smoothing
        for i in range(len(self.corpus)):
            ch = self.corpus[i]
            if ch not in self.word_dic:
                self.word_dic[ch] = {}
            # The number of times the word appears independently
            self.word_dic[ch][ch] = 1 + self.word_dic[ch].get(ch, 0)
            if i != len(self.corpus) - 1:
                ch_next = self.corpus[i + 1]
                # Count the frequency of occurrence of the word and the following word
                self.word_dic[ch][ch_next] = 1 + self.word_dic[ch].get(ch_next, 0)

        for key in self.word_dic.keys():
            self.bigram += len(self.word_dic[key].keys()) - 1  # Count the total number of all bigrams

    def get_all_words(self, sentence, max_length=5):
        """
        Find all the possible words in a sentence and their corresponding start and end positions.
        :param sentence:
        :param max_length: the maximum length of the forward match
        :return:
        """
        all_words = []
        word_stack = []
        for i in range(len(sentence)):
            # Save all possible segmentation results in the form of [word, i, j],
            # where i represents the position where word starts and j represents the position where word ends
            # Here, the first-in first-out of the stack is used to make the longer match in front of the all_words result,
            # which can significantly improve the final result and speed up the operation.
            word_stack.append([sentence[i], i, i])
            for j in range(1, max_length + 1):
                if i + j < len(sentence) and sentence[i:i + j + 1] in self.corpus:
                    word_stack.append([sentence[i:i + j + 1], i, i + j])
            while len(word_stack) != 0:
                all_words.append(word_stack.pop())
        return all_words

    def P(self, seg_sentence):
        """
        Pass in an already segmented result,
        use n_gram to calculate the probability of the segmentation result,
        and use Laplace smoothing.
        :param seg_sentence:
        :return:
        """
        P = 0
        # First divide the incoming split results by spaces
        word_list = seg_sentence.split(' ')
        word_list.insert(0, 'S')  # Add a sentence beginning
        # Calculate the conditional probability, then calculate the probability of the i-th word in the case of the i-1 word
        for i in range(len(word_list) - 1):
            word = word_list[i]
            word_next = word_list[i + 1]
            if word in self.word_dic:
                c1 = self.word_dic[word][word]
                c2 = self.word_dic[word].get(word_next, 0)
            else:
                c1 = 0
                c2 = 0
            # Conditional probability of the i-th word, logarithm
            P += math.log((c2 + 0.1) / (c1 + self.bigram * 0.1))
        return P

    def get_all_seg(self, sentence, max_length=5):
        """
        Get all possible segmentation results of sentence according to n_gram probability
        :param sentence:
        :param max_length:
        :return:
        """
        #
        all_words = self.get_all_words(sentence, max_length)  # Get all the possible words in the sentence first
        seg_result = []  # Save all possible segmentation results
        i = 0
        flag = 0
        while i < len(all_words):
            word = all_words[i]  # The word that needs to be stitched
            if word[1] == 0 and word[2] <= len(sentence) - 1:  # Has not formed the entire word order
                j = word[2] + 1  # where the word ends
                for word_next in all_words:  # Find all words that can be stitched by the word
                    if word_next[1] == j:
                        # Splice out a new word and calculate the probability
                        word_new = '{0} {1}'.format(word[0], word_next[0])
                        P_new = self.P(word_new)
                        # Search among all words to see if there is a word that corresponds to the position of the new word.
                        # If so,
                        # compare the probabilities of the two and remove the small probability to reduce a lot of useless calculations
                        for word_old in all_words:
                            if word_old[1] == word[1] and word_old[2] == word_next[2] and word_old[0] != word_new:
                                P_old = self.P(word_old[0])
                                if P_old >= P_new:
                                    # Do not add new words
                                    P_new = P_old
                                else:
                                    all_words.remove(word_old)
                            # When the search condition is not satisfied, break directly to speed up the calculation
                            if word_old[1] > word[1]:
                                break
                        if P_new == self.P(word_new) and [word_new, word[1], word_next[2]] not in all_words:
                            all_words.insert(flag, [word_new, word[1], word_next[2]])
                    elif word_next[1] > j:
                        break
                # The result of word has been traversed and can be deleted from the list to avoid useless calculations later
                all_words.remove(word)
                i = flag
            # When a segmentation result that satisfies the condition is found,
            # add it to the final result and add flag + 1
            elif word[1] == 0 and word[2] == len(sentence) - 1:
                if word[0] not in seg_result:
                    seg_result.append(word[0])
                flag += 1
                i = flag
            elif word[1] != 0:
                break

        return seg_result

    def best_seg(self, sentence, max_length=5):
        """
        :param sentence:
        :param max_length:
        :return:
        """
        MP = float('-Inf')
        best_seg = ''
        # Compare all the split results and take the most probable split
        for seg in self.get_all_seg(sentence, max_length):
            P = self.P(seg)
            if P > MP:
                MP = P
                best_seg = seg
        return best_seg

    def seg(self, sentence):
        """
        Traverse the sentence,
        cut the sentence according to Chinese characters, numbers, letters, and punctuation marks,
        and the Chinese characters must also be broken by MP
        :param sentence:
        :return:
        """
        result = []
        pre = ''
        word = ''
        number = ''
        alpha = ''
        for ch in sentence:
            if self.is_other(ch):
                # When the current character is a punctuation mark, save the previous result
                if self.is_number(pre):
                    result.append(number)
                    number = ''
                elif self.is_alpha(pre):
                    result.append(alpha)
                    alpha = ''
                elif self.is_chinese(pre):
                    word = self.best_seg(word)
                    result.append(word)
                    word = ''
                result.append(ch)
            elif self.is_number(ch):
                # When the current character is a number, it is stored cumulatively
                number += ch
                # If the previous character is not a number, save it
                if self.is_alpha(pre):
                    result.append(alpha)
                    alpha = ''
                elif self.is_chinese(pre):
                    word = self.best_seg(word)
                    result.append(word)
                    word = ''
            elif self.is_alpha(ch):
                # When the current character is a letter, it is saved cumulatively
                alpha += ch
                # If the previous character is not a letter, save it
                if self.is_number(pre):
                    result.append(number)
                    number = ''
                elif self.is_chinese(pre):
                    word = self.best_seg(word)
                    result.append(word)
                    word = ''
            else:
                word += ch
                if self.is_number(pre):
                    result.append(number)
                    number = ''
                elif self.is_alpha(pre):
                    result.append(alpha)
                    alpha = ''
            pre = ch
        # Save the last part of the sentence
        if number != '':
            result.append(number)
        elif alpha != '':
            result.append(alpha)
        elif word != '':
            word = self.best_seg(word)
            result.append(word)
        return result


if __name__ == "__main__":
    segmenter = ChineseSegmenter()
    segmenter.fit('corpus_for_ass2train.txt')
    f_test = open('corpus_for_ass2test.txt', 'r')
    f_result = open('2017211416_test.txt', 'w')

    for line_test in f_test.readlines():  # Read test set
        line_result = ' '.join(segmenter.seg(line_test))
        print(line_result)
        f_result.write(line_result)

    f_result.close()
    f_test.close()
