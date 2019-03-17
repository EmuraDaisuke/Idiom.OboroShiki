# 朧式
新しいイディオム「朧式」の提案です。  
これは、Pimplの進化版です。  

以下の特徴があります。  
* **Pimplより、更に記述が面倒**
* 公開classから、private要素を完全に除去
* 複数のメモリースキームに対応可能
  * ヒープを扱うunique_ptrやshared_ptrの他、**独自アロケータ用のポインタと併用が可能**

<br>

# 概要
朧式は、公開classと実装classの相互reinterpret_castが全てです。  
~~~
実装class* Cast(公開class* p){ return reinterpret_cast<実装class*>(p); }    // 内向きに使うcast
公開class* Cast(実装class* p){ return reinterpret_cast<公開class*>(p); }    // 外向きに使うcast
~~~

<br>

# 複数メモリースキームへの対応例
## local_ptr
以下の特徴があります。
* スタック上にインスタンスを生成する
* unique_ptrと同様、唯一の所有権を持つ
* ブレースを抜ける際にインスタンスを破棄する
* 関数を抜ける際にスタックを開放する
* **ループ内で使うと、スタックを大量に消費する可能性があるので、注意が必要(対策可能)**

## 使い方
公開classに以下のメソッドを追加します。  
~~~
static std::size_t local_size();    // 実装classの実体サイズを返す
void local_init([引数...]);         // コンストラクタのラッパー
~~~

インスタンスを生成します。  
~~~
auto p = make_local(型[, 引数...]);
~~~

## スタックオーバーフローへの対応
対策なし（ループ回数が増えると動作しない）
~~~
for (int n = 回数; n; --n){
  auto p = make_local(型);
}
~~~

対策済み（ループ回数が増えても問題ない）
~~~
for (int n = 回数; n; --n){
  []{
    auto p = make_local(型);
  }();
}
~~~

<br>

# ビルド＆テスト
検証を行った環境は以下のとおりです。
  * Windows 10 Pro 64bit  
  * Core i7-8700 3.20GHz  

## **Msvc**
Microsoft(R) C/C++ Optimizing Compiler Version 19.15.26732.1 for x64  
Microsoft (R) Incremental Linker Version 14.15.26732.1  
~~~
cl Main.cpp Pimpl.cpp OboroShiki.cpp -Ox -EHsc -openmp -Fe:TestMsvc.exe
TestMsvc.exe
~~~

## **clang++**
clang version 7.0.0 (tags/RELEASE_700/final)  
Target: x86_64-w64-windows-gnu  
~~~
clang++ Main.cpp Pimpl.cpp OboroShiki.cpp -O3 -o TestClang++.exe
TestClang++.exe
~~~

## **g++**
gcc version 8.2.0 (Rev3, Built by MSYS2 project)  
Target: x86_64-w64-mingw32  
~~~
g++ Main.cpp Pimpl.cpp OboroShiki.cpp -O3 -fopenmp -o TestG++.exe
TestG++.exe
~~~

<br>

# ベンチマーク
単位は秒で、数値が低いほど高速です。  

## **Msvc**
|100,000,000回|Pimpl.unique_ptr|朧式.unique_ptr|朧式.local_ptr|
|:-|-:|-:|-:|
|生成と破棄(Normal)|3.77094619|3.77549581|**0.60779183**|
|生成と破棄(OpenMP)|0.66776221|0.67680080|**0.07440678**|
|メソッドの呼び出し|0.09252870|0.09257201|0.09184603|

## **clang++**
|100,000,000回|Pimpl.unique_ptr|朧式.unique_ptr|朧式.local_ptr|
|:-|-:|-:|-:|
|生成と破棄(Normal)|3.85479482|3.84132531|**0.48662753**|
|生成と破棄(OpenMP)|N/A|N/A|N/A|
|メソッドの呼び出し|0.09045938|0.09064752|0.09042264|

## **g++**
|100,000,000回|Pimpl.unique_ptr|朧式.unique_ptr|朧式.local_ptr|
|:-|-:|-:|-:|
|生成と破棄(Normal)|3.87667382|3.89724941|**0.46185907**|
|生成と破棄(OpenMP)|0.71910911|0.72185421|**0.05114993**|
|メソッドの呼び出し|0.09052177|0.09079541|0.09055738|

## 所感
同じunique_ptrであれば、Pimplと朧式で、差がないことが分かります。  

「生成と破棄」のNormalとOpenMPを比較すると、unique_ptrでは5～6倍の高速化に対し、local_ptrでは8～9倍と、差が開いていることが分かります。  
これは、メモリーの確保と解放に排他制御が必要なunique_ptrに対し、local_ptrでは排他制御が不要な為、より効率良く並列化できていることを示しています。  

「メソッドの呼び出し」では、特に目立った環境差はなく、安定した結果となりました。  

<br>

# 余談
如何だったでしょうか？  

イディオムよりも、local_ptrの紹介になってる気がしなくもないですが、これは両輪のようなものです。  
複数メモリースキームの運用であれば、メリットがあることを示せたと思います。  

単一メモリースキームの運用では、手間ばかり掛かって「僅かばかりの体裁の良さ」しか得られない悲しみ。  
reinterpret_castに抵抗感のある方もいらっしゃるでしょう。  

評価の難しいイディオムだと思いますが、適所での活用が良いでしょう。  
