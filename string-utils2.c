#include "shel.h"

char *_itoa(size_t num) {
	size_t i, len = 0, tmp = num;
	char *str = NULL;

	if (num == 0)
		return ((_strdup("0")));

	while (tmp) {
		len++;
		tmp /= 10;
	}

	str = malloc((len + 1) * sizeof(char));
	if (!str) {
		perror("_itoa: str");
		return (NULL);
	}

	i = len;
	str[i--] = '\0';
	while (num) {
		str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	return (str);
}

