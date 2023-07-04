#include <iostream>
using namespace std;
void getKeyMatrix(const string& key, int keyMatrix[][3]) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}
void encrypt(int cipherMatrix[][1], const int keyMatrix[][3], const int messageVector[][1]) {
    int x, i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            cipherMatrix[i][j] = 0;
            for (x = 0; x < 3; x++) {
                cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}
void decrypt(int plainMatrix[][1], const int keyMatrix[][3], const int cipherMatrix[][1]) {
    int x, i, j;
    int inverseMatrix[3][3] = {{0}};
    int determinant =
        keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
        keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
        keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);
    int inverseDeterminant = -1;
    for (int i = 0; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            inverseDeterminant = i;
            break;
        }
    }
    if (inverseDeterminant == -1) {
        cout << "Invalid key. Decryption not possible." << endl;
        return;
    }
    inverseMatrix[0][0] = (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) * inverseDeterminant;
    inverseMatrix[0][1] = (keyMatrix[0][2] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][2]) * inverseDeterminant;
    inverseMatrix[0][2] = (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) * inverseDeterminant;
    inverseMatrix[1][0] = (keyMatrix[1][2] * keyMatrix[2][0] - keyMatrix[1][0] * keyMatrix[2][2]) * inverseDeterminant;
    inverseMatrix[1][1] = (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]) * inverseDeterminant;
    inverseMatrix[1][2] = (keyMatrix[0][2] * keyMatrix[1][0] - keyMatrix[0][0] * keyMatrix[1][2]) * inverseDeterminant;
    inverseMatrix[2][0] = (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]) * inverseDeterminant;
    inverseMatrix[2][1] = (keyMatrix[0][1] * keyMatrix[2][0] - keyMatrix[0][0] * keyMatrix[2][1]) * inverseDeterminant;
    inverseMatrix[2][2] = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) * inverseDeterminant;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            inverseMatrix[i][j] = (inverseMatrix[i][j] % 26 + 26) % 26;
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            plainMatrix[i][j] = 0;
            for (x = 0; x < 3; x++) {
                plainMatrix[i][j] += inverseMatrix[i][x] * cipherMatrix[x][j];
            }
            plainMatrix[i][j] = (plainMatrix[i][j] % 26 + 26) % 26;
        }
    }
}
void HillCipher(const string& message, const string& key) {
    if (key.length() != 9) {
        cout << "Invalid key. Key length must be 9 characters." << endl;
        return;
    }
    int keyMatrix[3][3];
    getKeyMatrix(key, keyMatrix);
    int messageVector[3][1];
    for (int i = 0; i < 3; i++) {
        messageVector[i][0] = (message[i]) % 65;
    }
    int cipherMatrix[3][1];
    encrypt(cipherMatrix, keyMatrix, messageVector);
    string cipherText;
    for (int i = 0; i < 3; i++) {
        cipherText += cipherMatrix[i][0] + 65;
    }
    cout << "Ciphertext: " << cipherText << endl;
    int decryptedMatrix[3][1];
    decrypt(decryptedMatrix, keyMatrix, cipherMatrix);
    string decryptedText;
    for (int i = 0; i < 3; i++) {
        decryptedText += decryptedMatrix[i][0] + 65;
    }
    cout << "Decrypted text: " << decryptedText << endl;
}
int main() {
    string message = "ABC";
    string key = "GYBNQKURP";
    HillCipher(message, key);
    return 0;
}
