import sys, os
from Crypto.Cipher import AES
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

def submit(text, iv, key):
    pre = "userid=321;userdata="
    suf = ";session-id=31337"
    
    t = pre + text + suf
    t = t.replace(';', '%3B')
    t = t.replace('=', '%3D')
    
    t = t.encode()
    t = pad(t)
    
    return cbcEncrypt(iv, t, key)

def verify(text, iv, key):
    admin = ';admin=true;'

    dec = cbcDecrypt(iv, text, key)
    print(dec)

    if admin in dec:
        return True
    else:
        return False

def main():
    if (len(sys.argv) != 5):
        print('Wrong usage of program: lab1.py infile outfile1 outfile2 "text"')
        sys.exit(0)
 
    key = os.urandom(BLOCK_SIZE)
    iv = os.urandom(BLOCK_SIZE)

    text = sys.argv[4]
    sub = submit(text, iv, key)

    admin = ";admin=true;"
    st = "userid%3D321%3Bu"

    iv = bytes([a ^ ord(b) for a,b in zip(iv, st)])
    iv = bytes([a ^ ord(b) for a,b in zip(iv, admin)])

    result = verify(sub, iv, key)
    print(result)
'''
    i_file1 = sys.argv[1]
    with open(i_file1, 'rb') as infile:
        header = infile.read(54)
        one = infile.read()

    one = pad(one)
    obj = AES.new(key)
    ecb = obj.encrypt(one)
   
    o_file1 = sys.argv[2]
    outfile1 = open(o_file1, 'wb')
    outfile1.write(header)
    outfile1.write(ecb)
     
    cbc = cbcEncrypt(iv, one, key)

    o_file2 = sys.argv[3]
    outfile2 = open(o_file2, 'wb')
    outfile2.write(header)
    outfile2.write(cbc)
'''      


if __name__ == '__main__':
    main()

