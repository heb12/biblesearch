from subprocess import check_output
from collections import Counter
import sys, json, subprocess

# Use sed to grab specifc line in file
def getLine(filepath, line_number):
    return check_output([
		"sed",
		"-n",
		"%sp" % line_number,
		filepath
	]).decode("utf-8").replace("\n", "")

# Use GNU sed and grep to search word file (really fricking fast)
def getVerses(word):
	firstLetter = word[0:1]
	startLine = startPoints[firstLetter]
	
	# Super speedy linux stuffs
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

	# Return the equivalent line in data/verses
	return getLine("data/verses", int(result))

# This tell grep where to start alphabetically, so we don't read uncessessary data
startPoints = {"a":1,"b":976,"c":1818,"d":2783,"e":3483,"f":4067,"g":4621,"h":5030,"i":5695,"j":6082,"k":6456,"l":6607,"m":7014,"n":7687,"o":7950,"p":8217,"q":9085,"r":9122,"s":9749,"t":11252,"u":11935,"v":12121,"w":12246,"x":0,"y":12683,"z":12718}

# Delete main.py of parameters
params = sys.argv
del params[0]

# Finally use an slower method to track duplicates for each array
verseList = []
notFound = False
for i in range(0, len(params)):
	verses = getVerses(params[i])

	# Return if nothing found
	if verses == "NOTFOUND":
		notFound = True
		break

	versesJson = json.loads(verses)

	# Do not try and find duplicates if nothing is there
	if i != 0:
		verseList = set(verseList) & set(versesJson)
	else:
		verseList = versesJson

if notFound:
	print('["Not Found"]')
else:
	print(verseList)