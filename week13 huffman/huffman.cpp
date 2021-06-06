#include "huffman.h"

// Ham tao mot node moi tren cay Huffman
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();
 
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
 
    return node;
}

// Kiem tra xem node co phai la node la
bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}
 
 
// Duyet cay Huffman va luu tru ma Huffman tren map
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }
 
    // Neu tim thay mot nut la
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
 
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
 
// Duyet cay Huffman va giai ma chuoi Huffman 
void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }
 
    // found a leaf node
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}
 
//void buildHuffmanTree2(string text)

//void buildHuffmanTree3(string text)

 
// Xay dung cay Huffman va giai ma van ban dau vao input
void buildHuffmanTree(string text, int menu)
{
    // Neu van ban input trong
    if (text == EMPTY_STRING) {
        return;
    }
 
    // dem tan suat xuat hien cua tung ki tu
    // va luu tru no trong mot ban do
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }
 	// ki tu fraq
 	cout<<"Character Freq: \n";
    unordered_map<char, int>::const_iterator got;
 	for (short ch=0; ch<=255; ch++) { // de kieu short, neu de char se bi tran so
 		got = freq.find (ch);
 		if(got != freq.end())
 		{
 			cout<<got->first<<" : " <<got->second<<endl;
		}        	
    }
    cout<<endl;
    
    // Tao mot hang doi uu tien de luu tru cac not truc tiep cua cay Huffman
    priority_queue<Node*, vector<Node*>, comp> pq;
 
    // Tao mot not la cho moi ki tu va them no 
    // vao hang doi uu tien. 
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
 
    // khi trong hang doi van nhieu hon 1 node thi van lam 
    while (pq.size() != 1)
    {
        // Loai bo hai not co muc do uu tien cao nhat
        // (tan suat thap nhat) tu hang doi 
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();
 
        // tao mot not noi bo moi voi hai not nay la con va
         // voi tan so bang tong tan so cua hai not.
         // Them not moi vao hang doi uu tien. 
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
 
    // `root` luu tru con tro toi goc cua Huffman Tree 
    Node* root = pq.top();
 
    // Duyet Cay Huffman va luu tru Ma Huffman
     // trong mot ban do. Sau do in chung 
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);
 
    cout << "Huffman Codes are:\n" << endl;
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }
 
    //cout << "\nThe original string is:\n" << text << endl;
 
    // In chuoi ma hoa 
    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }
    cout << "\nThe encoded string is:\n" << str << endl;
    
    if (menu ==3){
        //Giai ma chuoi ma hoa
        cout << "\nThe decoded string is:\n";
        if (isLeaf(root))
        {
            // Truong hop dac biet: Doi voi dau vao nhu a, aa, aaa, v.v.
            while (root->freq--) {
                cout << root->ch;
            }
        }
        else {
            // Duyet Cay Huffman va
            // giai ma chuoi ma hoa 
            int index = -1;
            while (index < (int)str.size() - 1) {
                decode(root, index, str);
            }
        }
    }
}

//Ma hoa Huffman voi file
void buildHuffmanTree_File(int menu){
    fstream file;
    string filePath;
    cout << "Hay nhap ten file:  ";   
    cin >> filePath;
    file.open(filePath, ios::in);
    //Doc file vao str roi luu vao str2
    if(file.is_open()){
        string str, str2;
        while(getline(file, str)){
            str2.insert(str2.length(), str +="\n");
        }
        cout<< str2<< endl;
        buildHuffmanTree(str2,menu);
    }
    file.close();
}

