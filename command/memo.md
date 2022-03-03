is_self_commandの条件分岐をcmp == 0のif文を複数個並べる方法に変える
exportは数字を受け付けてないのでバリデーションを追加する, 記号もだめ。
ただし_はok。でも_は上書きする必要があるかも
_はenvでは一番最後に出る。exportでは出力されない ...

lexer側で=で弾いている？ export test=testみたいなやつが通らない
コマンドが何も無いときはcmd structにnullを入れてほしい
echo a| aaa ←みたいなときパイプが文字列として判定される
環境変数で_が真ん中に入っている場合、文法エラーになるケースを考慮したい


export iのときに=""が入ってしまっている
keyが存在しないときにvalueがkeyとして入ってしまっている
OLDPWDが最初はNULL
=がないvalueに更新をしたらちゃんと更新できる？

env -iで初期化した場合、環境変数は以下
```
declare -x OLDPWD
declare -x PWD="/Users/masashi/Projects/42tokyo/minishell/test/test_sh"
declare -x SHLVL="1"
```
現在OLDPWD以外は実装できていない。
cdで移動したときに、pwdの""がついていない done
OLDPWDはPWDの値をコピーするため、もしcdしたときにPWDが存在しなかったら空文字になる。

リダイレクト処理のみの動作 ex) < file
pipeがあったらそのパイプのプロセスのみエラーになる。
ただファイルが作成される。
終了ステータスは1
