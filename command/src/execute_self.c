
#include "../includes/command.h"

// 引数のコマンド名と実行時のコマンドが一致していたらtrue
bool	is_(char *command, char *cmd)
{
	if (is_same_str(cmd, command))
		return (true);
	return (false);
}

void	execute_self_cmd(t_cmd	*c, t_exec_attr *ea, bool is_pipe)
{
	// TODO:argsだけ渡して成り立つものはargsの渡しで片付ける
	// echo hoge fugaみたいなケースはargsの線形リストに入るので、線形リストを回さないとだめ
	if (is_(CD, c->cmd))
		g_exit_status = exec_self_cd(c, ea);
	else if (is_(EXPORT, c->cmd))
		g_exit_status = exec_self_export(c, ea);
	else if (is_(EXIT, c->cmd))
		g_exit_status = exec_self_exit(c, ea, is_pipe);
	else if (is_(UNSET, c->cmd))
		g_exit_status = exec_self_unset(c, ea);
	else if (is_(PWD, c->cmd))
		g_exit_status = exec_self_pwd(c, ea);
	else if (is_(ECHO, c->cmd))
		g_exit_status = exec_self_echo(c, ea);
	else if (is_(ENV, c->cmd))
		g_exit_status = exec_self_env(c, ea);
	if (is_pipe)
		exit(g_exit_status);
}

// TODO: is_関数を使う
bool	is_self_cmd(char *cmd)
{
	if (is_(CD, cmd))
		return (true);
	if (is_(EXPORT, cmd))
		return (true);
	if (is_(EXIT, cmd))
		return (true);
	if (is_(UNSET, cmd))
		return (true);
	if (is_(PWD, cmd))
		return (true);
	if (is_(ECHO, cmd))
		return (true);
	if (is_(ENV, cmd))
		return (true);
	return (false);
}
