
char *trim_end(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] == ' ')
		str[len--] = '\0';
	return (str);
}
