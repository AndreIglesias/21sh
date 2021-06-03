/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:29:37 by jiglesia          #+#    #+#             */
/*   Updated: 2021/06/02 23:38:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# define BUFFER_SIZE 32

typedef unsigned char	t_uchar;

typedef struct s_trie
{
	t_uchar				children;
	t_uchar				end;
	struct s_trie		**map;
	char				*value;
}	t_trie;

typedef struct s_list
{
	void			*data;
	size_t			size;
	struct s_list	*next;
}					t_list;

typedef struct s_listi
{
	int				n;
	size_t			size;
	struct s_listi	*next;
}					t_listi;

char				*ft_strpop(char *str, size_t i);
int					is_file(char *filename);
int					ft_countchr(const char *s, int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dest, char *src, size_t size);
char				*ft_strnstr(const char *big, const char *litle, size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strins(char *s1, char const *s2, size_t pos);
char				*ft_fstrjoin(char *s1, char *s2);
char				*ft_fchrjoin(char *s1, char s2);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)
						(unsigned int a, char c));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					get_next_line(int fd, char **line);
double				ft_atod(char *str);
int					ft_exp(int a, int e);
int					ft_putstr(char *str);
int					ft_putchar(char c);
void				*ft_puterror(char *str, void *a);
void				ft_putnbr(int n);
int					ft_rgbtoi(unsigned char r, unsigned char g,
						unsigned char b);
double				ft_sqrt(double n);
t_list				*ft_newlist(void *data, size_t size);
t_listi				*ft_newlisti(int data, size_t size);

char				*get_value(t_trie *root, char *cmd);
t_trie				**delete_value(t_trie **root, char *key, int len,
						int depth);
void				delete_node(t_trie **node);
void				insert_trie(t_trie **root, char *cmd, int eq);
void				*ft_memalloc(size_t size);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strndup(const char *str, size_t size);
char				*ft_realloc(char *str, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_freesplit(char **split);
void				ft_puttrie(t_trie *root, char *str, int lvl);
void				ft_freetrie(t_trie **root);
long long			ft_atoll(char *nb);

#endif
