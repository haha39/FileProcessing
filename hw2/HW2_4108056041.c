#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <locale.h>

static int find_file(const char *dirname, char *filename);

int main(int argc, char *argv[])
{
	/* Select default locale */
	setlocale(LC_ALL, "");

	/* For each directory in command line */
	/*int i = 1;
	while (i < argc) {
		if (!find_directory(argv[i], argv[1]))
			exit(EXIT_FAILURE);
		i++;
	}*/

	/* List current working directory if no arguments on command line */
	int flag;
	if (argc == 2) {
		printf("from path : .\n");
		printf("search file : %s\n", argv[1]);
		flag = find_file(".", argv[1]);
	}
	else if(argc == 3) {
		printf("from path : %s\n", argv[1]);
		printf("search file : %s\n", argv[2]);
		flag = find_file(argv[1], argv[2]);
	}
	
	if(flag == 0) {
		printf("cannot find the corresponding file\n");
	}

	return EXIT_SUCCESS;
}

/* Find files and subdirectories recursively */
static int find_file(const char *dirname, char *filename)
{
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	char *end = &buffer[PATH_MAX];
	int ct=0;

	/* Copy directory name to buffer */
	const char *src = dirname;
	while (p < end && *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';

	/* Open directory stream */
	DIR *dir = opendir(dirname);
	if (!dir) {
		/* Could not open directory */
		fprintf(stderr,
			"Cannot open %s (%s)\n", dirname, strerror(errno));
		return /*failure*/ 0;
	}

	/* Print all files and directories within the directory */
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL) {
		char *q = p;
		char c;

		/* Get final character of directory name */
		if (buffer < q)
			c = q[-1];
		else
			c = ':';

		/* Append directory separator if not already there */
		if (c != ':' && c != '/' && c != '\\')
			*q++ = '/';

		/* Append file name */
		src = ent->d_name;
		while (q < end && *src != '\0') {
			*q++ = *src++;
		}
		*q = '\0';

		/* Decide what to do with the directory entry */
		switch (ent->d_type) {
		//case DT_LNK:
		case DT_REG:
			/* Output file name with directory */
			if(strcmp(ent->d_name, filename) == 0) {
				ct++;
				printf("%s\n", buffer);
			}
			break;
		case DT_DIR:
			/* Scan sub-directory recursively */
			if (strcmp(ent->d_name, ".") != 0
				&&  strcmp(ent->d_name, "..") != 0) {
				ct += find_file(buffer, filename);
			}
			break;
		default:
			/* Ignore device entries */
			/*NOP*/;
		}
	}

	//printf("%d\n", ct);

	closedir(dir);
	return ct;
}



