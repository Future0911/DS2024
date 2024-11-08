#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// 二叉树节点
struct BinTreeNode {
    char ch;            // 存储字符
    int freq;           // 存储字符频率
    BinTreeNode* left;  // 左子树
    BinTreeNode* right; // 右子树

    BinTreeNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// 比较器，用于优先队列（小根堆）
struct Compare {
    bool operator()(BinTreeNode* a, BinTreeNode* b) {
        return a->freq > b->freq;
    }
};

// 构建Huffman树
BinTreeNode* buildHuffTree(const unordered_map<char, int>& freq_map) {
    priority_queue<BinTreeNode*, vector<BinTreeNode*>, Compare> minHeap;

    // 将频率表中的每个字符和其频率添加到堆中
    for (const auto& entry : freq_map) {
        minHeap.push(new BinTreeNode(entry.first, entry.second));
    }

    // 构建Huffman树
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

// 生成Huffman编码
void generateHuffCode(BinTreeNode* node, const string& code, unordered_map<char, string>& huffCode) {
    if (!node) return;

    if (!node->left && !node->right) {
        huffCode[node->ch] = code;
        return;
    }

    generateHuffCode(node->left, code + "0", huffCode);
    generateHuffCode(node->right, code + "1", huffCode);
}

// 对输入字符串进行Huffman编码
string huffmanEncode(const string& input, const unordered_map<char, string>& huffCode) {
    string encodedString;
    for (char c : input) {
        c = tolower(c);  // 转换为小写
        if (huffCode.find(c) != huffCode.end()) {  // 只编码字母
            encodedString += huffCode.at(c);
        }
    }
    return encodedString;
}

int main() {
    // 给定的句子
    string text = "I have a dream that one day, down in Alabama, with its vicious racists, "
        "with its governor having his lips dripping with the words of \"interposition\" "
        "and \"nullification\" -- one day right there in Alabama little black boys and black girls "
        "will be able to join hands with little white boys and white girls as sisters and brothers.";

    // 统计字母的频率
    unordered_map<char, int> freq_map;
    for (char c : text) {
        if (isalpha(c)) { // 只考虑字母
            c = tolower(c); // 转换为小写，忽略大小写
            freq_map[c]++;
        }
    }

    // 构建Huffman树
    BinTreeNode* huffTreeRoot = buildHuffTree(freq_map);

    // 生成Huffman编码
    unordered_map<char, string> huffCode;
    generateHuffCode(huffTreeRoot, "", huffCode);

    // 输出生成的Huffman编码
    cout << "Huffman Encoding:" << endl;
    for (const auto& entry : huffCode) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // 测试编码
    string word1 = "dream";
    string word2 = "boys";
    string encodedWord1 = huffmanEncode(word1, huffCode);
    string encodedWord2 = huffmanEncode(word2, huffCode);

    cout << "\nEncoded 'dream': " << encodedWord1 << endl;
    cout << "Encoded 'boys': " << encodedWord2 << endl;

    return 0;
}
