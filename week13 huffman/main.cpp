#include "huffman.h"

// Huffman coding algorithm implementation in C++
int main()
{
    int menu;
    string text;
    //ifstream file; //doc file
    //ofstream file1 ("giaima.txt"); // ghi file
    while(0==0){
        cout << "---------------------------MENU-------------------------------\n";
        cout << "\n1.Minh hoa huffman voi xau nhap tu ban phim\n2.Ma hoa file text\n3.Giai ma file text\n4.Thoat\n";
        cout << "--------------------------------------------------------------\n";
        cout << "Hay chon menu: ";
        cin >> menu;
        switch(menu){
            case 1:
                cout<< "Hay nhap xau muon ma hoa Huffman: ";
                //cin >> text; //chi nhap chuoi khong chua khoang trang
                cin.ignore();
                getline(cin, text);
                buildHuffmanTree(text,1);
                break;
            case 2:
                buildHuffmanTree_File(2);
                //cout<<"Ma hoa file "<<filePath<<" thanh cong!!";
                /*file.open("text.txt");
                file.close();*/
                break;
            case 3:
                buildHuffmanTree_File(3);
                //file.close();
                break;
            case 4:
                exit(0);
            default:
                cout << "Khong co menu nay!!!\n";
        }
    }   
 
    return 0;
}
