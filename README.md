# ワンボードマイコンにSD-Cardとのロード、セーブ機能

　LKIT-16のようなキーボードにより単独で操作できるワンボードマイコンに最少のハードとソフトでSD-Cardとのロード、セーブ機能が使えるように目指したものです。

　SD-CardとのアクセスはArduino任せにし、ワンボードマイコンとは4線(入力2、出力2)でシリアル同期通信を行います。


## 必要なハードウェア

　Arduinoならなんでも(私が使ったのはPro Mini Atmega328 5V 16M)
 
　SD-Cardモジュール(私が使ったのはK-14015 microSDカードスロット レベルシフタ付きブレークアウト基板キット)
 
　ピンソケット等(接続したいワンボードマイコンのコネクタによります)
 
## 接続
　以下のとおり接続します。
 
　SD-CardとArduinoは標準的な接続です。
 
　ワンボードマイコンとの接続は、ワンボードマイコン側のI/Oとソフトウェアによりそれぞれ変わります。
 
　SD-Card　　　　　Arduino　　　　　　　　　ワンボードマイコン

　　　CLK　　-----　　13
   
　　　DAT　　-----　　12
   
　　　CMD　 -----　　11
   
　　　CS　　 -----　　10
   
　　　5V　　 -----　　5V　　　　　　　　　-----　　5V
   
　　　GND　 -----　　GND　　　　　　　　-----　　GND
   
　　　　　　　　　　9(FLG:output)　　-----　　CHK(input)
             
　　　　　　　　　　8(OUT:output)　　-----　　IN(input)
                
　　　　　　　　　　7(CHK:input)　　　-----　　FLG(output)
                
　　　　　　　　　　6(IN :input)　　　-----　　OUT(output)
                

## 使い方
 ワンボードマイコンからのコマンドにより制御されますので特に何かをする必要はないはずですが、挙動がおかしいと感じるときは、リセットボタンを押して再度試してください。

## 扱えるファイル
 拡張子btkとなっているバイナリファイルです。
 
 ファイル名は0000～FFFFまでの16進数4桁を付けてください。(例:0100.btk)
 
 この16進数4桁がワンボードマイコンからSD-Card内のファイルを識別するファイルNoとなります。
 
 構造的には、バイナリファイル本体データの先頭に4バイトの開始アドレス、終了アドレスを付加した形になっています。
 
 パソコンのクロスアセンブラ等でワンボードマイコン用の実行binファイルを作成したらバイナリエディタ等で先頭に4バイトの開始アドレス、終了アドレスを付加し、ファイル名を変更すればワンボードマイコンから呼び出せるようになります。

## 参考
 ワンボードマイコンからは次のコマンドを受け付けます。
 LOAD : 80
 SAVE : 81
