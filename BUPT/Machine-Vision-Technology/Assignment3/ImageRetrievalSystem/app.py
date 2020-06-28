import os

from flask import Flask, render_template, request, jsonify

import searcher

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


# Image database url list route
@app.route('/list', methods=['POST'])
def image_list():
    imgList = [img for img in list(os.listdir(os.path.join(os.path.dirname(__file__), 'static/images/'))) if
               img[-4:] == '.jpg']
    return jsonify(imgList=imgList)


# Search route
@app.route('/search', methods=['POST'])
def search():
    results_array = []

    # Get url
    image_url = request.form.get('img')

    # Perform the search
    results = searcher.search(image_url)

    # Return success
    return jsonify(results=results, preview="images/" + image_url)


# run
if __name__ == '__main__':
    app.run()
