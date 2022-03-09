# libmem_mgt

C言語のmallocで確保したメモリを管理してくれるツールです。<br>

# 機能

- mallocで確保したメモリの情報を記憶＆表示
- プログラム終了時にメモリリークの検出＆未解放のメモリを解放
- プログラムの任意のタイミングで未解放のメモリの検出＆解放
- 指定したサイズよりも多くメモリを確保した場合にエラー終了

# 使い方

1. リポジトリをgit clone

	作業ディレクトリ内にリポジトリをcloneします。
	```
	git clone https://github.com/kiri-42/libmem_mgt.git
	```
1. makeの実行

	cloneしたディレクトリに移動し、makeコマンドを実行します。
	```
	cd libmem_mgt
	make
	```
1. ヘッダーファイルをインクルード

	管理したいプログラムにmem_mgt.hとreplace_mem_mgt.hをインクルードします。
	```
	#include "libmem_mgt/mem_mgt.h"
	#include "libmem_mgt/replace_mem_mgt.h"
	```

1. コンパイルして実行

	2.で作成したlibmem_mgt.aを含めてコンパイルして実行すればメモリリークの情報を標準出力に検出してくれます。
	```
	gcc <file>.c libmem_mgt/libmem_mgt.a
	```

# 注意事項

プログラムはexitで終了してください。<br>
main関数のreturn終了やCtrl + Cには対応していません。
