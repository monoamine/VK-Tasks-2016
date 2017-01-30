#define _GNU_SOURCE

#include "trie.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        perror("Error opening file.\n");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        perror("Error reading file's stats.\n");
        return 1;
    }
    if (!S_ISREG (sb.st_mode))
    {
        fprintf(stderr, "%s is not a regular file.\n", argv[1]);
        return 1;
    }

    char *map_ptr = mmap (0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map_ptr == MAP_FAILED)
    {
        perror("Error during mmap.\n");
        return 1;
    }

    puts("Please wait while the file is being read...");
    Trie* tr = new_trie();
    char *word;
    off_t file_len = 0, word_start = 0;
    for (file_len = 0; file_len < sb.st_size; file_len++)
    {
        if (map_ptr[file_len] == '\n')
        {
            word = &map_ptr[word_start];
            word_start = file_len + 1;

            trie_add(tr, word);
        }
    }
    // '\n' is the delimeter between words in mmaped file and when adding to the trie
    // it may be possible that there's no \n' at the end of file
    if (map_ptr[file_len - 1] != '\n') 
    {
        char* last_word;
        asprintf(&last_word, "%s\n", &map_ptr[word_start]);
        trie_add(tr, last_word);
        free(last_word);
    }
    munmap(map_ptr, sb.st_size);

    puts("Done.");
    puts("Now you can search:");
    const int max_word_sz = 255;
    char to_find[max_word_sz];
    while (1)
    {
        scanf("%s", to_find);
        if (!strcmp(to_find, "exit")) break;
        if (trie_find(tr, to_find)) puts("YES");
        else puts("NO");
    }

    delete_trie(tr);
    return 0;
}
