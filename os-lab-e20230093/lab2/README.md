# Lab 2 — Linux Navigation and File Management: individual report

- Student name/ID: Phoung Sovannara / e20230093
- Ubuntu username: gic-phoung-sovannara
- My values (`oslab values lab2`): file1 = vendor list.txt, file2 = audit notes.txt, owner = Sales, reader = Marketing, third = HR
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv -- "$file1" ../reports/` | `lab2/incoming` |
| Move the second file (absolute paths) | `mv -- "$OSLAB_WORKSPACE/lab2/incoming/$file2" "$OSLAB_WORKSPACE/lab2/reports/"` | `lab2` |
| Read the report from my reader department (relative path) | `cat -- "../$owner/$file1"` | `lab2/TechCorp/Marketing` |
| The path error I made on purpose, and its message | `cat "reports/$file1"` gave `cat: 'reports/vendor list.txt': No such file or directory` | `lab2/TechCorp/Marketing` |
| The relative path that fixed it | `../../reports/vendor list.txt` | `lab2/TechCorp/Marketing` |

## Explanation

A relative path is always read from the folder I am in at that moment, not from the lab folder. The file `reports/vendor list.txt` really existed, but from `TechCorp/Marketing` the shell looked for a `reports` folder inside Marketing, and there is none, so I got "No such file or directory" with a correct file name. I had to go up two folders (`../../`) to reach the lab folder first. `mv` moves the file: after `mv -- "$file1" ../reports/`, `vendor list.txt` was gone from `incoming/` and only existed in `reports/`. `cp` makes a second file: after copying to `TechCorp/Sales/`, `vendor list.txt` was in both `reports/` and `TechCorp/Sales/`.

## What My Tests Do Not Prove

`ls` and `find` only show that a file with that name exists, not what is inside it. `cmp` proves the copies in `TechCorp/Sales/` have exactly the same bytes as the files in `reports/`, but it does not prove those bytes are the original content from `incoming/`; I only know that because I read them with `cat` before moving them (`amount,700` and `amount,722`).
