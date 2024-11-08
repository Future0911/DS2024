#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// �������ڵ�
struct BinTreeNode {
    char ch;            // �洢�ַ�
    int freq;           // �洢�ַ�Ƶ��
    BinTreeNode* left;  // ������
    BinTreeNode* right; // ������

    BinTreeNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// �Ƚ������������ȶ��У�С���ѣ�
struct Compare {
    bool operator()(BinTreeNode* a, BinTreeNode* b) {
        return a->freq > b->freq;
    }
};

// ����Huffman��
BinTreeNode* buildHuffTree(const unordered_map<char, int>& freq_map) {
    priority_queue<BinTreeNode*, vector<BinTreeNode*>, Compare> minHeap;

    // ��Ƶ�ʱ��е�ÿ���ַ�����Ƶ����ӵ�����
    for (const auto& entry : freq_map) {
        minHeap.push(new BinTreeNode(entry.first, entry.second));
    }

    // ����Huffman��
    while (minHeap.size() > 1) {
        BinTreeNode* left = minHeap.top(); minHeap.pop();
        BinTreeNode* right = minHeap.top(); minHeap.pop();

        BinTreeNode* newNode = new BinTreeNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// ����Huffman����
void generateHuffCode(BinTreeNode* node, const string& code, unordered_map<char, string>& huffCode) {
    if (!node) return;

    if (!node->left && !node->right) {
        huffCode[node->ch] = code;
        return;
    }

    generateHuffCode(node->left, code + "0", huffCode);
    generateHuffCode(node->right, code + "1", huffCode);
}

// �������ַ�������Huffman����
string huffmanEncode(const string& input, const unordered_map<char, string>& huffCode) {
    string encodedString;
    for (char c : input) {
        c = tolower(c);  // ת��ΪСд
        if (huffCode.find(c) != huffCode.end()) {  // ֻ������ĸ
            encodedString += huffCode.at(c);
        }
    }
    return encodedString;
}

int main() {
    // �����ľ���
    string text = "I have a dream that one day, down in Alabama, with its vicious racists, "
        "with its governor having his lips dripping with the words of \"interposition\" "
        "and \"nullification\" -- one day right there in Alabama little black boys and black girls "
        "will be able to join hands with little white boys and white girls as sisters and brothers.";

    // ͳ����ĸ��Ƶ��
    unordered_map<char, int> freq_map;
    for (char c : text) {
        if (isalpha(c)) { // ֻ������ĸ
            c = tolower(c); // ת��ΪСд�����Դ�Сд
            freq_map[c]++;
        }
    }

    // ����Huffman��
    BinTreeNode* huffTreeRoot = buildHuffTree(freq_map);

    // ����Huffman����
    unordered_map<char, string> huffCode;
    generateHuffCode(huffTreeRoot, "", huffCode);

    // ������ɵ�Huffman����
    cout << "Huffman Encoding:" << endl;
    for (const auto& entry : huffCode) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // ���Ա���
    string word1 = "dream";
    string word2 = "boys";
    string encodedWord1 = huffmanEncode(word1, huffCode);
    string encodedWord2 = huffmanEncode(word2, huffCode);

    cout << "\nEncoded 'dream': " << encodedWord1 << endl;
    cout << "Encoded 'boys': " << encodedWord2 << endl;

    return 0;
}
