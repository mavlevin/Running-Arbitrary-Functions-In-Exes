
import binascii

def encode(s):
	"""encode a string to be later decode by the C program"""
	s = s[::-1]

	result = b"\x00"
	for c in s:
		result += bytes([c ^ result[-1] ^ 0x31])

	return result[::-1]

res = encode(b"hello :)")
printable = "\\x" + "\\x".join("{:02x}".format(c) for c in res)
print(printable)
