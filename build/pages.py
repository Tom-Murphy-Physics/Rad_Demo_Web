import flask
from flask import Flask
import subprocess

app = Flask(__name__)

bp = flask.Blueprint("pages", __name__)

@bp.route('/')
def home():
	<html>
		<body>
			<form>
				<input type="submit" name="open" value="Open">
				<input type="submit" name="close" value="Close">
			</form>
		<body>
	<html>
    
"""
@bp.route('/')
def home():
    return f'''
    <h1>Welcome to Rad Demo</h1>
    <form action="{flask.url_for('foo')}" method="post">
        <button type="submit">Run</button>
    </form>
    '''
"""

@bp.route("/about")
def about():
    return "Hello, About!"

@bp.route('/foo', methods=['POST'])
def foo():
    subprocess.run(["python3", "Rad_Demo.py"])

