
char    *trim_end2(char *str)
{
        char *ptr;

        ptr = ft_strchr(str, ' ');
        if (ptr)
                *ptr = '\0';
        return(str);
}
