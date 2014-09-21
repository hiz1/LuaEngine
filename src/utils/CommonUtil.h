//
//  CommonUtil.h
//  Menu
//
//  Created by 成田 輝久 on 2013/11/03.
//
//

#ifndef __Menu__CommonUtil__
#define __Menu__CommonUtil__

#include <iostream>
#include <stdexcept>
#include "ofMain.h"

using namespace std;

// 文字列の長さを全角文字数で数える
int utf8len(const string &s);

// 文字列の長さを半角文字数で数える
int utf8HWlen(const string &s);

// n番目の全角文字のインデックスを返す
int utf8index(const string &s, int widx);

// 半角文字で数えてn番目の文字のインデックスを返す
int utf8HBindex(const string &s, int hwidx);

// stringのbegin番目の全角文字からbegin+length-1番目の全角文字までのsubstringを返す
std::string utf8substr(const string &s, int begin, int length);

// stringのbegin番目の全角文字からbegin+length-1番目の全角文字までのsubstringを返す
std::string utf8HWsubstr(const string &s, int begin, int length);

// 文字列を１行col文字のrow行の文字列に変換する
std::string createParagraph(const string &s, int col, int row);

// 文字列をareaに収まる文字列に変換する（非推奨）
std::string createParagraphByArea(const string &s, const ofPoint &fontSize, const ofPoint &area);

// メッシュに法線ベクトルを自動追加する（TRIANGLESを想定）
void setNormals(ofMesh &mesh);

#endif /* defined(__Menu__CommonUtil__) */
