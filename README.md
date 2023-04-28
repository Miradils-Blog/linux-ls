# linux-ls
Rewriting Linux 'ls' command in C. 

The following flags are/will be supported:


| Implemented                | flag    | description                                                                                               |
| -------------------------- | ------- | --------------------------------------------------------------------------------------------------------- |
| <ul> <li>- [ ] </li> </ul> | **-a** | Show hidden entries (a.k.a. files starting with '.')                                                      |
| <ul> <li>- [ ] </li> </ul> | **-A** | Do not show current and previous directories ("." and "..")                                               |
| <ul> <li>- [ ] </li> </ul> | **-C** | List entries in tabular format (by columns)                                                               |
| <ul> <li>- [ ] </li> </ul> | **-c** | Sort entries by their "last modification time"                                                            |
| <ul> <li>- [ ] </li> </ul> | **-d** | List directories themselves, not their contents                                                           |
| <ul> <li>- [ ] </li> </ul> | **-f** | List all files in their order in directory, without any colors                                            |
| <ul> <li>- [ ] </li> </ul> | **-F** | Append indicator (kind of like extension) to the end of filename, depending their type (one of */=>@ \| ) |
| <ul> <li>- [ ] </li> </ul> | **-g** | Same as `-l`, but do not show owner.                                                                      |
| <ul> <li>- [ ] </li> </ul> | **-G** | In list view, do not show group                                                                           |
| <ul> <li>- [ ] </li> </ul> | **-h** | In list view, show file size in human-readable form (2G, 12M, etc.)                                       |
| <ul> <li>- [ ] </li> </ul> | **-i** | Print inode (index number) of each file                                                                   |
| <ul> <li>- [ ] </li> </ul> | **-l** | Show enties in long list format                                                                           |
| <ul> <li>- [ ] </li> </ul> | **-m** | Show list as comma-separated values                                                                       |
| <ul> <li>- [ ] </li> </ul> | **-n** | Same as `-l`, but show owner and group ID                                                                 |
| <ul> <li>- [ ] </li> </ul> | **-p** | Put '/' at the end of directory names                                                                     |
| <ul> <li>- [ ] </li> </ul> | **-Q** | All file names will be inside quotes                                                                      |
| <ul> <li>- [ ] </li> </ul> | **-r** | Reverse order for sorting                                                                                 |
| <ul> <li>- [ ] </li> </ul> | **-R** | List all subdirectories recursively.                                                                      |
| <ul> <li>- [ ] </li> </ul> | **-S** | Sort file by size, largest first                                                                          |
| <ul> <li>- [ ] </li> </ul> | **-t** | Sort by time, newest first                                                                                |
| <ul> <li>- [ ] </li> </ul> | **-u** | Sort and show access time. Newest first.                                                                  |
| <ul> <li>- [ ] </li> </ul> | **-U** | Do not sort, list entries in directory order                                                              |
| <ul> <li>- [ ] </li> </ul> | **-x** | List entries by lines                                                                                     |
| <ul> <li>- [ ] </li> </ul> | **-X** | Sort alphabetically by file extensions                                                                    |
| <ul> <li>- [ ] </li> </ul> | **-1** | List one file per line                                                                                    |
