import string
import itertools
# import classicalciphers
import math

ALPHABET = string.ascii_uppercase
LETTERS = ['E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z']
FREQUENCY = [0.12702, 0.09056, 0.08167, 0.07507, 0.06966, 0.06749, 0.06327, 0.06094, 0.05987, 0.04253, 0.04025, 0.02782, 0.02758, 0.02406, 0.02360, 0.02228, 0.02015, 0.01974, 0.01929, 0.01492, 0.00978, 0.00772, 0.00153, 0.00150, 0.00095, 0.00074]
ENGLISH_FREQUENCY_SUM = sum([x**2 for x in FREQUENCY])
ENGLISH_FREQUENCY = dict(zip(LETTERS, FREQUENCY))
ENGLISH_CI = 0.0667

def readfile(file):
    f=open(file, mode='r')
    message=''
    for ch in f.read():
        if 65 <= ord(ch) <= 90 or 97 <= ord(ch) <= 122:
            message+=ch.upper()
    f.close()
    return message

#Build shifted alphabet
def offset(char, offset):
    return ALPHABET[(ALPHABET.index(char)+offset)%26]

class Caesar:
    @staticmethod
    def encrypt(message, key):
        return ''.join(map(offset, list(message), [key,]*len(message)))

    @staticmethod
    def decrypt(ciphertext, key):
        return ''.join(map(offset, list(ciphertext), [26-key,]*len(ciphertext)))

class Vigenere:
    @staticmethod
    def encrypt(message, key):
        return ''.join(map(offset, message, list(map(lambda x: ALPHABET.index(x), key))*(len(message)//len(key)+1)))

    @staticmethod
    def decrypt(ciphertext, key):
        return ''.join(map(offset, ciphertext, list(map(lambda x: 26-ALPHABET.index(x), key))*(len(ciphertext)//len(key)+1)))

#Statistic of trigrams collected from this text https://en.wikipedia.org/wiki/Classical_cipher
# trigram_file = open('trigrams', 'rb')
# ENGLISH_TRIGRAMS = pickle.load(trigram_file)

#calculate letter freuency in string message
def frequency(message):
    return {ch: message.count(ch)/len(message) for ch in ALPHABET}

#calculate letters count in string message
def letterscount(message):
    return {ch: message.count(ch) for ch in ALPHABET}

#calculate coincidence index for string message
def indexcoincidence(message):
    lettersnumbers, length = letterscount(message), len(message)
    return sum([dict.get(lettersnumbers, num, 0) * (dict.get(lettersnumbers, num, 0) - 1) / (length * (length - 1)) for num in ALPHABET])

#select each step-th letter in message started from start-th sign
def columnrepresentation(message,  step, start=0):
    return ''.join([message[k] for k in range(start, len(message), step)])

#build a new strings msg by selecting letters with offset equal to i
#for each builted string calculate coincidence index
#if Vigenere key was not found last parametr of columnrepresentation should be changed
def shiftedindexcoincidence(message):
    result = {}
    for i in range(1, 26):
        msg=columnrepresentation(message, i, 0)
        result[i] = indexcoincidence(msg)
    return result

#Test is message frequency corresponds to eglish language
def alphabetcorrelation(messagefrequency):
    return sum(ENGLISH_FREQUENCY[ch]*messagefrequency[ch] for ch in ALPHABET)

#Break Caesar encryption by trying all possible key and check is frequency in decrypted message corresponds to english
def breakcaesar(ciphertext):
    variants=[]
    for i in range(26):
        d=Caesar.decrypt(ciphertext, i)
        msg_frequency=frequency(d)
        variants.append((i, alphabetcorrelation(msg_frequency)))
    return max(variants, key=lambda x: x[1])

#Searching Vigenere cipher's key length by calculation coincidence index for each possible length in range 1-25
#serchborder - parameter defining how close coincidence index should be to normal english coincidence index
def findvigenerekeylength(ciphertext, serchborder):
    keylengths = [(a, b) for a, b in shiftedindexcoincidence(ciphertext).items() if abs(b-ENGLISH_CI)<ENGLISH_CI*serchborder]
    ProbableLength=min(keylengths, key=lambda x: x[0])
    return ProbableLength[0]

#recovery Vigenere key character by character using key length
def recovervigenerekey(ciphertext, keylength):
    result=[]
    for k in range(keylength):
        msg=columnrepresentation(ciphertext, keylength, k)
        tmp=breakcaesar(msg)
        result.append(ALPHABET[tmp[0]])
    return ''.join(result)

message = readfile(r'111.txt')
print('---Break Caesar cipher---')
ciphertext = Caesar.encrypt(message, 16)
print(ciphertext)
print(frequency(ciphertext))
print(indexcoincidence(ciphertext))
print(Caesar.decrypt(ciphertext, breakcaesar(ciphertext)[0]))

print('---Break Vigenere cipher---')
ciphertext = Vigenere.encrypt(message, "SECRET")
print(ciphertext)
print(frequency(ciphertext))
print(indexcoincidence(ciphertext))
print(shiftedindexcoincidence(ciphertext))
keylen = findvigenerekeylength(ciphertext, 0.10)
print (keylen)
key = recovervigenerekey(ciphertext, keylen)
print(key)
mess = Vigenere.decrypt(ciphertext, key)
print(mess)
