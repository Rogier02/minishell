#include "minishell.h"

void wachter(t_minishell *minishell)
{
    t_child_p *current = minishell->child;
    int status;
    
    while (current)
    {
        if (current->pid > 0)
        {
            waitpid(current->pid, &status, 0);
            if (WIFEXITED(status))
                minishell->exit_code = WEXITSTATUS(status);
        }
        current = current->next;
    }
}