var fs = require('fs');

// Define a bunch of raw data
var to = {"Gen":"Genesis","Exod":"Exodus","Lev":"Leviticus","Num":"Numbers","Deut":"Deuteronomy","Josh":"Joshua","Judg":"Judges","Ruth":"Ruth","1Sam":"1st Samuel","2Sam":"2nd Samuel","1Kgs":"1st Kings","2Kgs":"2nd Kings","1Chr":"1st Chronicles","2Chr":"2nd Chronicles","Ezra":"Ezra","Neh":"Nehemiah","Esth":"Esther","Job":"Job","Ps":"Psalms","Prov":"Proverbs","Eccl":"Ecclesiastes","Song":"Song of Solomon","Isa":"Isaiah","Jer":"Jeremiah","Lam":"Lamentations","Ezek":"Ezekiel","Dan":"Daniel","Hos":"Hosea","Joel":"Joel","Amos":"Amos","Obad":"Obadiah","Jonah":"Jonah","Mic":"Micah","Nah":"Nahum","Hab":"Habakkuk","Zeph":"Zephaniah","Hag":"Haggai","Zech":"Zechariah","Mal":"Malachi","Matt":"Matthew","Mark":"Mark","Luke":"Luke","John":"John","Acts":"Acts","Rom":"Romans","1Cor":"1st Corinthians","2Cor":"2nd Corinthians","Gal":"Galatians","Eph":"Ephesians","Phil":"Philippians","Col":"Colossians","1Thess":"1st Thessalonians","2Thess":"2nd Thessalonians","1Tim":"1st Timothy","2Tim":"2nd Timothy","Titus":"Titus","Phlm":"Philemon","Heb":"Hebrews","Jas":"James","1Pet":"1st Peter","2Pet":"2nd Peter","1John":"1st John","2John":"2nd John","3John":"3rd John","Jude":"Jude","Rev":"Revelation"};

var alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
var alphabetObj = {"a":0,"b":0,"c":0,"d":0,"e":0,"f":0,"g":0,"h":0,"i":0,"j":0,"k":0,"l":0,"m":0,"n":0,"o":0,"p":0,"q":0,"r":0,"s":0,"t":0,"u":0,"v":0,"w":0,"x":0,"y":0,"z":0}

// Load bible main data
var bible = require('./jubl2000.json');
bible = bible.osis.osisText.div;

var verses = {

}

// Generate verses as "Gen" or "Genesis"
// Change this from the notice after generating
var length = "short";

// Go through entire bible
for (var book = 0; book < bible.length; book++) {
    if (!book.chapter) {
        for (var chapter = 0; chapter < bible[book]['chapter'].length; chapter++) {
            processVerses(false, bible[book]['chapter'][chapter], length);
        }
    } else {
        processVerses(true, bible[book]['chapter'][chapter], length);
    }
}

// Process verses into OBJ
// Type refers to how JSON is structured, one chapter or multiple
function processVerses(type, obj, length) {
    if (!type) {
        for (var verse = 0; verse < obj.verse.length; verse++) {
            var text = obj.verse[verse][1];
            text = text.replace(/([0-9,!?.\(\):;'><\[\]\"])/gm, "");
            text = text.toLowerCase();

            textSplit = text.split(" ");

            for (var word = 0; word < textSplit.length; word++) {

                // Set to array if not
                if (typeof verses[textSplit[word]] == "undefined") {

                    // Filter out double spaces
                    if (textSplit[word] !== "") {
                        verses[textSplit[word]] = [];
                    }
                }

                var verseChapter = obj.osisID.split("."); // outputs ["john", "3"]

                // Use longer names or else, short
                var book;
                if (length == "long") {
                    var book = verseChapter[0];
                } else {
                    var book = to[verseChapter[0]];
                }

                var chapter = verseChapter[1];

                // Filter out double spaces again
                if (textSplit[word] !== "") {
                    verses[textSplit[word]].push(book + " " + chapter + " " + (verse + 1));
                }
            }
        }
    }
}

var allWords = Object.keys(verses);
allWords = allWords.sort(); // Sort alphabetically

// This should create a text "file" with every word, and the verses after a space
var verseFile = '';
for (var i = 1; i < allWords.length; i++) {
    verseFile += '["' + verses[allWords[i]].join('","') + '"]\n';
}

// Turn into breaks
var wordFile = allWords.join("\n");

// Generate alphabet file for speedier searching
var alphabetFile = "";
var currentLetter = 0;

for (var l = 0; l < alphabet.length; l++) {

    var letter = alphabet[l];
    for (var i = 0; i < allWords.length; i++) {

        var subWord = allWords[i].substring(0, 1);
        if (subWord == letter) {
            alphabetObj[letter] = i;
            break;
        }
    }
}

// First letter is 1 ahead
alphabetObj.a--

// Create data folder if not already created
if (!fs.existsSync("data")){
    fs.mkdirSync("data");
}

// Create verse file according to length
var verseFileName;
if (length == "long") {
    verseFileName = "versesLong";
} else {
    verseFileName = "versesShort"
}

fs.writeFile("data/" + verseFileName, verseFile, function() {
    console.log("Created " + verseFileName);
});

fs.writeFile("data/words", wordFile, function() {
    console.log("Created word file");
});

console.log("Notice: " + verseFileName + " was created, and the other verse length file was not.");
console.log("To generate the other file, change the length variable in this file to the opposite. (long/short)\n")
