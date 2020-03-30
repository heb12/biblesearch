# HTTP server
import flask, json, os, main, logging
from flask import request
from waitress import serve

app = flask.Flask(__name__)

@app.route('/', methods=['GET'])
def home():
	words = request.args.get('words')
	length = request.args.get('length')
	page = request.args.get('page')
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
		output = main.search({'words': words, 'returnType': length})
		output = json.loads(output)

		# Result slicing (1-10, 5-20)
		if results != None:
			results = results.split("-")

			if len(results) < 2:
				return "['Results must be in format 1-10']"
			else:
				try:
					output = output[int(results[0]):int(results[1])]
				except Exception as e:
					return "['Array slicing error']"

		# Remove backslashes
		output = json.dumps(output)
		output = output.replace("\\", "")

		if callback is None:
			return output
		else:
			return callback + "(" + output + ")"
	except Exception as e:
		logging.exception(e)
		return "['URL parameter error']"

serve(app, host='0.0.0.0', port=5000)
