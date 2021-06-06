#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include<fstream>
using namespace std;
 
#define EMPTY_STRING ""
 
// Khai bao cau truc node
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};
 
// Ham tao mot node moi tren cay Huffman
Node* getNode(char ch, int freq, Node* left, Node* right);

 
// Đối tượng so sánh được sử dụng để đặt hàng đống
struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        // mục ưu tiên cao nhất có tần suất thấp nhất 
        return l->freq > r->freq;
    }
};
 
// Kiem tra xem co phai node la khong
bool isLeaf(Node* root);
 
// Duyet cay Huffman va luu tru ma Huffman tren map
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode);
 
// Duyet cay Huffman va giai ma chuoi Huffman 
void decode(Node* root, int &index, string str);
 
// Ma hoa Huffman van ban dau vao input
void buildHuffmanTree(string text, int menu);

//Ma hoa Huffman voi file
void buildHuffmanTree_File(int menu);
