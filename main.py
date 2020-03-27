# This program must be executed like this:
# python3 main.py <versesLong/versesShort> for god so loved the world
# versesLong and Short are like Gen.3.1 and Genesis 3 1

from subprocess import check_output
from collections import Counter
import sys, json, subprocess, copy

# This tell grep where to start alphabetically, so we don't read uncessessary data
startPoints = {"a":1,"b":976,"c":1818,"d":2783,"e":3483,"f":4067,"g":4621,"h":5030,"i":5695,"j":6082,"k":6456,"l":6607,"m":7014,"n":7687,"o":7950,"p":8217,"q":9085,"r":9122,"s":9749,"t":11252,"u":11935,"v":12121,"w":12246,"x":0,"y":12683,"z":12718}

# Use GNU SED to grab specifc line in file
def getLine(file, line):
    lineResult = subprocess.check_output(
        "sed -n " + line + "p " + filepath,
        shell = True
    ).decode("utf-8").replace("\n", "")

# Use GNU sed and grep to search word file
def getVerses(word, returnType):
	firstLetter = word[0:1]
	startLine = startPoints[firstLetter]

	# Use
	try:
		resultLine = subprocess.check_output(
			"sed -n '" + str(startLine) + ",$ p' data/words | grep -x --line-number '" + word + "'",
			shell = True
		)
	except Exception as e:
		return "NOTFOUND" # Return text if command returns error (word not found)

	# Sed = Grep returns as bytes, and 123:word, so parse it
	result = resultLine.decode("utf-8").replace("\n", "")
	result = result.split(":")[0]
	result = int(result);
	result = result + startLine - 1 # add back start point, and minus 1

	# Return the equivalent line in data/verses, with return type
	return getLine("data/" + returnType, int(result))

def search(obj):
	words = obj['words']

	# Use .intersection to extract duplicates in the new and old array
	verseList = []
	notFound = False
	for i in range(0, len(words)):
		verses = getVerses(words[i], obj['returnType'])

		# Return if nothing found
		if verses == "NOTFOUND":
			notFound = True
			break

		versesJson = json.loads(verses)

		# Do not try and find duplicates if nothing is there
		# Use built-in python function
		if i != 0:
			verseList = set(verseList).intersection(versesJson)
			verseList = list(verseList)
		else:
			verseList = versesJson

	if notFound:
		return '["Not Found"]'
	else:
		verseList = json.dumps(verseList) # This converts the single quotes to double (javascript needs that)
		return verseList
