# This is a flask server
import flask, json, os
from flask import request
from waitress import serve

app = flask.Flask(__name__)

import biblesearch.main
os.chdir('biblesearch')

@app.route('/', methods=['GET'])
def home():
	words = request.args.get('words')
	length = request.args.get('length')
	callback = request.args.get('callback')

	# Defaults
	if words is None:
		words = 'for god so loved'
	if length is None:
		length = 'long'

	# Replace length with proper file name
	if length == "short":
		length = "versesShort"
	else:
		length = "versesLong"
	
	try:
		words = words.split(" ")

		output = biblesearch.main.search({'words': words, 'returnType': length})
		output = json.dumps(output)

		# Remove backslashes and start and end quotes, may not be the best, but will do for now
		output = output.replace("\\", "")[1:-1]

		if callback is None:
			return output
		else:
			return callback + "(" + output + ")"
	except Exception as e:
		print(e)
		return "['URL parameter error']"

serve(app, host='0.0.0.0', port=5000)