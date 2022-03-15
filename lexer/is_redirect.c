#include "lexer.h"
#include <stdbool.h>

bool	is_redirect(t_tokentype type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC);
}

bool	is_redirect_without_heredoc(t_tokentype type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND);
}
