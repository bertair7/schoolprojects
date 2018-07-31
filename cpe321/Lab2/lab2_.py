import sys, os
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
from Crypto.Util import number

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

def part1():
    h1 = SHA256.new()
    h2 = SHA256.new()
    iv = os.urandom(BLOCK_SIZE)

    p = int("B10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C69A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C013ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD7098488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708DF1FB2BC2E4A4371", 16)
    g = int("A4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507FD6406CFF14266D31266FEA1E5C41564B777E690F5504F213160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28AD662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24855E6EEB22B3B2E5", 16)
    a = 7
    b = 17

    mA = "Hi Bob!"
    mB = "Hi Alice!"

    A = pow(g, a, p)
    B = pow(g, b, p)

    sharedA = pow(B, a, p)
    h1.update(str(sharedA).encode())
    kA = h1.digest()[:BLOCK_SIZE]

    sharedB = pow(A, b, p)
    h2.update(str(sharedB).encode())
    kB = h2.digest()[:BLOCK_SIZE]

    print("sharedA = " + str(sharedA) + "\nsharedB = " + str(sharedB))
    print("kA = " + str(kA) + "\nkB = " + str(kB))

    mA = pad(mA.encode())
    mB = pad(mB.encode())

    cA = cbcEncrypt(iv, mA, kA)
    cB = cbcEncrypt(iv, mB, kB)

    print("cA = " + str(cA) + "\ncB = " + str(cB))
 
    m0 = cbcDecrypt(iv, cB, kA)
    m1 = cbcDecrypt(iv, cA, kB)

    print("m0 = " + str(m0) + "\nm1 = " + str(m1))

#------------------------------------------------------------------------------

def part2():
    h1 = SHA256.new()
    h2 = SHA256.new()
    iv = os.urandom(BLOCK_SIZE)

    p = int("B10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C69A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C013ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD7098488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708DF1FB2BC2E4A4371", 16)
    g = int("A4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507FD6406CFF14266D31266FEA1E5C41564B777E690F5504F213160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28AD662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24855E6EEB22B3B2E5", 16)
    a = 7
    b = 17

    mA = "Hi Bob!"
    mB = "Hi Alice!"

    # Mallory attack - g = 1, p, p-1
    g = p

    A = pow(g, a, p)
    B = pow(g, b, p)
    print("A = " + str(A) + "\nB = " + str(B))

    # Mallory attack - A = p; B = p
    sharedA = pow(B, a, p)
    h1.update(str(sharedA).encode())
    kA = h1.digest()[:BLOCK_SIZE]

    sharedB = pow(A, b, p)
    h2.update(str(sharedB).encode())
    kB = h2.digest()[:BLOCK_SIZE]

    print("sharedA = " + str(sharedA) + "\nsharedB = " + str(sharedB))
    print("kA = " + str(kA) + "\nkB = " + str(kB))

    mA = pad(mA.encode())
    mB = pad(mB.encode())

    cA = cbcEncrypt(iv, mA, kA)
    cB = cbcEncrypt(iv, mB, kB)

    print("cA = " + str(cA) + "\ncB = " + str(cB))
 
    m0 = cbcDecrypt(iv, cB, kA)
    m1 = cbcDecrypt(iv, cA, kB)

    print("m0 = " + str(m0) + "\nm1 = " + str(m1))

#------------------------------------------------------------------------------

def rsaEncrypt(msg, key):
    e, n = key
    cip = [pow(ord(a), e, n) for a in msg]
    return cip

def rsaDecrypt(cip, key):
    d, n = key
    dec = [chr(pow(a, d, n)) for a in cip]
    return ''.join(dec)

def multInverse(e, phi):
    d = e % phi
    for x in range(1, phi):
        if (d * x) % phi == 1:
            return x
    return 1

def part3():
    primeLen = 8
    e = 65537
    h = SHA256.new()

    p = number.getPrime(primeLen)
    q = number.getPrime(primeLen)
    n = p * q
    phi = (p-1) * (q-1)

    d = multInverse(e, phi)
    print(e * d % phi) 

    msg = "I'm a little teacup"
    public = (e, n)
    secret = (d, n)

    cip = rsaEncrypt(msg, public)
    dec = rsaDecrypt(cip, secret)
    print(dec)

#------------------------------------------------------------------------------

def main():
    #part1()
    #part2()
    part3()

if __name__ == '__main__':
    main()
