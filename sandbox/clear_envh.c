/* Testing function */

void    clear_all_env_h(char **environ, t_hlist **env_h)
{
        int     n;
        char    *ptr;
        char    *str;

        n = -1;
        while (environ[++n])
        {
                ptr = ft_strchr(environ[n], '=');
                *ptr = '\0';
                str = ft_strjoin("unsetenv ", environ[n]);
                unset_env(str, env_h);
                *ptr = '=';
                free(str);
        }
}
