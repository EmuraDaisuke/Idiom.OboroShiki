# Phantasma.Idiom
新しいイディオム"Phantasma"の提案です。  
これは、"Pimpl"の進化版です。  

以下の特徴があります。  
* **"Pimpl"より記述が面倒**
* 公開classから、private要素を完全に除去
* 複数のメモリースキームに対応可能
  * ヒープを扱うunique_ptrやshared_ptrの他、独自アロケータ用のポインタを併用可能
    * 複数のメモリー領域を使い分け可能

<br>

# 概要
"Phantasma"イディオムは、公開classと実体classの相互reinterpret_castが全てです。  

## 疑似コード
~~~
実体class* Cast(公開class* p){ return reinterpret_cast<実体class*>(p); }
公開class* Cast(実体class* p){ return reinterpret_cast<公開class*>(p); }
~~~

<br>

# 環境
検証を行った環境は以下のとおりです。
  * Windows 10 Pro 64bit  
  * Core i7-8700 3.20GHz  

## **Msvc**
Microsoft(R) C/C++ Optimizing Compiler Version 19.15.26732.1 for x64  
Microsoft (R) Incremental Linker Version 14.15.26732.1  

## **clang++**
clang version 7.0.0 (tags/RELEASE_700/final)  
Target: x86_64-w64-windows-gnu  

## **g++**
gcc version 8.2.0 (Rev3, Built by MSYS2 project)  
Target: x86_64-w64-mingw32  

<br>

# ビルド＆テスト
## **Msvc**
~~~
cl Main.cpp Pimpl.cpp Phantasma.cpp -Ox -F0x10000000 -EHsc -Fe:TestMsvc.exe
TestMsvc.exe
~~~

## **clang++**
~~~
clang++ Main.cpp Pimpl.cpp Phantasma.cpp -O3 -Wl,--stack,0x10000000 -o TestClang++.exe
TestClang++.exe
~~~

## **g++**
~~~
g++ Main.cpp Pimpl.cpp Phantasma.cpp -O3 -Wl,--stack,0x10000000 -o TestG++.exe
TestG++.exe
~~~

<br>

# ベンチマーク
複数メモリースキームの運用例として、unique_ptrとlocal_ptr(後述)を比較してみました。  
単位は秒で、数値が低いほど高速です。  
* 「生成と破棄」を「1,000,000」回でサンプリング
* 「メソッドの呼び出し」を「100,000,000」回でサンプリング

## **Msvc**
||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04009438|0.03977647|**0.00504075**|
|メソッドの呼び出し|0.09252870|0.09257201|0.09184603|

## **clang++**
||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04081490|0.03976941|**0.00420185**|
|メソッドの呼び出し|0.11360534|0.09064752|0.09042264|

## **g++**
||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04010625|0.04020441|**0.00414539**|
|メソッドの呼び出し|0.09052177|0.09079541|0.09055738|

## 所感
clang++の"Pimpl"で、「メソッドの呼び出し」に多少コストが掛かっているように見えますが、どの環境もほぼ安定しています。  

<br>

# local_ptrとは？
以下の特徴があります。
* スタック上にインスタンスを生成する
* unique_ptrと同様、唯一の所有権を持つ
* ブレースを抜ける際にインスタンスを破棄する
* メソッドを抜ける際にスタックを開放する
* **安易にループ内で使うと、大量にスタックを消費するので注意が必要**

## 使い方
公開classに以下のメソッドを追加します。  
~~~
static std::size_t local_size();    // 実体classのサイズを返す
void local_init([引数...]);         // コンストラクタのラッパー
~~~

インスタンスを生成します。  
~~~
auto p = make_local(型[, 引数...]);
~~~

<br>

# 余談
如何だったでしょうか？  

通常用途では、手間ばかり掛かって、得られるものが「僅かばかりの体裁の良さ」というのが泣けます。  
reinterpret_castに拒絶反応を示す方もいらっしゃるでしょう。  

正直、あまり使いどころのないイディオムですが、組み込み用途であれば、活用の機会があるかもしれません。  
