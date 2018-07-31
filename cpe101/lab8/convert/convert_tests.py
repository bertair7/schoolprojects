import unittest
import convert

class TestConvert(unittest.TestCase):
   def test_convert(self):
      str1 = '8.0'
      str2 = 'eight'
      default = 8.0
      self.assertEqual(convert.float_default(str1, default), 8.0)
      self.assertEqual(convert.float_default(str2, default), 8.0)


if __name__ == '__main__':
   unittest.main()

