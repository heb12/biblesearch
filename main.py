# This program must be executed like this:
# python3 main.py <versesLong/versesShort> for god so loved the world
# versesLong and Short are like Gen.3.1 and Genesis 3 1

from subprocess import check_output
from collections import Counter
import sys, json, subprocess, copy

# This tell grep where to start alphabetically, so we don't read uncessessary data
with open("data/alphabet.json") as file:
	startPoints = file.read()
	startPoints = json.loads(startPoints);

# Use Sed to grab specifc line in file
def getLine(file, line):
    lineResult = subprocess.check_output(
        "sed -n " + str(line) + "p " + file,
        shell = True
    ).decode("utf-8").replace("\n", "")
    return lineResult

# Use GNU sed and grep to search word file
def getVerses(word):
	firstLetter = word[0:1]
	startLine = startPoints[firstLetter]

	# Use Sed | Grep
	try:
		resultLine = subprocess.check_output(
			"sed -n '" + str(startLine) + ",$ p' data/words | grep -x --line-number '" + word + "'  | sed 's/:.*//'",
			shell = True
		)
	except Exception as e:
		return [1, "Error, word not found."] # Return text if command returns error (word not found)

	# Filter out the string some
	result = resultLine.decode("utf-8").replace("\n", "")
	result = int(result);

	# add back start point, and minus 1
	result = result + startLine - 1

	# Return the equivalent line in data/verses, with return type
	return getLine("data/verses", int(result))

def search(obj):
	words = obj['words']

	# Use .intersection to extract duplicates in the new and old array
	verseList = []
	for i in range(0, len(words)):
		verses = getVerses(words[i])

		# Return if nothing found
		if verses[0] == 1:
			return verses[1]

		versesJson = json.loads(verses)

		# Do not try and find duplicates if nothing is there
		# Use built-in python function
		if i != 0:
			verseList = set(verseList).intersection(versesJson)
			verseList = list(verseList)
		else:
			verseList = versesJson

		verseList = json.dumps(verseList) # This converts the single quotes to double (javascript needs that)
		return verseList

# Test Script:
print(search({'words': ["for", "god", "so", "loved"]}))
