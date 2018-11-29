# Phantasma.Idiom
新しいイディオム"Phantasma"の提案と応用例です。  
これは、"Pimpl"の進化版です。  

以下の特徴があります。  
* **"Pimpl"より記述が面倒**
* 公開classから、private要素を完全除去
* 複数のメモリースキームに対応可能

<br>

# ビルド＆テスト
## **Msvc**
cl Main.cpp Pimpl.cpp Phantasma.cpp -Ox -F0x10000000 -EHsc -Fe:TestMsvc.exe  
TestMsvc.exe  

## **clang++**
clang++ Main.cpp Pimpl.cpp Phantasma.cpp -O3 -Wl,--stack,0x10000000 -o TestClang.exe  
TestClang.exe  

## **g++**
g++ Main.cpp Pimpl.cpp Phantasma.cpp -O3 -Wl,--stack,0x10000000 -o TestGcc.exe  
TestGcc.exe  

<br>

# ベンチマーク
動作環境は以下の通り。  
* Windows 10 Pro 64bit  
* Core i7-8700 3.20GHz  

メモリースキームの応用例として、local_ptr(後述)との組み合わせを試してみました。  
単位は秒で、数値が低いほど高速です。  
* 「生成と破棄」を「1,000,000」回でサンプリング
* 「メソッドの呼び出し」を「100,000,000」回でサンプリング

## **Msvc**
Microsoft(R) C/C++ Optimizing Compiler Version 19.15.26732.1 for x64  
Microsoft (R) Incremental Linker Version 14.15.26732.1  

||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04009438|0.03977647|**0.00504075**|
|メソッドの呼び出し|0.09252870|0.09257201|0.09184603|

## **clang**
clang version 7.0.0 (tags/RELEASE_700/final)  
Target: x86_64-w64-windows-gnu  

||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04081490|0.03976941|**0.00420185**|
|メソッドの呼び出し|0.11360534|0.09064752|0.09042264|

## **gcc**
gcc version 8.2.0 (Rev3, Built by MSYS2 project)  
Target: x86_64-w64-mingw32  

||Pimpl.unique_ptr|Phantasma.unique_ptr|Phantasma.local_ptr|
|-:|-:|-:|-:|
|生成と破棄|0.04010625|0.04020441|**0.00414539**|
|メソッドの呼び出し|0.09052177|0.09079541|0.09055738|

## 所感
どの環境でも安定して使えそうです。  
clangの"Pimpl"では、「メソッドの呼び出し」に多少コストが掛かっているように見えます。  

<br>

# local_ptrとは？
以下の特徴があります。
* unique_ptrと同様、唯一の所有権を持つ
* スタック上にインスタンスを生成する
* ブレースを抜ける際にインスタンスを破棄する
* メソッドを抜ける際にスタックを開放する

"Phantasma"なclassでlocal_ptrを使うには、以下のメソッドが必要となります。  
~~~
static std::size_t local_size();    // 実体classのサイズを返す
void local_init();                  // コンストラクタのラッパー
~~~

<br>

# 余談
如何だったでしょうか？  

正直、手間ばかり掛かって、得られるものが「僅かばかりの外面の良さ」というのが泣けます。  

local_ptrと併用しなければ実行上のメリットは殆どありませんし、local_ptrが必要となる場面すら稀だろうと思います。  
