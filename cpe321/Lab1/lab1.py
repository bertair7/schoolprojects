import sys, os, time
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
BLOCK_SIZE = 16

def cbcEncrypt(iv, one, key):
    firstByte = 0
    lastByte = 16

    obj = AES.new(key)
    loops = int(len(one) / BLOCK_SIZE)
    data = one[firstByte:lastByte]

    cip = obj.encrypt(bytes([a ^ b for a,b in zip(data, iv)]))
    cbc = cip

    for l in range(0, loops-1):
        firstByte = lastByte
        lastByte += BLOCK_SIZE
        data = one[firstByte:lastByte]

        xor = bytes([a ^ b for a,b in zip(data, cip)])
        cip = obj.encrypt(xor)
        cbc += cip

    return cbc

def pad(text):
    pad = BLOCK_SIZE - (len(text) % BLOCK_SIZE)
    s = ""
    for i in range(0, pad):
        s = s + chr(pad)
    return text + s.encode()

def unpad(text):
    val = text[-1]

    for i in range(1, val):
        if text[-i] != val:
            print("Error in padding sequence: pad of length " + str(val) + ", got " 
                    + str(text[-i]) + " at position " + str(len(text)-i))
            sys.exit(1)

    text = text.decode()
    text = text[:-val]

    return text

def cbcDecrypt(iv, one, key):
    firstByte = 0
    lastByte = 16

    obj = AES.new(key)
    loops = int(len(one) / BLOCK_SIZE)
    cip = one[firstByte:lastByte]

    dec = obj.decrypt(cip)
    cbc = bytes([a ^ b for a,b in zip(dec, iv)])
    
    for l in range(0, loops-1):
        firstByte = lastByte
        lastByte += BLOCK_SIZE
        data = one[firstByte:lastByte]

        dec = obj.decrypt(data)
        xor = bytes([a ^ b for a,b in zip(dec, cip)])
        cbc += xor
        cip = data

    return unpad(cbc)


def main():
    if (len(sys.argv) != 1):
        print('Wrong usage of program: lab1.py')
        sys.exit(0)
 
    h = SHA256.new()
    same = False
    inputs = 0
    t0 = time.clock()
    bitmap = '\xff\xff\xff\xff\xff\xff\xb0'

    while (same != True):
        s1 = os.urandom(8)
        s2 = os.urandom(8)
        inputs += 1

        h.update(s1)
        a = h.hexdigest()
        a = [ord(a) & ord(b) for a,b in zip(a, bitmap)]

        h.update(s2)
        b = h.hexdigest()
        b = [ord(a) & ord(b) for a,b in zip(b, bitmap)]

        if a == b:
            same = True
            t1 = time.clock()

    print(str(t1 - t0))
    print("inputs: " + str(inputs))

'''    h.update(b"Yelling hurts my ears")
    print(h.hexdigest())
    h.update(b"Yellinf hurts my ears")
    print(h.hexdigest())
 '''   

if __name__ == '__main__':
    main()

