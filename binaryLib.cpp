#include <iostream>
#include <string>
#include <vector>
#include <math.h>

std::vector<int> multiplyBinaryNumbers(const std::vector<int>& binaryNum1, const std::vector<int>& binaryNum2) {
    std::vector<int> result(binaryNum1.size() + binaryNum2.size(), 0);

    for (int i = binaryNum1.size() - 1; i >= 0; i--) {
        if (binaryNum1[i] == 1) {
            int carry = 0;
            for (int j = binaryNum2.size() - 1; j >= 0; j--) {
                int temp = result[i + j + 1] + binaryNum2[j] + carry;
                result[i + j + 1] = temp % 2;
                carry = temp / 2;
            }
            result[i] += carry;
        }
    }

    return result;
}

std::vector<int> addBinaryNumbers(const std::vector<int>& binaryNum1, const std::vector<int>& binaryNum2) {
    int size1 = binaryNum1.size();
    int size2 = binaryNum2.size();
    int maxSize = std::max(size1, size2);
    std::vector<int> result(maxSize, 0);
    int carry = 0;

    for (int i = 0; i < maxSize; i++) {
        int sum = carry;
        if (i < size1)
            sum += binaryNum1[size1 - i - 1];
        if (i < size2)
            sum += binaryNum2[size2 - i - 1];

        result[maxSize - i - 1] = sum % 2;
        carry = sum / 2;
    }

    if (carry > 0) {
        result.insert(result.begin(), carry);
    }

    return result;
}

std::vector<int> toBinary(unsigned int n) {
    std::vector<int> binaryRepresentation;

    if (n == 0) {
        binaryRepresentation.push_back(0);
    } else {
        while (n > 0) {
            binaryRepresentation.insert(binaryRepresentation.begin(), n % 2);
            n /= 2;
        }
    }

    return binaryRepresentation;
}

std::vector<std::vector<int>> makeNumericForm(const std::string& myMsg) {
    std::vector<std::vector<int>> msg;

    for (int i = 0; i < myMsg.length(); i++) {
        msg.push_back(toBinary(myMsg[i]));
    }

    return msg;
}

std::vector<int> getBinarySumOfString(std::string input) {
  std::vector<std::vector<int>> M = makeNumericForm(input);
  std::vector<std::vector<int>> total = {{0}};
  std::vector<int> curr;
  int i = 0;
  for (std::vector<int> list : M) {
      for (int digit : addBinaryNumbers(total[i], list)) {
        curr.push_back(digit);
      }

      total.push_back(curr);
      curr.clear();
      i++;
  }

  return total.back();
}

/* compares the sizes of the vectors first. If the sizes are different, it returns 1 if the first number is larger, -1 if it is smaller, and 0 if they are equal. If the sizes are the same, it compares each bit from the most significant bit to the least significant bit and returns 1, -1, or 0 accordingly. */
int compareBinaryNumbers(const std::vector<int>& binaryNum1, const std::vector<int>& binaryNum2) {
    int size1 = binaryNum1.size();
    int size2 = binaryNum2.size();

    if (size1 > size2) {
        return 1;
    } else if (size1 < size2) {
        return -1;
    } else {
        for (int i = 0; i < size1; i++) {
            if (binaryNum1[i] > binaryNum2[i]) {
                return 1;
            } else if (binaryNum1[i] < binaryNum2[i]) {
                return -1;
            }
        }
        return 0;
    }
}

std::vector<int> subtractBinaryNumbers(const std::vector<int>& binaryNum1, const std::vector<int>& binaryNum2) {
    std::vector<int> result;
    std::vector<int> temp1(binaryNum1);
    std::vector<int> temp2(binaryNum2);
    int size1 = temp1.size();
    int size2 = temp2.size();

    // Pad the shorter binary number with leading zeros
    if (size1 < size2) {
        temp1.insert(temp1.begin(), size2 - size1, 0);
    } else if (size2 < size1) {
        temp2.insert(temp2.begin(), size1 - size2, 0);
    }

    int borrow = 0;
    for (int i = temp1.size() - 1; i >= 0; i--) {
        int diff = temp1[i] - temp2[i] - borrow;

        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.insert(result.begin(), diff);
    }

    // Remove leading zeros from the result
    while (!result.empty() && result[0] == 0) {
        result.erase(result.begin());
    }

    if (result.empty()) {
        result.push_back(0);
    }

    return result;
}

std::vector<int> moduloBinaryNumbers(const std::vector<int>& binaryNum1, const std::vector<int>& binaryNum2) {
    std::vector<int> quotient(binaryNum1);
    std::vector<int> remainder;

    while (compareBinaryNumbers(quotient, binaryNum2) >= 0) {
        if (quotient[0] == 1) {
            remainder = subtractBinaryNumbers(remainder, binaryNum2);
        }
        quotient.erase(quotient.begin());
        quotient.push_back(0);
    }

    return remainder;
}

int binaryToInt(const std::vector<int>& binaryNum) {
    int result = 0;
    int size = binaryNum.size();

    for (int i = 0; i < size; i++) {
        result += binaryNum[size - i - 1] * (1 << i);
    }

    return result;
}

void printBinary(std::vector<int> v) {
  for (int digit : v) {
        std::cout << digit;
  }
  std::cout << std::endl;
}
