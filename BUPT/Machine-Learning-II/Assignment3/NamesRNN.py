import numpy as np


class NamesRNN:
    """
    Decision baby names RNN class
    """

    def __init__(self, names_file):
        self.names_file = names_file

        data = open(dataset_file, 'r').read().lower()
        chars = list(set(data))
        chars_sorted = sorted(chars)
        self.vocab_size = len(chars)  # Number of unique characters found in the text, size of the vocabulary
        self.char2ix = {ch: i for i, ch in enumerate(chars_sorted)}  # Dictionary mapping each index to a character
        self.ix2char = {i: ch for i, ch in enumerate(chars_sorted)}  # Dictionary mapping each character to an index
        print('Unique characters in dataset:', self.vocab_size)

        # params: python dictionary containing:
        #   Wax - Weight matrix multiplying the input, numpy array of shape (n_a, n_x)
        #   Waa - Weight matrix multiplying the hidden state, numpy array of shape (n_a, n_a)
        #   Wya - Weight matrix relating the hidden-state to the output, numpy array of shape (n_y, n_a)
        #   b -  Bias, numpy array of shape (n_a, 1)
        #   by - Bias relating the hidden-state to the output, numpy array of shape (n_y, 1)
        self.params = {}

        # grads: python dictionary containing:
        #   dWax - Gradients of input-to-hidden weights, of shape (n_a, n_x)
        #   dWaa - Gradients of hidden-to-hidden weights, of shape (n_a, n_a)
        #   dWya - Gradients of hidden-to-output weights, of shape (n_y, n_a)
        #   db - Gradients of bias vector, of shape (n_a, 1)
        #   dby - Gradients of output bias vector, of shape (n_y, 1)
        self.grads = {}

    @staticmethod
    def softmax(x):
        e_x = np.exp(x - np.max(x))
        return e_x / e_x.sum(axis=0)

    def rnn_forward_step(self, a_prev, x):
        # Hidden state
        a_next = np.tanh(np.dot(self.params['Wax'], x) + np.dot(self.params['Waa'], a_prev) + self.params['b'])

        # Unnormalized log probabilities for next chars
        p_t = self.softmax(np.dot(self.params['Wya'], a_next) + self.params['by'])

        return a_next, p_t

    def rnn_backward_step(self, dy, x, a, a_prev):
        self.grads['dWya'] += np.dot(dy, a.T)
        self.grads['dby'] += dy
        da = np.dot(self.params['Wya'].T, dy) + self.grads['da_next']  # Back propagate into h
        daraw = (1 - a * a) * da  # Back propagate through tanh nonlinearity
        self.grads['db'] += daraw
        self.grads['dWax'] += np.dot(daraw, x.T)
        self.grads['dWaa'] += np.dot(daraw, a_prev.T)
        self.grads['da_next'] = np.dot(self.params['Waa'].T, daraw)

    def rnn_forward(self, X, Y, a0):
        # Initialize x, a and y_hat as empty dictionaries
        x, a, y_hat = {}, {}, {}

        a[-1] = np.copy(a0)

        # Initialize the loss to 0
        loss = 0

        for t in range(len(X)):

            # Set x[t] to be the one-hot vector representation of the t'th character in X.
            # if X[t] == None, we just have x[t]=0. This is used to set the input for the first time step to the zero vector.
            x[t] = np.zeros((self.vocab_size, 1))
            if X[t] is not None:
                x[t][X[t]] = 1

            # Run one step forward of the RNN
            a[t], y_hat[t] = self.rnn_forward_step(a[t - 1], x[t])

            # Update the loss by substracting the cross-entropy term of this time-step from it.
            loss -= np.log(y_hat[t][Y[t]][0])

        return loss, (y_hat, a, x)

    def rnn_backward(self, X, Y, cache):
        # Initialize gradients as an empty dictionary
        self.grads = {}  # A dictionary containing the gradients "dWaa", "dWax", "dWya", "db", "dby"

        # Retrieve from cache and parameters
        (y_hat, a, x) = cache

        # Each one should be initialized to zeros of the same dimension as its corresponding parameter
        self.grads['dWax'] = np.zeros_like(self.params['Wax'])
        self.grads['dWaa'] = np.zeros_like(self.params['Waa'])
        self.grads['dWya'] = np.zeros_like(self.params['Wya'])
        self.grads['db'] = np.zeros_like(self.params['b'])
        self.grads['dby'] = np.zeros_like(self.params['by'])
        self.grads['da_next'] = np.zeros_like(a[0])

        # Back propagate through time
        for t in reversed(range(len(X))):
            dy = np.copy(y_hat[t])
            dy[Y[t]] -= 1
            self.rnn_backward_step(dy, x[t], a[t], a[t - 1])

        return a

    def sample(self, seed):
        """
        Sample a sequence of characters according to a sequence of probability distributions output of the RNN.

        :param seed: used for grading purposes.
        :return: indices - a list of length n containing the indices of the sampled characters.
        """

        n_a = self.params['Waa'].shape[1]

        # Create the one-hot vector x for the first character (initializing the sequence generation).
        x = np.zeros((self.vocab_size, 1))
        # Initialize a_prev as zeros
        a_prev = np.zeros((n_a, 1))

        # Create an empty list of indices, this is the list which will contain the list of indices of the characters to generate
        indices = []

        # Idx is a flag to detect a newline character, we initialize it to -1
        idx = -1

        # Loop over time-steps t. At each time-step, sample a character from a probability distribution and append
        # its index to "indices". We'll stop if we reach 20 characters (which should be very unlikely with a well
        # trained model), which helps debugging and prevents entering an infinite loop.
        counter = 0
        max_counter = 20
        newline_char = self.char2ix['\n']

        while idx != newline_char and counter != max_counter:
            # Forward propagate x using the following equations
            a = np.tanh(np.dot(self.params['Wax'], x) + np.dot(self.params['Waa'], a_prev) + self.params['b'])
            z = np.dot(self.params['Wya'], a) + self.params['by']
            y = self.softmax(z)

            # For grading purposes
            np.random.seed(counter + seed)

            # Sample the index of a character within the vocabulary from the probability distribution y
            idx = np.random.choice(a=list(range(self.vocab_size)), p=y.ravel())

            # Append the index to "indices"
            indices.append(idx)

            # Overwrite the input character as the one corresponding to the sampled index.
            x = np.zeros((self.vocab_size, 1))
            x[idx] = 1

            # Update "a_prev" to be "a"
            a_prev = a

            # For grading purposes
            seed += 1
            counter += 1

        if counter == max_counter:
            indices.append(self.char2ix['\n'])

        return indices

    def print_sample(self, sample_ix):
        txt = ''.join(self.ix2char[ix] for ix in sample_ix)
        txt = txt[0].upper() + txt[1:]  # capitalize first character
        print(txt, end='')

    def optimize(self, X, Y, a_prev, learning_rate=0.01):
        """
        Execute one step of the optimization to train the model.

        :param X: list of integers, where each integer is a number that maps to a character in the vocabulary.
        :param Y: list of integers, exactly the same as X but shifted one index to the left.
        :param a_prev: previous hidden state.
        :param learning_rate: learning rate for the model.
        :return:    loss - value of the loss function (cross-entropy);
                    a[len(X)-1] - the last hidden state, of shape (n_a, 1)
        """

        # Forward propagate through time
        loss, cache = self.rnn_forward(X, Y, a_prev)

        # Back propagate through time
        a = self.rnn_backward(X, Y, cache)

        # Gradient clipping: clips the gradients' values between -5 and 5.
        max_value = 5
        dWax = self.grads['dWax']
        dWaa = self.grads['dWaa']
        dWya = self.grads['dWya']
        db = self.grads['db']
        dby = self.grads['dby']
        # Clip to mitigate exploding gradients, loop over [dWax, dWaa, dWya, db, dby].
        for grad in [dWax, dWaa, dWya, db, dby]:
            np.clip(grad, -max_value, max_value, out=grad)
        # A dictionary with the clipped gradients.
        self.grads = {"dWax": dWax, "dWaa": dWaa, "dWya": dWya, "db": db, "dby": dby}

        # Update parameters
        self.params['Wax'] += -learning_rate * self.grads['dWax']
        self.params['Waa'] += -learning_rate * self.grads['dWaa']
        self.params['Wya'] += -learning_rate * self.grads['dWya']
        self.params['b'] += -learning_rate * self.grads['db']
        self.params['by'] += -learning_rate * self.grads['dby']

        return loss, a[len(X) - 1]

    def train(self, n_iterations=100000, n_a=50, seq_length=5):
        """
        Trains the model and generates baby names.
        Overview of the model:
            - Initialize parameters
            - Run the optimization loop
                - Forward propagation to compute the loss function
                - Backward propagation to compute the gradients with respect to the loss function
                - Clip the gradients to avoid exploding gradients
                - Using the gradients, update your parameter with the gradient descent update rule
            - Get the learned parameters

        :param n_iterations: number of iterations to train the model for
        :param n_a: number of units of the RNN cell
        :param seq_length: number of baby names you want to sample at each iteration.
        """

        # Initialize parameters with small random values.
        Wax = np.random.randn(n_a, self.vocab_size) * 0.01  # Input to hidden
        Waa = np.random.randn(n_a, n_a) * 0.01  # Hidden to hidden
        Wya = np.random.randn(self.vocab_size, n_a) * 0.01  # Hidden to output
        b = np.zeros((n_a, 1))  # Hidden bias
        by = np.zeros((self.vocab_size, 1))  # Output bias
        self.params = {"Wax": Wax, "Waa": Waa, "Wya": Wya, "b": b, "by": by}

        # Initialize loss (this is required because we want to smooth our loss)
        loss = -np.log(1.0 / self.vocab_size) * seq_length

        # Build list of all baby names (training examples).
        with open(self.names_file) as f:
            names = f.readlines()
        names = [x.lower().rstrip() for x in names]

        # Shuffle list of all baby names
        np.random.seed(0)
        np.random.shuffle(names)

        # Initialize the hidden state of the LSTM
        a_prev = np.zeros((n_a, 1))

        # Optimization loop
        for i in range(n_iterations):

            # Use the hint above to define one training example (X,Y)
            index = i % len(names)
            X = [None] + [self.char2ix[ch] for ch in names[index]]
            Y = X[1:] + [self.char2ix["\n"]]

            # Perform one optimization step: Forward-prop -> Backward-prop -> Clip -> Update parameters
            cur_loss, a_prev = self.optimize(X, Y, a_prev)

            # Use a latency trick to keep the loss smooth. It happens here to accelerate the training.
            loss = loss * 0.999 + cur_loss * 0.001

            # Every 1000 Iteration, generate "n" characters thanks to sample() to check if the model is learning properly
            if (i + 1) % 1000 == 0:
                print('\n\nIteration: {0}, Loss: {1}\n'.format(i + 1, loss))

                # The number of baby names to print
                seed = 0
                for name in range(seq_length):
                    # Sample indices and print them
                    sample_ix = self.sample(seed)
                    self.print_sample(sample_ix)

                    seed += 1  # To get the same result for grading purposed, increment the seed by one.

    def predict(self, begin):

        """
        Predict a sequence of characters according to a sequence of probability distributions output of the RNN.
        :param begin:
        """

        n_a = self.params['Waa'].shape[1]

        # Create the one-hot vector x for the last character of the given characters.
        x = np.zeros((self.vocab_size, 1))

        # Initialize a_prev as zeros
        a_prev = np.zeros((n_a, 1))  ######
        for i in range(len(begin)):
            # Forward propagate x using the following equations
            a = np.tanh(np.dot(self.params['Wax'], x) + np.dot(self.params['Waa'], a_prev) + self.params['b'])
            # Overwrite the input character as the one corresponding to the sampled index.
            x = np.zeros((self.vocab_size, 1))
            x[self.char2ix[begin[i]]] = 1
            # Update "a_prev" to be "a"
            a_prev = a

        # Create an empty list of indices, this is the list which will contain the list of indices of the characters to generate
        indices = []
        for char in begin:
            indices.append(self.char2ix[char])
        # Idx is a flag to detect a newline character, we initialize it to -1
        idx = [-1]

        # Loop over time-steps t. At each time-step, sample a character from a probability distribution and append
        # its index to "indices". We'll stop if we reach 20 characters (which should be very unlikely with a well
        # trained model), which helps debugging and prevents entering an infinite loop.
        counter = len(begin)
        max_counter = 20
        newline_char = self.char2ix['\n']

        while idx[0] != newline_char and counter != max_counter:
            # Forward propagate x using the following equations
            a = np.tanh(np.dot(self.params['Wax'], x) + np.dot(self.params['Waa'], a_prev) + self.params['b'])
            z = np.dot(self.params['Wya'], a) + self.params['by']
            y = self.softmax(z)

            # For grading purposes
            np.random.seed(counter)

            # Sample the index of a character within the vocabulary from the probability distribution y
            idx = np.random.choice(a=list(range(self.vocab_size)), size=5, replace=False, p=y.ravel())

            # Append the index to "indices"
            indices.append(idx[0])

            # Overwrite the input character as the one corresponding to the sampled index.
            x = np.zeros((self.vocab_size, 1))
            x[idx[0]] = 1

            # Update "a_prev" to be "a"
            a_prev = a

            # For grading purposes
            counter += 1
            chars = []
            for ix in idx:
                chars.append(self.ix2char[ix])
            print("\n\nCandidate letters: ", chars)
            print("Current Name: ", end='')
            self.print_sample(indices)

        if counter == max_counter:
            indices.append(self.char2ix['\n'])


if __name__ == "__main__":
    dataset_file = 'baby_names/baby_names.txt'
    rnn = NamesRNN(dataset_file)
    rnn.train()
    rnn.predict(['a', 'b'])
